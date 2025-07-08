# Importing the swagger template
resource "aws_api_gateway_rest_api" "api" {
  body = jsonencode({
    swagger = "2.0",
    info = {
      version = "2017-01-12T02:52:43Z",
      title   = local.api_gateway_name
    },
    host     = "e9djdv2xjb.execute-api.${local.region}.amazonaws.com",
    basePath = "/prd",
    schemes = [
      "https"
    ],
    paths = {
      "/picture" = {
        options = {
          consumes = [
            "application/json"
          ],
          produces = [
            "application/json"
          ],
          responses = {
            "200" = {
              description = "200 response",
              schema = {
                "$ref" = "#/definitions/Empty"
              },
              headers = {
                "Access-Control-Allow-Origin" = {
                  type = "string"
                },
                "Access-Control-Allow-Methods" = {
                  type = "string"
                },
                "Access-Control-Allow-Headers" = {
                  type = "string"
                }
              }
            }
          },
          "x-amazon-apigateway-integration" = {
            responses = {
              default = {
                statusCode = "200",
                responseParameters = {
                  "method.response.header.Access-Control-Allow-Methods" = "'OPTIONS'",
                  "method.response.header.Access-Control-Allow-Headers" = "'Content-Type,X-Amz-Date,Authorization,X-Api-Key,X-Amz-Security-Token'",
                  "method.response.header.Access-Control-Allow-Origin"  = "'*'"
                }
              }
            },
            requestTemplates = {
              "application/json" = "{\"statusCode\": 200}"
            },
            passthroughBehavior = "when_no_match",
            type                = "mock"
          }
        }
      },
      "/picture/search" = {
        post = {
          produces = [
            "application/json"
          ],
          responses = {
            "200" = {
              description = "200 response",
              schema = {
                "$ref" = "#/definitions/Empty"
              },
              headers = {
                "Access-Control-Allow-Origin" = {
                  type = "string"
                }
              }
            }
          },
          security = [
            {
              "${local.cognito_pool_name}" = []
            }
          ],
          "x-amazon-apigateway-integration" = {
            responses = {
              default = {
                statusCode = "200",
                responseParameters = {
                  "method.response.header.Access-Control-Allow-Origin" = "'*'"
                }
              }
            },
            uri                 = aws_lambda_function.rek_search.invoke_arn,
            passthroughBehavior = "when_no_match",
            httpMethod          = "POST",
            contentHandling     = "CONVERT_TO_TEXT",
            type                = "aws_proxy"
          }
        },
        options = {
          consumes = [
            "application/json"
          ],
          produces = [
            "application/json"
          ],
          responses = {
            "200" = {
              description = "200 response",
              schema = {
                "$ref" = "#/definitions/Empty"
              },
              headers = {
                "Access-Control-Allow-Origin" = {
                  type = "string"
                },
                "Access-Control-Allow-Methods" = {
                  type = "string"
                },
                "Access-Control-Allow-Headers" = {
                  type = "string"
                }
              }
            }
          },
          "x-amazon-apigateway-integration" = {
            responses = {
              default = {
                statusCode = "200",
                responseParameters = {
                  "method.response.header.Access-Control-Allow-Methods" = "'POST,OPTIONS'",
                  "method.response.header.Access-Control-Allow-Headers" = "'Content-Type,X-Amz-Date,Authorization,X-Api-Key,X-Amz-Security-Token'",
                  "method.response.header.Access-Control-Allow-Origin"  = "'*'"
                }
              }
            },
            requestTemplates = {
              "application/json" = "{\"statusCode\": 200}"
            },
            passthroughBehavior = "when_no_match",
            type                = "mock"
          }
        }
      }
    },
    securityDefinitions = {
      "${local.cognito_pool_name}" = {
        type                           = "apiKey",
        name                           = "Authorization",
        in                             = "header",
        "x-amazon-apigateway-authtype" = "cognito_user_pools",
        "x-amazon-apigateway-authorizer" = {
          providerARNs = [
            aws_cognito_user_pool.pool.arn
          ],
          type = "cognito_user_pools"
        }
      }
    },
    definitions = {
      Empty = {
        type  = "object",
        title = "Empty Schema"
      }
    },
    "x-amazon-apigateway-binary-media-types" = [
      "image/png",
      "image/jpg"
    ]
  })

  name = "example"
}

# Deploying the gateway 
resource "aws_api_gateway_deployment" "api" {
  rest_api_id = aws_api_gateway_rest_api.api.id
}
# Deploy to prod stage

resource "aws_api_gateway_stage" "prod" {
  deployment_id = aws_api_gateway_deployment.api.id
  rest_api_id   = aws_api_gateway_rest_api.api.id
  stage_name    = "prod"
}

# Grant the API Gateway access to invoke the Lambda function
resource "aws_lambda_permission" "rek_api" {
  function_name = aws_lambda_function.rek_add.function_name
  statement_id  = "${local.root_name}-apigateway-prod"
  action        = "lambda:InvokeFunction"
  principal     = "apigateway.amazonaws.com"
  source_arn    = "arn:aws:execute-api:${local.region}:${local.account_number}:${aws_api_gateway_rest_api.api.id}/prod/POST/picture/search"
}
