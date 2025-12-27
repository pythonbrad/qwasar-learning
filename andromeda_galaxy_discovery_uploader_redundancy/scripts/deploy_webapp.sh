#!/usr/bin/sh

set -ex

# Deploy the app
sudo yum install -y git
curl -LsSf https://astral.sh/uv/install.sh | sh
git clone https://github.com/pythonbrad/andromeda-pixel

mkdir ~/.aws && cp /tmp/credentials ~/.aws/credentials
sudo rm /tmp/credentials

cd andromeda-pixel
mkdir instance && cp /tmp/config.py instance
ln -s /home/ec2-user/.local/bin/uv uv
./uv sync --no-dev
./uv pip install gunicorn greenlet gevent
./uv run flask --app flaskr init-db

sudo cp /tmp/webapp.service /etc/systemd/system/webapp.service
sudo systemctl start webapp
sudo systemctl enable webapp
