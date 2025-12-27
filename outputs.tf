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
    "User Pool"     = aws_cognito_user_pool.pool.id
    "Identity Pool" = aws_cognito_identity_pool.main.id
    "Client"        = aws_cognito_user_pool_client.client.id
  }
}

output "lambda_functions" {
  description = "Lambda functions"
  value = {
    "Add"    = local.function_rek_add_handler
    "Remove" = local.function_rek_del_handler
    "Search" = local.function_rek_search_handler
  }
}

output "auth_commands" {
  description = "Set of commands for the authentification"
  value = {
    sign_up                 = <<EOT
    aws cognito-idp sign-up --client-id ${aws_cognito_user_pool_client.client.id} --username $${USERNAME} --password $${PASSWORD} --user-attributes '[ { "Name": "email", "Value": "test@user.com" }, { "Name": "phone_number", "Value": "+12485551212" }]' --region ${local.region}
    EOT
    confirm_user            = "aws cognito-idp admin-confirm-sign-up --user-pool-id ${aws_cognito_user_pool.pool.id} --username $${USERNAME} --region ${local.region}"
    get_jwt_token           = <<EOT
  ## begin auth flow
  cat > /tmp/authflow.json <<< "{ \"AuthFlow\": \"ADMIN_NO_SRP_AUTH\", \"AuthParameters\": { \"USERNAME\": \"$${USERNAME}\", \"PASSWORD\": \"$${PASSWORD}\" } }"
  aws cognito-idp admin-initiate-auth --user-pool-id ${aws_cognito_user_pool.pool.id} --client-id ${aws_cognito_user_pool_client.client.id} --cli-input-json file:///tmp/authflow.json --query AuthenticationResult.IdToken --output text --region ${local.region}
  EOT
    get_cognito_identity_id = "aws cognito-identity get-id --identity-pool-id ${aws_cognito_identity_pool.main.id} --logins {\"cognito-idp.${local.region}.amazonaws.com/${aws_cognito_user_pool.pool.id}\":\"$${JWT_ID_TOKEN}\"} --query IdentityId --output text --region ${local.region}"
  }
}

output "picture_commamds" {
  description = "Set of command to upload, search and delete pictures"
  value = {
    upload_picture = "aws s3 cp new-york.jpg s3://${local.bucket_name}/usercontent/$${COGNITO_IDENTITY_ID}/ --region ${local.region}"
    search_picture = <<EOT
    curl -X POST -H "Authorization: $(aws cognito-idp admin-initiate-auth --user-pool-id ${aws_cognito_user_pool.pool.id} --client-id ${aws_cognito_user_pool_client.client.id} --cli-input-json file:///tmp/authflow.json --query AuthenticationResult.IdToken --output text --region ${local.region})" -H "search-key: building" -H "Cache-Control: no-cache" "${aws_api_gateway_stage.prod.invoke_url}/picture/search/"
    EOT
    remove_picture = "aws s3 rm s3://${local.bucket_name}/usercontent/$${COGNITO_IDENTITY_ID}/new-york.jpg --region ${local.region}"
  }
}

output "redeploy_function" {
  description = "Want to redeploy the Search Lambda function? Run the following command"
  value       = "aws lambda update-function-code --region ${local.region} --function-name ${local.function_rek_search} --zip-file fileb://${local.jar_location} --region ${local.region}"
}
