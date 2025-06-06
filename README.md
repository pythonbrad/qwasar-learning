# Welcome to Quest Terraform Build
***

## Task

The tasks consisted to deploy different EC2 instances using terraform.

**ex00** consisted to deploy a simple EC2 instance and check if it is online.
**ex01** consisted to deploy an EC2 instance with the `qwasar` user created through a ssh connecton.
**ex02** constisted to deploy an EC2 instance with nginx running inside.
**ex03** consisted to deploy an EC2 instance with nginx delivering static files through the S3 bucket.

## Description

To accomplish this tasks, i wrote a terraform instructions to:

- connect to aws
- start an EC2 instance with ssh key
- setup the EC2 instance using the ssh connection
- create and config an S3 bucket

## Installation

**Requirements**

- [terraform](https://developer.hashicorp.com/terraform/install)
- [aws-cli](https://docs.aws.amazon.com/cli/latest/userguide/getting-started-install.html)

**Tools installation**

Before the deployement, you will need to install [terraform](https://developer.hashicorp.com/terraform/install) and [aws-cli](https://docs.aws.amazon.com/cli/latest/userguide/getting-started-install.html).

For fast installation using `linux-am64`:

```
# aws
curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip"
unzip awscliv2.zip
sudo ./aws/install

# terraform
curl "https://releases.hashicorp.com/terraform/1.13.0-alpha20250521/terraform_1.13.0-alpha20250521_linux_amd64.zip" -o "terraform.zip"
sudo mv terraform/terraform /usr/local/bin/
```

**Configuration**

You need to config your AWS credentials. You can consult [aws-cli-config](https://docs.aws.amazon.com/cli/latest/userguide/cli-configure-files.html) for more details.

```
aws configure
```

**Deployment**

You can deploy the infrastruction on AWS as follows.

```
terraform init
terraform apply
```

## Usage

For each deployment, you will see the instance IP address and more useful info in the output.

**ex00**

Check the server connectivity.

```
ping <instance-ip>
```

**ex01**

Check the new user presence.

```
ssh -i ./ex01-keypair.pem ec2-user@<instance-ip>
sudo cat /etc/passwd | grep qwasar
```

**ex02**

Check the nginx service status.

```
ssh -i ./ex02-keypair.pem ex2-user@<instance-ip>
sudo systemctl status nginx
```

**ex03**

Before run terraform, make sure to download the staticfiles.

```
wget https://storage.googleapis.com/qwasar-public/track-cloud-devops/cats.zip
# Unszip data in the s3-files folder.
unzip cats.zip -d s3-files
rm cats.zip
```

You can test, the deployment as follow.

```
curl <generated_dns>/mousecat.jpg
```

### The Core Team

Brady Fomegne

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
