package main

import (
	"context"
	"log"
	"time"

	pb "usertest/user/proto"

	"google.golang.org/grpc"
)

const (
	address = "localhost:8080"
)

func main() {
	// Set up a connection to the server.
	conn, err := grpc.Dial(address, grpc.WithInsecure(), grpc.WithBlock())
	if err != nil {
		log.Fatalf("did not connect: %v", err)
	}
	defer conn.Close()
	client := pb.NewUserClient(conn)

	// Contact the server and print out its response.
	ctx, cancel := context.WithTimeout(context.Background(), time.Second)
	defer cancel()

	r, err := client.CheckUser(ctx, &pb.Request{
		Username: "Cornell_1",
		// Password: "1111111111",
	})
	if err != nil {
		log.Fatalf("could not check user: %v", err)
	}
	log.Printf("User check result: %v", r.Correct)

}
