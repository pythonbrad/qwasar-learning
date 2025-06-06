terraform {
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 4.16"
    }
  }

  required_version = ">= 1.2.0"
}

# Default VPC.
resource "aws_default_vpc" "default" {}

# Enable ICMP protocol.
# To be able to ping our server.
resource "aws_security_group" "my_security_group" {
  name   = "ex00_security_group_terraform"
  vpc_id = aws_default_vpc.default.id

  ingress {
    from_port   = "-1"
    to_port     = "-1"
    protocol    = "icmp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  egress {
    from_port   = "0"
    to_port     = "0"
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
  vpc_security_group_ids = [aws_security_group.my_security_group.id]

  tags = {
    Name = "ServerInstanceEx00"
  }

  # provisioner "local-exec" {
  #   # Test if the server is online
  #   command = "ping -c 5 ${self.public_ip}"
  # }
}

output "public_ip" {
  value = aws_instance.app_server.public_ip
}
