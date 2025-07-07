# Welcome to Andromeda Galaxy Discovery Uploader Redundancy
***

## Task

The task consisted to develop a web application to allow the sharing of the photo about the adromeda galaxy.

## Description

**Web application**

I developped using python-flask (backend), bulmacss+htmx (frontend), sqlite3 (database) and AWS S3 (storage), a web application of photo sharing.
I tried to make a UX design in the respect of the theme "andromeda galaxy".
The web application is available on github through https://github.com/pythonbrad/andromeda-pixel.

**Deployment**

I used terraform for the infrastructure.
The terraform script, create an S3 bucket for the webapp, create an EC2 instance with ssh access, deploy the web application on it and setup nginx as proxy gateway.

## Installation

To deploy the infrastructure, you will need to install [`terraform`](https://developer.hashicorp.com/terraform/install) and [`aws-cli`](https://docs.aws.amazon.com/cli/latest/userguide/getting-started-install.html).
After it, you should config your aws credentials using [`aws configure`](https://docs.aws.amazon.com/cli/latest/userguide/cli-configure-files.html).
And finally, you can use the following command.

```
terraform init
# Note that, the webapp use a aws client
# You will be asked to provide the path of the credential file that the webapp will use to operate.
terraform apply
```

## Usage

After deployement, you can access the server in different way.

**HTTP access**

You can use a webbrowser or make a simple test with curl.

```
curl <your-generated-server-addr>
```

**SSH access**

```
ssh -i keypair.pem ec2-user@<your-generated-server-addr>
```

### The Core Team

Brady Fomegne

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
