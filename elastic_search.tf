# Setup Elasticsearch
resource "aws_elasticsearch_domain" "es" {
  domain_name           = local.es_domain_name
  elasticsearch_version = "6.8"

  cluster_config {
    instance_type  = "m5.large.elasticsearch"
    instance_count = 1
  }

  ebs_options {
    ebs_enabled = true
    volume_type = "standard"
    volume_size = 10
  }
}

resource "aws_elasticsearch_domain_policy" "main" {
  domain_name = aws_elasticsearch_domain.es.domain_name

  access_policies = jsonencode(
    {
      Version = "2012-10-17",
      Statement = [
        {
          Effect = "Allow",
          Principal = {
            AWS = aws_iam_role.main.arn
          },
          Action   = "es:*",
          Resource = "${aws_elasticsearch_domain.es.arn}/*"
        },
        {
          Sid    = "",
          Effect = "Allow",
          Principal = {
            AWS = "*"
          },
          Action   = "es:*",
          Resource = "${aws_elasticsearch_domain.es.arn}/*",
          Condition = {
            IpAddress = {
              "aws:SourceIp" = "127.0.0.1/32"
              # "aws:SourceIp" = "EXTERNAL_IP_ADDRESS_REPLACE_ME"
            }
          }
        }
      ]
  })
}
