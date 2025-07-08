data "aws_caller_identity" "current" {}

locals {
  app_root = "${path.root}/serverless-photo-recognition"

  root_name         = var.root_name
  bucket_name       = "rekognition-${local.root_name}"
  region            = "us-east-1"
  account_number    = data.aws_caller_identity.current.account_id
  cognito_pool_name = "${local.root_name}rek"
  api_gateway_name  = "cognitorek-${local.root_name}"
  table_name        = ""

  # Lambda
  jar_location                = "${local.app_root}/build/libs/rekognition-rest-1.0-SNAPSHOT.jar"
  function_rek_search         = "rekognition-search-picture-${local.root_name}"
  function_rek_add            = "rekognition-add-picture-${local.root_name}"
  function_rek_del            = "rekognition-del-picture-${local.root_name}"
  function_rek_search_handler = "com.budilov.searchphotoshandler"
  function_rek_add_handler    = "com.budilov.addphotolambda"
  function_rek_del_handler    = "com.budilov.removephotolambda"

  # IAM
  role_name = "lambda-to-es-rek-s3-${local.root_name}"

  # ES
  es_domain_name = "rekognition-${local.root_name}"
}
