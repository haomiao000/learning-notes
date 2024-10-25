module server1

go 1.22.3

replace grpc_gen => ../proto

replace trace => ../trace

replace interceptor => ../interceptor

require (
	github.com/grpc-ecosystem/go-grpc-middleware v1.4.0
	google.golang.org/grpc v1.67.1
	grpc_gen v0.0.0-00010101000000-000000000000
	interceptor v0.0.0-00010101000000-000000000000
	trace v0.0.0-00010101000000-000000000000
)

require (
	github.com/opentracing/opentracing-go v1.2.0 // indirect
	github.com/pkg/errors v0.9.1 // indirect
	github.com/uber/jaeger-client-go v2.30.0+incompatible // indirect
	github.com/uber/jaeger-lib v2.4.1+incompatible // indirect
	go.uber.org/atomic v1.11.0 // indirect
	golang.org/x/net v0.28.0 // indirect
	golang.org/x/sys v0.24.0 // indirect
	golang.org/x/text v0.17.0 // indirect
	google.golang.org/genproto/googleapis/rpc v0.0.0-20240814211410-ddb44dafa142 // indirect
	google.golang.org/protobuf v1.35.1 // indirect
	gopkg.in/yaml.v3 v3.0.1 // indirect
)
