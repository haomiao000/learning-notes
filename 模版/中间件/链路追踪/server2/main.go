package main

import (
	"context"
	"fmt"
	"grpc_gen/MultiplyServ"
	"grpc_gen/AddServ"
	"net"
	"trace"
	"interceptor"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	grpcMiddleware "github.com/grpc-ecosystem/go-grpc-middleware"
)

type MultiplyImpl struct {
	AddServ AddServ.AddServiceClient
	MultiplyServ.UnimplementedMultiplyServiceServer
}

func InitAddServ() AddServ.AddServiceClient {
	tracer , closer := trace.NewTracer("AddServer")
	defer closer.Close()
	conn, err := grpc.Dial(
        "localhost:50051",
        grpc.WithUnaryInterceptor(
            grpcMiddleware.ChainUnaryClient(
                interceptor.ClientInterceptor(tracer),
            ),
        ),
        grpc.WithTransportCredentials(insecure.NewCredentials()), 
    )
	if err != nil {
		panic(err)
	}
	c := AddServ.NewAddServiceClient(conn)
	return c
}

func (s *MultiplyImpl) Multiply(ctx context.Context , req *MultiplyServ.MultiplyRequest) (*MultiplyServ.MultiplyResponse , error) {
	var resp = new(MultiplyServ.MultiplyResponse)
	fmt.Println(req.A)
	fmt.Println(req.B)
	num , _ := s.AddServ.AddTwice(ctx , &AddServ.AddTwiceRequest{
		A: req.A,
		B: req.B,
	})
	resp.Result = req.A * req.B + num.Result
	return resp , nil
}

func main() {
	AddServer := InitAddServ()
	tracer, closer := trace.NewTracer("Multiply")
	grpcServer := grpc.NewServer(grpc.UnaryInterceptor(
		grpcMiddleware.ChainUnaryServer(
			interceptor.ServerInterceptor(tracer),
		),
	))
	defer closer.Close()
	impl := &MultiplyImpl{
		AddServ: AddServer,
	}
	MultiplyServ.RegisterMultiplyServiceServer(grpcServer , impl)
	listener, err := net.Listen("tcp", ":50052")
	if err != nil {
		fmt.Printf("Failed To Listen On Addr: %v", err)
	}
	if err := grpcServer.Serve(listener); err != nil {
		fmt.Printf("Failed To Serve GRPC Server: %v", err)
	}
}