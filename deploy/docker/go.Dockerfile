FROM golang:1.22 as build
WORKDIR /src
COPY go/gateway /src
RUN go mod tidy && CGO_ENABLED=0 go build -o /out/gateway
FROM gcr.io/distroless/base-debian12
COPY --from=build /out/gateway /gateway
EXPOSE 8080
ENTRYPOINT ["/gateway"]