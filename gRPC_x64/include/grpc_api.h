#pragma once

#ifdef GRPC_X64_EXPORTS
#define GRPC_API __declspec(dllexport)
#else
#define GRPC_API __declspec(dllimport)
#endif

extern "C" {

	GRPC_API bool StartGrpcServer(const char* address);
	GRPC_API void StopGrpcServer();

}
