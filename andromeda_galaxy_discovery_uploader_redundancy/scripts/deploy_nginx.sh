#!/usr/bin/sh

set -ex

# Deploy nginx
sudo useradd -m nginx

sudo yum install -y nginx

sudo cp /tmp/nginx.conf /etc/nginx/conf.d/s3-proxy.conf
sudo systemctl start nginx
sudo systemctl enable nginx
