resource "aws_api_gateway_rest_api" "example" {
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
            uri                 = "arn:aws:apigateway:${local.region}:lambda:path/2015-03-31/functions/${aws_lambda_function.rek_search.arn}/invocations",
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
