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
  name            = "client"
  user_pool_id    = aws_cognito_user_pool.pool.id
  generate_secret = false
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
    "Version" = "2012-10-17",
    "Statement" = [
      {
        "Effect" = "Allow",
        "Action" = [
          "mobileanalytics:PutEvents",
          "cognito-sync:*"
        ],
        "Resource" = [
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
    "Version" = "2012-10-17",
    "Statement" = [
      {
        "Effect" = "Allow",
        "Action" = [
          "mobileanalytics:PutEvents",
          "cognito-sync:*",
          "cognito-identity:*"
        ],
        "Resource" = [
          "*"
        ]
      },
      {
        "Effect" = "Allow",
        "Action" = [
          "dynamodb:GetItem",
          "dynamodb:BatchGetItem",
          "dynamodb:Query",
          "dynamodb:PutItem",
          "dynamodb:UpdateItem",
          "dynamodb:DeleteItem"
        ],
        "Resource" = [
          "arn:aws:dynamodb:${local.region}:${local.account_number}:table/${local.table_name}"
        ],
        "Condition" = {
          "ForAllValues:StringEquals" = {
            "dynamodb:LeadingKeys" = [
              "$${cognito-identity.amazonaws.com:sub}"
            ]
          }
        }
      },
      {
        "Action" = [
          "s3:GetObject",
          "s3:PutObject",
          "s3:DeleteObject"
        ],
        "Effect" = "Allow",
        "Resource" = [
          "arn:aws:s3:::${local.bucket_name}/usercontent/$${cognito-identity.amazonaws.com:sub}/*"
        ]
      }
    ]
  })
}

# Create the s3 bucket
resource "aws_s3_bucket" "main" {
  bucket = local.bucket_name

}

resource "aws_s3_bucket_policy" "allow_access" {
  bucket = aws_s3_bucket.main.id
  policy = jsonencode({
    "Version" = "2012-10-17",
    "Statement" = [{
      "Sid"       = "PublicReadForGetBucketObjects",
      "Effect"    = "Allow",
      "Principal" = "*",
      "Action"    = ["s3:GetObject"],
      "Resource" = ["${aws_s3_bucket.main.arn}/*"
      ]
      }
    ]
  })
}

