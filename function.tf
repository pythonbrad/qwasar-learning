# Create the user pool
resource "aws_cognito_user_pool" "pool" {
  name                     = local.root_name
  auto_verified_attributes = ["email"]

  schema {
    name                = "email"
    required            = true
    attribute_data_type = "String"
  }

  password_policy {
    minimum_length    = 8
    require_uppercase = true
    require_lowercase = true
    require_numbers   = true
    require_symbols   = true
  }
}

# Create the user pool client
resource "aws_cognito_user_pool_client" "client" {
  name                = "client"
  user_pool_id        = aws_cognito_user_pool.pool.id
  generate_secret     = false
  explicit_auth_flows = ["ADMIN_NO_SRP_AUTH"]
}

# Create a Cognito Identity and Set roles
resource "aws_cognito_identity_pool" "main" {
  identity_pool_name               = local.root_name
  allow_unauthenticated_identities = true

  # Add the user pool and user pool client id to the identity pool
  cognito_identity_providers {
    provider_name = "cognito-idp.${local.region}.amazonaws.com/${aws_cognito_user_pool.pool.id}"
    client_id     = aws_cognito_user_pool_client.client.id
  }
}

# Update cognito identity with the roles
resource "aws_cognito_identity_pool_roles_attachment" "main" {
  identity_pool_id = aws_cognito_identity_pool.main.id

  roles = {
    authenticated   = aws_iam_role.authenticated.arn
    unauthenticated = aws_iam_role.unauthenticated.arn
  }

  depends_on = [aws_iam_role.authenticated, aws_iam_role.unauthenticated]
}

# Create an IAM role for unauthenticated users
resource "aws_iam_role" "unauthenticated" {
  name = "${local.root_name}-unauthenticated-role"

  assume_role_policy = jsonencode({
    Version = "2012-10-17"
    Statement = [
      {
        Action = "sts:AssumeRoleWithWebIdentity"
        Effect = "Allow"
        Principal = {
          Federated = "cognito-identity.amazonaws.com"
        }
        Condition = {
          StringEquals = {
            "cognito-identity.amazonaws.com:aud" = "${aws_cognito_identity_pool.main.id}"
          }
          "ForAnyValue:StringLike" = {
            "cognito-identity.amazonaws.com:amr" = "unauthenticated"
          }
        }
      }
    ]
  })
}

resource "aws_iam_role_policy" "unauthenticated_policy" {
  name = "CognitoPolicy"
  role = aws_iam_role.unauthenticated

  policy = jsonencode({
    Version = "2012-10-17",
    Statement = [
      {
        Effect = "Allow",
        Action = [
          "mobileanalytics:PutEvents",
          "cognito-sync:*"
        ],
        Resource = [
          "*"
        ]
      }
    ]
  })
}

# Create an IAM role for authenticated users
resource "aws_iam_role" "authenticated" {
  name = "${local.root_name}-authenticated-role"

  assume_role_policy = jsonencode({
    Version = "2012-10-17"
    Statement = [
      {
        Action = "sts:AssumeRoleWithWebIdentity"
        Effect = "Allow"
        Principal = {
          Federated = "cognito-identity.amazonaws.com"
        }
        Condition = {
          StringEquals = {
            "cognito-identity.amazonaws.com:aud" = "${aws_cognito_identity_pool.main.id}"
          }
          "ForAnyValue:StringLike" = {
            "cognito-identity.amazonaws.com:amr" = "authenticated"
          }
        }
      }
    ]
  })
}

resource "aws_iam_role_policy" "authenticated_policy" {
  name = "CognitoPolicy"
  role = aws_iam_role.authenticated

  policy = jsonencode({
    Version = "2012-10-17",
    Statement = [
      {
        Effect = "Allow",
        Action = [
          "mobileanalytics:PutEvents",
          "cognito-sync:*",
          "cognito-identity:*"
        ],
        Resource = [
          "*"
        ]
      },
      {
        Effect = "Allow",
        Action = [
          "dynamodb:GetItem",
          "dynamodb:BatchGetItem",
          "dynamodb:Query",
          "dynamodb:PutItem",
          "dynamodb:UpdateItem",
          "dynamodb:DeleteItem"
        ],
        Resource = [
          "arn:aws:dynamodb:${local.region}:${local.account_number}:table/${local.table_name}"
        ],
        Condition = {
          "ForAllValues:StringEquals" = {
            "dynamodb:LeadingKeys" = [
              "$${cognito-identity.amazonaws.com:sub}"
            ]
          }
        }
      },
      {
        Action = [
          "s3:GetObject",
          "s3:PutObject",
          "s3:DeleteObject"
        ],
        Effect = "Allow",
        Resource = [
          "arn:aws:s3:::${local.bucket_name}/usercontent/$${cognito-identity.amazonaws.com:sub}/*"
        ]
      }
    ]
  })
}

# Create IAM roles
resource "aws_iam_role" "main" {
  name = local.role_name
  assume_role_policy = jsonencode({
    Version = "2012-10-17",
    Statement = [
      {
        Effect = "Allow",
        Principal = {
          Service = "lambda.amazonaws.com"
        },
        Action = "sts:AssumeRole"
      }
    ]
  })
}

resource "aws_iam_policy_attachment" "one" {
  name       = "${local.role_name}-amazon-es-fullaccess"
  roles      = [aws_iam_role.main.name]
  policy_arn = "arn:aws:iam::aws:policy/AmazonESFullAccess"
}

