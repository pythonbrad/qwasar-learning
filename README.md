# Welcome to Quest Terraform Install
***

## Task
The task consist to install terraform on an EC2 instance.

## Description
The accomplisment of this task require to have an AWS account and create an EC2 instance.
Once the instance is started, you should be connected t it through an SSH connection via the command `ssh <username>@<instance-public-ip>`

## Installation
To install terraform on an EC2, you can use the following command.
```
sudo yum update -y
sudo yum install -y yum-utils
sudo yum-config-manager --add-repo https://rpm.releases.hashicorp.com/AmazonLinux/hashicorp.repo
sudo yum -y install terraform
```

## Usage
Use the command below to get the version of the installed terraform.
```
terraform --version
```

You can customize the output format, consult `terraform -version -help`.

### The Core Team
Brady Fomegne


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
