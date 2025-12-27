####
# Variables
####

variable app_aws_s3_bucket_name {
  type = string
  description = "AWS S3 bucket used by the webapp"
  default = "andromeda-redundancy"
}

variable private_key_path {
  type = string
  description = "Private key for remote access to the created AWS EC2."
  default = "keypair.pem"
}

variable app_aws_credential_path {
  description = "Path to the AWS credentials to use for the webapp."
  type = string
}

#####
# Key generations.
#####

# Generate an RSA private key.
resource "tls_private_key" "awskey" {
  algorithm = "RSA"
  rsa_bits = 2048
}

# Save the private key to a local file.
resource "local_file" "private_key" {
  content = tls_private_key.awskey.private_key_pem
  filename = var.private_key_path
  file_permission = "0400"
}

# Create an AWS keypair using the generated public key
resource "aws_key_pair" "awskey" {
  key_name = "keypair"
  public_key = tls_private_key.awskey.public_key_openssh
}

#####
# Network policies
#####

# Default VPC
resource "aws_default_vpc" "default" {}

resource "aws_security_group" "my_security_group" {
  name = "redundancy_security_group_terraform"
  vpc_id = aws_default_vpc.default.id

  ingress {
    from_port = 22
    to_port = 22
    protocol = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  ingress {
    from_port = 80
    to_port = 80
    protocol = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  egress {
    from_port = 0
    to_port = 0
    protocol = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }
}

####
# Create the AWS S3 Bucket
####

resource "aws_s3_bucket" "s3" {
  bucket = var.app_aws_s3_bucket_name
}

#####
# Create an AWS EC2
#####

provider "aws" {
  region = "us-east-1"
}

resource "aws_instance" "server" {
  ami = "ami-0953476d60561c955"
  instance_type = "t2.micro"
  key_name = aws_key_pair.awskey.key_name
  vpc_security_group_ids = [aws_security_group.my_security_group.id]

  tags = {
    Name = "AndromedaRedundancyServerInstance"
  }

  # Config the ssh access.
  connection {
    type = "ssh"
    user = "ec2-user"
    host = self.public_ip
    private_key = tls_private_key.awskey.private_key_pem
  }

  # Deploy the nginx configuration.
  provisioner "file" {
    source = "${path.root}/confs/nginx.conf"
    destination = "/tmp/nginx.conf"
  }

  provisioner "remote-exec" {
    script = "${path.root}/scripts/deploy_nginx.sh"
  }

  # Deploy the webapp service.
  provisioner "file" {
    source = "${path.root}/confs/webapp.service"
    destination = "/tmp/webapp.service"
  }
  
  provisioner "file" {
    source = var.app_aws_credential_path
    destination = "/tmp/credentials"
  }

  provisioner "remote-exec" {
    inline = ["printf 'AWS_S3_BUCKET_NAME=\"${aws_s3_bucket.s3.bucket}\"' > /tmp/config.py"]
  }

  provisioner "remote-exec" {
    script = "${path.root}/scripts/deploy_webapp.sh"
  }
}

output "public_ip" {
  value = aws_instance.server.public_ip
}

output "public_dns" {
  value = aws_instance.server.public_dns
}

output "ssh_command" {
  value = "ssh -i ${path.root}/keypair.pem ec2-user@${aws_instance.server.public_ip}"
  sensitive = true
}
