#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib")
#endif

#define MAX(a, b) a > b ? a : b
#define BUFFER_SIZE 1024

template <class T>
int _max(T a, T b) {
    return a > b ? a : b;
}

int main(int argc, char** argv, char** envp) {
    if (argc < 2) {
        printf("No port no specified\n");
        return 1;
    }
    WSADATA wsaData;
    int result;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    //printf("%d", _max(5.1, 2));
    //printf("%d", _max(5.5, 2.1));
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("WSAStartup failed: %d\n", result);
        return 1;
    }

    // Create a SOCKET for connecting to server
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    char* c = argv[1];
    int portNo = atoi(c);
    address.sin_port = htons(portNo);
    result = bind(serverSocket, (struct sockaddr*)&address, addrlen);
    if(result == SOCKET_ERROR) {
        printf("Error at bind: %ld\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    result = listen(serverSocket, 1);
    if(result == SOCKET_ERROR) {
        printf("Error at listen: %ld\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    SOCKET clientSocket = accept(serverSocket, (sockaddr*)&address, &addrlen);
    if (clientSocket == INVALID_SOCKET) {
        printf("Error at client socket(): %ld\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    char buffer[BUFFER_SIZE];
    int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if(bytesReceived > 0) {
        printf("Received message: %s\n", buffer);
    }
    // Clean up and exit
    closesocket(serverSocket);
    closesocket(clientSocket);
    WSACleanup();
    return 0;


}