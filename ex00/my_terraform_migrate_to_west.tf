terraform {
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 5.99"
    }
  }

  required_version = ">= 1.2.0"
}

####
# Set variables
####

variable "old_pandora_id" {
  type = string
  default = "i-0e94669805312bb7f"
}

variable "old_region" {
  type = string
  default = "us-east-1"
  description = "The old region."
}

variable "new_region" {
  type = string
  default = "us-west-2"
  description = "The new region."
}

####
# Set provider of the new and old instances
####

provider "aws" {
  region = var.old_region
  alias = "old"
}

# Set the region of the new EC2 instance.
provider "aws" {
  region = var.new_region
}

####
# Backup old instance.
####

# Create an AIM from the source EC2 instance.
resource "aws_ami_from_instance" "old_pandora_ami" {
  name = "${var.old_region}-pandora-ami"
  source_instance_id = var.old_pandora_id
  provider = aws.old
}

# Copy this image to the new region.
resource "aws_ami_copy" "new_pandora_ami" {
  name = "${var.new_region}-pandora-ami"
  source_ami_id = aws_ami_from_instance.old_pandora_ami.id
  source_ami_region = var.old_region
}

####
# Creation of a clone EC2 instance at the new region.
####

# Get old aws instance details.
data "aws_instance" "old_pandora" {
  instance_id = var.old_pandora_id
  provider = aws.old
}

resource "aws_instance" "new_pandora" {
  ami = aws_ami_copy.new_pandora_ami.id
  instance_type = data.aws_instance.old_pandora.instance_type
  security_groups = data.aws_instance.old_pandora.security_groups
  tags = {
    Name = "${var.new_region}-pandora-instance"
  }
}

####
# Output info
####

output old_pandora_availability_zone {
  value = data.aws_instance.old_pandora.availability_zone
}

output new_pandora_availability_zone {
  value = aws_instance.new_pandora.availability_zone
}
