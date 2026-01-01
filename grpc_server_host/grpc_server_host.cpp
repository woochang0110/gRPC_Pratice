// grpc_server_host.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <iostream>

typedef bool (*StartGrpcServerFn)(const char*);
typedef void (*StopGrpcServerFn)();

int main()
{
    HMODULE hDll = LoadLibraryA("grpc_x64.dll");
    if (!hDll)
    {
        std::cout << "DLL load failed\n";
        return -1;
    }

    auto StartGrpcServer =
        (StartGrpcServerFn)GetProcAddress(hDll, "StartGrpcServer");

    auto StopGrpcServer =
        (StopGrpcServerFn)GetProcAddress(hDll, "StopGrpcServer");

    if (!StartGrpcServer || !StopGrpcServer)
    {
        std::cout << "GetProcAddress failed\n";
        return -1;
    }

    StartGrpcServer("0.0.0.0:50051");

    std::cout << "gRPC server running. Press ENTER to stop...\n";
    std::cin.get();

    StopGrpcServer();
    FreeLibrary(hDll);
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