resource "aws_iam_policy_attachment" "two" {
  name       = "${local.role_name}-amazon-rekognition-fullaccess"
  roles      = [aws_iam_role.main]
  policy_arn = "arn:aws:iam::aws:policy/AmazonRekognitionFullAccess"
}

resource "aws_iam_policy_attachment" "three" {
  name       = "${local.role_name}-amazon-s3-fullaccess"
  roles      = [aws_iam_role.main]
  policy_arn = "arn:aws:iam::aws:policy/AmazonS3FullAccess"
}

resource "aws_iam_policy_attachment" "four" {
  name       = "${local.role_name}-cloudwatch-fullaccess"
  roles      = [aws_iam_role.main]
  policy_arn = "arn:aws:iam::aws:policy/CloudWatchLogsFullAccess"
}

# Create the photos bucket
resource "aws_s3_bucket" "main" {
  bucket = local.bucket_name
}

resource "aws_s3_bucket_cors_configuration" "main" {
  bucket = aws_s3_bucket.main.id

  cors_rule {
    allowed_origins = ["*"]
    allowed_headers = ["*"]
    allowed_methods = [
      "PUT",
      "POST",
      "DELETE",
      "HEAD",
      "GET"
    ]
    max_age_seconds = 3000
    expose_headers = [
      "x-amz-server-side-encryption",
      "ETag"
    ]
  }
}

# resource "aws_s3_bucket_policy" "allow_access" {
#   bucket = aws_s3_bucket.main.id
#   policy = jsonencode({
#     Version = "2012-10-17",
#     Statement = [{
#       Sid       = "PublicReadForGetBucketObjects",
#       Effect    = "Allow",
#       Principal = "*",
#       Action    = ["s3:GetObject"],
#       Resource  = ["${aws_s3_bucket.main.arn}/*"
#       ]
#       }
#     ]
#   })
# }

# Build and deploy Lambda functions
# Update the application properties data
data "local_file" "properties" {
  filename = "${path.root}/src/main/kotlin/com/budilov/Properties.kt"
}

resource "local_file" "properties" {
  content = replace(
    replace(
      replace(
        replace(
          replace(
            replace(
              data.local_file.properties.content,
            "REGION_REPLACE_ME", local.region),
          "ACCOUNT_REPLACE_ME", local.account_number),
        "COGNITO_POOL_ID_REPLACE_ME", aws_cognito_identity_pool.main.id),
      "USER_POOL_ID_REPLACE_ME", aws_cognito_user_pool.pool.id),
    "ES_SERVICE_URL_REPLACE_ME", aws_elasticsearch_domain.es.id),
  "BUCKET_REPLACE_ME", aws_s3_bucket.main.id)
  filename = data.local_file.properties.filename

  depends_on = [aws_elasticsearch_domain.es]
}

# Build the .jar file
resource "null_resource" "build" {
  provisioner "local-exec" {
    command = "chmod 755 ${path.root}/gradlew && ${path.root}/gradlew build"
  }
}

# Create lambda functions and deploy
resource "aws_lambda_function" "rek_add" {
  function_name = local.function_rek_add
  filename      = local.jar_location
  role          = aws_iam_role.main.arn
  handler       = local.function_rek_add_handler
  runtime       = "java8"
  memory_size   = 192
  timeout       = 20
}

resource "aws_lambda_function" "rek_del" {
  function_name = local.function_rek_del
  filename      = local.jar_location
  role          = aws_iam_role.main.arn
  handler       = local.function_rek_del_handler
  runtime       = "java8"
  memory_size   = 192
  timeout       = 20
}

resource "aws_lambda_function" "rek_search" {
  function_name = local.function_rek_search
  filename      = local.jar_location
  role          = aws_iam_role.main.arn
  handler       = local.function_rek_search_handler
  runtime       = "java8"
  memory_size   = 192
  timeout       = 20
}

# Setup the S3 events
# Adding the ADD event Lambda permissions
resource "aws_lambda_permission" "rek_add" {
  function_name  = aws_lambda_function.rek_add.function_name
  statement_id   = "${local.root_name}-rekognition"
  action         = "lambda:InvokeFunction"
  principal      = "s3.amazonaws.com"
  source_arn     = aws_s3_bucket.main.arn
  source_account = local.account_number
}

# Adding the DEL event Lambda permissions
resource "aws_lambda_permission" "rek_del" {
  function_name  = aws_lambda_function.rek_del.function_name
  statement_id   = "${local.root_name}-rekognition"
  action         = "lambda:InvokeFunction"
  principal      = "s3.amazonaws.com"
  source_arn     = aws_s3_bucket.main.arn
  source_account = local.account_number
}

# Creating the s3 notification events
resource "aws_s3_bucket_notification" "main" {
  bucket = aws_s3_bucket.main.id

  lambda_function {
    lambda_function_arn = aws_lambda_function.rek_add.arn
    events              = ["s3:ObjectCreated:*"]
  }

  lambda_function {
    lambda_function_arn = aws_lambda_function.rek_del.arn
    events              = ["s3:ObjectRemoved:*"]
  }

  depends_on = [
    aws_lambda_permission.rek_add,
    aws_lambda_permission.rek_del,
  ]
}
