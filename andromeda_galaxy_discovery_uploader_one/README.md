# Welcome to Andromeda Galaxy Discovery Uploader One
***

## Task
The task consists to put in practice my previous learning knowledges to deploy an EC2 instance running nginx and remote accessible via ssh.

## Description
To accomplish the task, i gone through the following steps.

- Write a installation script for the nginx server: [`userdata.tpl`](userdata.tpl).
- Configure the network policies by opening the ports 22 and 80.
- Generate a RSA keypair for the SSH connection.

## Installation
You will require to have an environment with [`terraform`](https://developer.hashicorp.com/terraform), [`aws-cli`](https://docs.aws.amazon.com/cli/latest/userguide/getting-started-install.html) installed. And you should make sure to configure aws credentials using [`aws configure`](https://docs.aws.amazon.com/cli/latest/userguide/cli-configure-files.html).

## Configuration
You can change the destination of the `private key` (generated to remove access the server) on [`terraform.tfvars`](terraform.tfvars)

## Usage
You can deploy using the following command.
```
terraform init
terraform apply
```

Note that, the instance IP / DNS will be show at end of the log.
The nginx can take a little bit time (up to 5s) to start.

To test if everything is ok, you can use one of the following methods.

- Try to http access by the IP / DNS.

```
curl <instance-ip>
```

- Access the server and check the nginx status.

```
ssh -i keypair.pem ec2-user@<instance-ip>
sudo systemctl status nginx
```

### The Core Team
Brady Fomegne


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
