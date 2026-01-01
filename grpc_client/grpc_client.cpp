// grpc_client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <grpcpp/grpcpp.h>
#include "../gRPC_x64/generated/helloworld.grpc.pb.h"

#include <iostream>
#include <memory>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

int main()
{
    auto channel = grpc::CreateChannel(
        "127.0.0.1:50051",
        grpc::InsecureChannelCredentials());

    std::unique_ptr<helloworld::Greeter::Stub> stub =
        helloworld::Greeter::NewStub(channel);

    helloworld::HelloRequest request;
    request.set_name("gRPC DLL");

    helloworld::HelloReply reply;
    ClientContext context;

    Status status = stub->SayHello(&context, request, &reply);

    if (status.ok())
        std::cout << "Reply: " << reply.message() << std::endl;
    else
        std::cout << "RPC failed\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
