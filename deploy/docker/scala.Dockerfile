FROM eclipse-temurin:21-jdk
WORKDIR /app
COPY scala/assignment-service /app
RUN curl -s https://get.sdkman.io | bash || true
# For brevity: assume sbt available in image or mounted in CI
CMD ["java","-version"]