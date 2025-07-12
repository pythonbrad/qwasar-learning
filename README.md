# Welcome to Andromeda Galaxy Discovery Uploader Final
***

## Task
The task consists to write a terraform configuration file to deploy an infrastructure,
which was previously deployed without terraform.

## Description

**Analyzing of the initial implementation**

My first step consisted to underderstand the initial deployement (architecture and process).
I did it in reading the documentation, the [source code](https://github.com/awslabs/serverless-photo-recognition) and the [blog post](https://aws.amazon.com/blogs/machine-learning/use-amazon-rekognition-to-build-an-end-to-end-serverless-photo-recognition-system/).

**Writing of the terraform configuration**

After the analysis, i started to write the terraform configuration.
Not necessarely a working one but a prototype to help me to have a clear idea of what to do.
This step has been done using the [terraform documentation](https://registry.terraform.io/providers/hashicorp/aws/latest/docs/r) of AWS.
I also take time to reduce the usage of hard coding (ARN, URI, etc.)

After this prototype, i make a first attempt with `terraform plan`, to prevent mistake in the configuration.
After the configuration has been valided, i attempt a deployment on AWS and apply
some adjustment (execution order through `depends_on`) until a succeed status.
I also take a time to verify that everything is working as expected.
Additionally, i used a `outputs.tf` to display any useful information about the deployement (functions, api, domain, etc.).

**Testing**

After a succeed deployment (without testing), i tested each feature one by one.
- Authentification (signup, account validation and login)
- Picture operations (creation, deletion and searching)

And make adjustment where needed.

I wrote terraform outputs to display ready to use commands for fast testing.

**Assumption and decisions**

- I used HCL over json file for readability and to simplify the editing and modularity of the configuration (specially the policies).
- I removed hardcoded data (ARN, URI, etc.) where possible to decrease the maintanance complexity.

**Important to know**

- The terraform configuration won't download the [photo-recognition](https://github.com/awslabs/serverless-photo-recognition/) application.
- During the deployment, the `src/main/kotlin/com/budilov/Properties.kt` will be modified. Be careful when modifying this file manually.
- The aws elastic search domain policies can fail while the creation. Don't worry, wait a little bit and make another attempt and it will fix it. Confer https://github.com/hashicorp/terraform-provider-aws/pull/36592.
- Some useful commands will be displayed after the deployment. Take a look at it.

**Change to the source code**

With the deprecation of [`java8`](https://github.com/aws-samples/aws-redshift-udfs-textanalytics/issues/6) on aws lambda, i was obligate to switch from `java8` to `java11`. And since `java11` on the initial aws sdk version introduced a [breaking change](https://github.com/aws-samples/aws-redshift-udfs-textanalytics/issues/6), i was obligated to update the aws sdk version from `1.11` to `1.12` (based on the [last minor version](https://docs.aws.amazon.com/AWSJavaSDK/latest/javadoc/com/amazonaws/util/Base64.html)) available. And this sdk version will be deprecated after [31 December 2025](https://aws.amazon.com/blogs/developer/the-aws-sdk-for-java-1-x-is-in-maintenance-mode-effective-july-31-2024/).

## Installation

**Requirements**

To test the deployment, you will need to have [`terraform`](https://developer.hashicorp.com/terraform/tutorials/aws-get-started/install-cli) and ['aws-cli'](https://docs.aws.amazon.com/cli/latest/userguide/getting-started-install.html) in your environment. Additionally, you will need [`git`](https://git-scm.com/downloads) and [`jdk8`](https://www.oracle.com/java/technologies/downloads/#java8) to download and build the photo recognition application.

**Preparation of your IAM role**

You will need an AWS account with access to the different service.

- AWS S3
- AWS ElasticSearch
- AWS API Gateway
- AWS Lambda
- AWS Cognito Identity

In some case, you will need to check the terraform configuration to complete.


**Download the photo-recognition source code**

```
git clone https://github.com/awslabs/serverless-photo-recognition/
```

NB: It should be in the same folder that the terraform configuration. 

**Update the AWS SDK version**

In the `build.gradle` file, update the aws sdk version.

```
ext.aws_version = '1.12.787'
```

**Deployment**

```
terraform init
# Note that you will have to specify the java_home of java8 for the app building.
terraform apply
```

## Usage

After, deployment you can use the following command to test if everything is ok.
**NB**: All the commands used below will be displayed after the deployments as outputs. Each command will contains the related information needed for his execution.

*The account that we will create below is related to the photo-recognition application*

**Set your user credentials**

```
USERNAME=tester
PASSWORD=P@ssw0rd
```

**Create your account**

```
aws cognito-idp sign-up --client-id **** --username ${USERNAME} --password ${PASSWORD} --user-attributes '[ { "Name": "email", "Value": "test@user.com" }, { "Name": "phone_number", "Value": "+12485551212" }]' --region us-east-1
```

**Admin: Confirm the created account**

```
aws cognito-idp admin-confirm-sign-up --user-pool-id us-east-1_**** --username ${USERNAME} --region us-east-1
```

**Get a JWT token**

```
cat > /tmp/authflow.json <<< "{ \"AuthFlow\": \"ADMIN_NO_SRP_AUTH\", \"AuthParameters\": { \"USERNAME\": \"${USERNAME}\", \"PASSWORD\": \"${PASSWORD}\" } }"
JWT_ID_TOKEN=$(aws cognito-idp admin-initiate-auth --user-pool-id us-east-1_**** --client-id **** --cli-input-json file:///tmp/authflow.json --query AuthenticationResult.IdToken --output text --region us-east-1)
```

**Get your cognito identification**

It will be useful to securely add and remove pictures.

```
COGNITO_IDENTITY_ID=$(aws cognito-identity get-id --identity-pool-id us-east-1:**** --logins {\"cognito-idp.us-east-1.amazonaws.com/us-east-1_****\":\"${JWT_ID_TOKEN}\"} --query IdentityId --output text --region us-east-1)
```

**Upload a picture**

```
# Note the usage of your cognito identity id
aws s3 cp new-york.jpg s3://rekognition-finala/usercontent/${COGNITO_IDENTITY_ID}/ --region us-east-1
```

**NB**: You can check the log at AWS Cloudwatch for debugging.

**Remove a picture**

```
# Note the usage of your cognito id
aws s3 rm s3://rekognition-finala/usercontent/${COGNITO_IDENTITY_ID}/new-york.jpg --region us-east-1
```

**NB**: You can check the log at AWS Cloudwatch for debugging.

**Search a picture**

```
curl -X POST -H "Authorization: $(aws cognito-idp admin-initiate-auth --user-pool-id us-east-1_**** --client-id **** --cli-input-json file:///tmp/authflow.json --query AuthenticationResult.IdToken --output text --region us-east-1)" -H "search-key: building" -H "Cache-Control: no-cache" "https://****.execute-api.us-east-1.amazonaws.com/prod/picture/search/"
```

**NB**: You can check the log at AWS Cloudwatch and AWS API Gateway for debugging.

You can make a simple check with.

```
curl -I -X OPTIONS https://****.execute-api.us-east-1.amazonaws.com/prod/picture
```

**Update the jar file**

If you need to update the java code without rebuild the infrastructure, you can use the following command.

```
aws lambda update-function-code --region us-east-1 --function-name rekognition-search-picture-finala --zip-file fileb://./serverless-photo-recognition/build/libs/rekognition-rest-1.0-SNAPSHOT.jar --region us-east-1
```

### The Core Team

Brady Fomegne


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
