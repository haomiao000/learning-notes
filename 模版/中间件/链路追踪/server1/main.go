package main

import (
	"context"
	"fmt"
	"grpc_gen/AddServ"
	"interceptor"
	"net"
	"trace"
	"grpc_gen/MultiplyServ"
	grpcMiddleware "github.com/grpc-ecosystem/go-grpc-middleware"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

type AddImpl struct {
	MultiplyServ MultiplyServ.MultiplyServiceClient
	AddServ.UnimplementedAddServiceServer
}

func InitMultiplyServ() MultiplyServ.MultiplyServiceClient {
	tracer , closer := trace.NewTracer("Multi")
	defer closer.Close()
	conn, err := grpc.Dial(
        "localhost:50052",
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
	c := MultiplyServ.NewMultiplyServiceClient(conn)
	return c
}

func (s *AddImpl) Add(ctx context.Context , req *AddServ.AddRequest) (*AddServ.AddResponse , error) {
	var resp = new(AddServ.AddResponse)
	fmt.Println(req.A)
	fmt.Println(req.B)
	mul , err := s.MultiplyServ.Multiply(ctx , &MultiplyServ.MultiplyRequest{
		A: req.A,
		B: req.B,
	})
	if err != nil {
		return nil , err
	}
	resp.Result = req.A + req.B + mul.Result
	return resp , nil
}

func (s *AddImpl) AddTwice(ctx context.Context , req *AddServ.AddTwiceRequest) (*AddServ.AddTwiceResponse , error) {
	var resp = new(AddServ.AddTwiceResponse)
	fmt.Println(req.A)
	fmt.Println(req.B)
	resp.Result = (req.A + req.B) * 2
	return resp , nil
}


func main() {
	MultiplyServer := InitMultiplyServ()
	tracer, closer := trace.NewTracer("ADD")
	grpcServer := grpc.NewServer(grpc.UnaryInterceptor(
		grpcMiddleware.ChainUnaryServer(
			interceptor.ServerInterceptor(tracer),
		),
	))
	defer closer.Close()
	impl := &AddImpl{
		MultiplyServ: MultiplyServer,
	}
	AddServ.RegisterAddServiceServer(grpcServer , impl)
	listener, err := net.Listen("tcp", ":50051")
	if err != nil {
		fmt.Printf("Failed To Listen On Addr: %v", err)
	}
	if err := grpcServer.Serve(listener); err != nil {
		fmt.Printf("Failed To Serve GRPC Server: %v", err)
	}
}