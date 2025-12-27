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

#####################################
#       Key generations             #
#####################################
# Generate an RSA private key.
resource "tls_private_key" "awskey" {
  algorithm = "RSA"
  rsa_bits  = 2048
}

# Save the private key to a local file.
resource "local_file" "private_key" {
  content         = tls_private_key.awskey.private_key_pem
  filename        = "${path.root}/ex01-keypair.pem"
  file_permission = "0400"
}

# Create an AWS Key Pair using the generated public key.
resource "aws_key_pair" "awskey" {
  key_name   = "ex01-keypair"
  public_key = tls_private_key.awskey.public_key_openssh
}

######################################
#       Network policies.            #
######################################

# Default VPC
resource "aws_default_vpc" "default" {}

resource "aws_security_group" "my_security_group" {
  name   = "ex01_security_group_terraform"
  vpc_id = aws_default_vpc.default.id

  ingress {
    from_port   = 22
    to_port     = 22
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

provider "aws" {
  region = "us-east-1"
}

resource "aws_instance" "app_server" {
  ami                    = "ami-0953476d60561c955"
  instance_type          = "t2.micro"
  key_name               = aws_key_pair.awskey.key_name
  vpc_security_group_ids = [aws_security_group.my_security_group.id]

  tags = {
    Name = "ServerInstanceEx01"
  }

  # Establishes ssh connection for remote operation.
  connection {
    type        = "ssh"
    user        = "ec2-user"
    host        = self.public_ip
    private_key = tls_private_key.awskey.private_key_pem
  }

  provisioner "remote-exec" {
    inline = ["sudo useradd -m qwasar"]
  }
}

output "public_ip" {
  value = aws_instance.app_server.public_ip
}

output "ssh_command" {
  value     = "ssh -i ${path.root}/ex01-keypair.pem ec2-user@${aws_instance.app_server.public_ip}"
  sensitive = true
}

