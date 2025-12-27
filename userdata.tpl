#!/bin/bash 
sudo useradd -m nginx
sudo yum install -y nginx
sudo systemctl enable nginx
sudo systemctl start nginx
