package main

import (
    "context"
    "fmt"
    "log"
	grpcMiddleware "github.com/grpc-ecosystem/go-grpc-middleware"
    AddServ "grpc_gen/AddServ"
	// MultiplyServ "grpc_gen/MultiplyServ"
    "google.golang.org/grpc"
	"trace"
	"interceptor"
	"google.golang.org/grpc/credentials/insecure"
)

func main() {
	tracer, closer := trace.NewTracer("start")
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
        log.Fatalf("did not connect: %v", err)
    }
    defer closer.Close()
	// tracer, closer := trace.NewTracer("start")
	// grpcServer := grpc.NewServer(grpc.UnaryInterceptor(
	// 	grpcMiddleware.ChainUnaryServer(
	// 		interceptor.ServerInterceptor(tracer),
	// 	),
	// ))

    client := AddServ.NewAddServiceClient(conn)
    req := &AddServ.AddRequest{
        A: 5,
        B: 3,
    }

    resp, err := client.Add(context.Background(), req)
    if err != nil {
        log.Fatalf("Error calling Add service: %v", err)
    }

    fmt.Printf("Add result: %d\n", resp.Result)


	// tracer2, closer := trace.NewTracer("start2")
	// conn2, err := grpc.Dial(
    //     "localhost:50052",
    //     grpc.WithUnaryInterceptor(
    //         grpcMiddleware.ChainUnaryClient(
    //             interceptor.ClientInterceptor(tracer2),
    //         ),
    //     ),
    //     grpc.WithTransportCredentials(insecure.NewCredentials()), 
    // )
    // if err != nil {
    //     log.Fatalf("did not connect: %v", err)
    // }
    // defer closer.Close()
	// // tracer, closer := trace.NewTracer("start")
	// // grpcServer := grpc.NewServer(grpc.UnaryInterceptor(
	// // 	grpcMiddleware.ChainUnaryServer(
	// // 		interceptor.ServerInterceptor(tracer),
	// // 	),
	// // ))

    // client2 := MultiplyServ.NewMultiplyServiceClient(conn2)
    // req2 := &MultiplyServ.MultiplyRequest{
    //     A: 5,
    //     B: 3,
    // }

    // resp2, err := client2.Multiply(context.Background(), req2)
    // if err != nil {
    //     log.Fatalf("Error calling Add service: %v", err)
    // }

    // fmt.Printf("Add result: %d\n", resp2.Result)
}