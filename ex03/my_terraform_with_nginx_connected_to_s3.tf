terraform {
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 4.16"
    }

    tls = {
      source  = "hashicorp/tls"
      version = "~> 4.0"
    }
  }

  required_version = ">= 1.2.0"
}

####
# Key generations.
####

# Generate an RSA private key
resource "tls_private_key" "awskey" {
  algorithm = "RSA"
  rsa_bits  = 2048
}

# Save the private key to a local file.
resource "local_file" "private_key" {
  content         = tls_private_key.awskey.private_key_pem
  filename        = "${path.root}/ex03-keypair.pem"
  file_permission = "0400"
}

# Create an AWS key pair using the generated public key.
resource "aws_key_pair" "awskey" {
  key_name   = "ex03-keypair"
  public_key = tls_private_key.awskey.public_key_openssh
}

#####
# Network policies.
#####

# Default VPC.
resource "aws_default_vpc" "default" {}

resource "aws_security_group" "my_security_group" {
  name   = "ex03_security_group_terraform"
  vpc_id = aws_default_vpc.default.id

  ingress {
    from_port   = 22
    to_port     = 22
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  ingress {
    from_port   = 80
    to_port     = 80
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }
}

####
# Config bucket of AWS S3.
####

resource "aws_s3_bucket" "s3" {
  bucket = "bucket-ex03"
}

# Configuring ACLs for S3 buckets.
# Resource to avoid error "AccessControlListNotSupported: The bucket does not allow ACLs".
resource "aws_s3_bucket_ownership_controls" "ownership" {
  bucket = aws_s3_bucket.s3.id

  rule {
    object_ownership = "BucketOwnerPreferred"
  }
}

resource "aws_s3_bucket_public_access_block" "pb" {
  bucket = aws_s3_bucket.s3.id

  block_public_acls       = false
  block_public_policy     = false
  ignore_public_acls      = false
  restrict_public_buckets = false
}

resource "aws_s3_bucket_acl" "acl" {
  bucket     = aws_s3_bucket.s3.id
  acl        = "private"
  depends_on = [aws_s3_bucket_ownership_controls.ownership]
}

# Enumerate and save files on buckets.
resource "aws_s3_object" "objects" {
  for_each = fileset(path.root, "s3-files/*.jpg")
  bucket   = aws_s3_bucket.s3.bucket
  key      = replace(each.key, "s3-files/", "")
  source   = each.value
  acl      = "public-read"
}

provider "aws" {
  region = "us-east-1"
}

resource "aws_instance" "app_server" {
  ami                    = "ami-0953476d60561c955"
  instance_type          = "t2.micro"
  key_name               = aws_key_pair.awskey.key_name
  vpc_security_group_ids = [aws_security_group.my_security_group.id]

  tags = {
    name = "ServiceInstanceEx03"
  }

  # Config the ssh access.
  connection {
    type        = "ssh"
    user        = "ec2-user"
    host        = self.public_ip
    private_key = tls_private_key.awskey.private_key_pem
  }

  # Install and deploy nginx to serve s3 files.
  provisioner "file" {
    source      = "${path.root}/nginx.conf"
    destination = "/tmp/nginx.conf"
  }

  provisioner "remote-exec" {
    inline = [
      "sudo useradd -m nginx",
      "sudo yum install -y nginx",
      "sudo cp /tmp/nginx.conf /etc/nginx/conf.d/s3-proxy.conf",
      "sudo systemctl enable nginx",
      "sudo systemctl start nginx"
    ]
  }
}

output "public_ip" {
  value = aws_instance.app_server.public_ip
}

output "public_dns" {
  value = aws_instance.app_server.public_dns
}

output "ssh_command" {
  value     = "ssh -i ${path.root}/ex03-keypair.pem ec2-user@${aws_instance.app_server.public_ip}"
  sensitive = true
}
