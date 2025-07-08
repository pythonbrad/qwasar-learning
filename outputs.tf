output "els_domain" {
  description = "AWS ES domain"
  value       = aws_elasticsearch_domain.es.endpoint
}

output "api_gateway" {
  value = aws_api_gateway_stage.prod.invoke_url
}

output "cognito_ids" {
  description = "Cognito IDs"
  value = {
    "User Pool" = aws_cognito_user_pool.pool.id
    "Identity Pool" = aws_cognito_identity_pool.main.id
    "Client" = aws_cognito_user_pool_client.client.id
  }
}

output "lambda_functions" {
  description = "Lambda functions"
  value = {
    "Add" = local.function_rek_add_handler
    "Remove" = local.function_rek_del_handler
    "Search" = local.function_rek_search_handler
  }
}

output "upload_picture" {
  description = "Upload a picture"
  value = "aws s3 cp new-york.jpg s3://${local.bucket_name}/usercontent/${aws_cognito_identity_pool.main.id}/ --region ${local.region}"
}

output "search_picture" {
  description = "Search a picture"
  value = "curl -X POST -H \"Authorization: \\$(aws cognito-idp admin-initiate-auth  --user-pool-id ${aws_cognito_user_pool.pool.id} --client-id ${aws_cognito_user_pool_client.client.id} --cli-input-json file:///tmp/authflow.json --query AuthenticationResult.IdToken --output text --region ${local.region})\" -H \"search-key: building\" -H \"Cache-Control: no-cache\" \"${aws_api_gateway_stage.prod.invoke_url}/picture/search/\""
}

output "remove_picture" {
  description = "Remove a picture"
  value = "aws s3 rm s3://${local.bucket_name}/usercontent/${aws_cognito_identity_pool.main.id}/new-york.jpg --region ${local.region} "
}

output "redeploy_function" {
  description = "Want to redeploy the Search Lambda function? Run the following command"
  value = "aws lambda update-function-code --region ${local.region} --function-name ${local.function_rek_search} --zip-file fileb://${local.jar_location} --region ${local.region}"
}
