output "els_domain" {
  description = "AWS ES domain"
  value       = aws_elasticsearch_domain.es.endpoint
}
