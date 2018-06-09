#!/bin/bash

set -e

BUILD_TAG=${BUILD_NUMBER:-latest}
AWS_ECR_URL=$AWS_ACCOUNT.dkr.ecr.$AWS_REGION.amazonaws.com/$REPO_SLUG
SOURCE_VERSION=${CODEBUILD_SOURCE_VERSION:-latest}

should_deploy_branch() {
  if [[ "$CODEBUILD_BUILD_SUCCEEDING" != "1" ]]; then
    return 1
  fi

  if [[ "$DEPLOY_BUILD" == "1" ]]; then
    return 0
  fi

  return 1
}

tag_and_push() {
  echo "Tagging Docker Image: '$1' ..."
  docker tag $REPO_SLUG:latest $AWS_ECR_URL:$1

  echo "Pushing Docker Image: '$1' ..."
  docker push $AWS_ECR_URL:$1
}

if should_deploy_branch $BUILD_BRANCH; then
  echo "Logging into ECR..."
  `aws ecr get-login --no-include-email --region $AWS_REGION`

  echo "Building Docker Image..."
  docker build -t $REPO_SLUG .

  tag_and_push $BUILD_TAG

  if [ "$BUILD_TAG" != "latest" ]; then
    tag_and_push "latest"
  fi

  if [ ! -z "$BUILD_RELEASE" ]; then
    tag_and_push $BUILD_RELEASE
  fi

  if [ "$SOURCE_VERSION" != "latest" ]; then
    tag_and_push $SOURCE_VERSION
  fi

  if [ "$BUILD_TAG" != "latest" ]; then
    tag_and_push "latest"
  fi

  echo "Finished!"
else
  echo "Not deploying branch: $BUILD_BRANCH"
fi