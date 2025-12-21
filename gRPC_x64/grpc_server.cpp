#include "pch.h"
#include "grpc_api.h"

#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>

#include "helloworld.grpc.pb.h"

#include <memory>
#include <thread>
#include <atomic>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

static std::unique_ptr<Server> g_server;
static std::thread g_serverThread;
static std::atomic<bool> g_running{ false };


// ---------- Service 구현 ----------
class GreeterServiceImpl final : public helloworld::Greeter::Service {
public:
    Status SayHello(ServerContext* context,
        const helloworld::HelloRequest* request,
        helloworld::HelloReply* reply) override
    {
        reply->set_message("Hello " + request->name());
        return Status::OK;
    }
};

// ---------- 서버 스레드 ----------
static void RunServer(const std::string& address)
{
    GreeterServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    g_server = builder.BuildAndStart();
    g_running = true;

    g_server->Wait();   // 블로킹
}

// ---------- DLL API ----------
bool StartGrpcServer(const char* address)
{
    if (g_running)
        return false;

    g_serverThread = std::thread(RunServer, std::string(address));
    return true;
}

void StopGrpcServer()
{
    if (!g_running)
        return;

    g_server->Shutdown();
    g_serverThread.join();
    g_running = false;
}
