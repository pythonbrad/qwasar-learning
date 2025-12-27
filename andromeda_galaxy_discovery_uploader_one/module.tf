##
# Set variables
##
variable "private_key_path" {
  type    = string
  default = "keypair.pem"
}

##
# Key Generations
##

# Generate an RSA private key.
resource "tls_private_key" "awskey" {
  algorithm = "RSA"
  rsa_bits  = 2048
}

# Save the private key to a local file.
resource "local_file" "private_key" {
  content         = tls_private_key.awskey.private_key_pem
  filename        = var.private_key_path
  file_permission = "0400"
}

# Create an AWS keypair using the generated public key.
resource "aws_key_pair" "awskey" {
  key_name   = "keypair"
  public_key = tls_private_key.awskey.public_key_openssh
}

##
# Network policies
##

# Default VPC
resource "aws_default_vpc" "default" {}

resource "aws_security_group" "my_security_group" {
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

# AWS EC2 instance
provider "aws" {
  region = "us-east-1"
}

resource "aws_instance" "server" {
  ami                    = "ami-0953476d60561c955"
  instance_type          = "t2.micro"
  key_name               = aws_key_pair.awskey.key_name
  vpc_security_group_ids = [aws_security_group.my_security_group.id]
  user_data              = file("${path.root}/userdata.tpl")

  tags = {
    Name = "ServerInstance"
  }
}

output "public_ip" {
  value = aws_instance.server.public_ip
}

output "public_dns" {
  value = aws_instance.server.public_dns
}

output "ssh_command" {
  value     = "ssh -i ${var.private_key_path} ec2-user@${aws_instance.server.public_ip}"
  sensitive = true
}
