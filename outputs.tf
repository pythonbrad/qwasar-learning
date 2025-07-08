output "els_domain" {
  description = "AWS ES domain"
  value       = aws_elasticsearch_domain.es.endpoint
}

output "api_gateway" {
  value = aws_api_gateway_stage.prod.invoke_url
}
