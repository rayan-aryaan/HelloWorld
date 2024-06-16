#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib")
#endif

#define BUFFER_SIZE 1024

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("No port no specified\n");
        return 1;
    }
    WSADATA wsaData;
    int result;
    struct sockaddr_in serverAddress;
    int addrlen = sizeof(serverAddress);
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("WSAStartup failed: %d\n", result);
        return 1;
    }

    // Create a SOCKET for connecting to server
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(atoi(argv[1]));
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
    result = connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
    if(result == SOCKET_ERROR) {
        printf("Error at connect: %1d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 0;
    }
    char str[BUFFER_SIZE];
    printf("Send some message to server: ");
    gets_s(str, sizeof(str));
    int bytesSend = send(clientSocket, str, BUFFER_SIZE, 0);
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}