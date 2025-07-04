# Welcome to Andromeda Galaxy Discovery Uploader Two
***

## Task
The Task consisted to deploy a rail application on AWS Elantic BeansTalk using AWS codePipeline and GitHub.

## Description

**Github**

The first step consists to push the rail application source code on github.

```
git init .
git remote add origin <>
git commit -m init
git push origin main
```

Since the rail application was using a github action to automate the test and lint checking, I make sure all the tests has passed successfully. The reason is to avoid to deploy a non production ready code.
To facilitate the deployment, i adjusted the environement variable names for the production enviroment.

**AWS Elastic Beanstack**

Before proceed with the deployment, I created an AWS Elastic Beanstack application and his environment. Since I am deploying a ruby applcation, I selected ruby as platform. Also, I selected the sample application code to be sure everything is ready before the deployment. I configured a postgres database, and setting the environment variable, `SECRET_KEY_BASE` was enough.

**AWS CodePipeline**

On AWS CodePipeline, I built a custom pipeline with Github (via Github App) as provider. To avoid a potential error during the getting of the source code, I make sure to give an access at my github repo to AWS.
At the level of the deploy stage, I selected the application that I created.
Stangely, I was in the need to complete the permission policies of the generated pipeline service role. It helped me to fix the issue of missing permissions during the deployment.

**AWS Certificate Manager**

At this point, I was already holding a domain name and using it for a professional purpose. Then, I created a subdomain for my qwasar learning.
I requested a ACME public certificate on AWS certificate manager. It tooks 26 hours, 72 hours was the limit, then i think is ok.

**AWS Load Balancer**

With the SSL certificate that i created before, I created a load balancer to handle the https to http interface with my application.
I also  configurated the security group to allow https traffic with my load balancer.

**AWS Route 53**

To end, i connected my load balancer to my domain name.

## Installation
No installation is needed.

## Usage

**Test the application**

You can access the application at https://andromeda-two.qwasar.fodydev.org.

**SSL certificate**

To test my SSL certificate, you can use https://www.ssl.org/.

### The Core Team

Brady Fomegne


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
