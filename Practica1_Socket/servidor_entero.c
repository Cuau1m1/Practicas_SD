#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

void error_handling(char *message);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <puerto>\n", argv[0]);
        exit(1);
    }
    
    WSADATA wsaData;
    SOCKET hServSock, hClntSock;
    SOCKADDR_IN servAddr, clntAddr;
    
    char buffer_rx[1024];
    char buffer_tx[1024];
    int szClntAddr;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        error_handling("Error WSAStartup");
    }

    hServSock = socket(PF_INET, SOCK_STREAM, 0);
    if (hServSock == INVALID_SOCKET) {
        error_handling("Error al crear socket");
    }

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));


    if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
        error_handling("Error en bind()");
    }

    if (listen(hServSock, 5) == SOCKET_ERROR) {
        error_handling("Error en listen()");
    }

    while(1) { 
        szClntAddr = sizeof(clntAddr);
        hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
        if (hClntSock == INVALID_SOCKET) {
            error_handling("Error en accept()");
            continue;
        }

        int str_len;
        while((str_len = recv(hClntSock, buffer_rx, sizeof(buffer_rx) - 1, 0)) != 0) {
             if (str_len < 0) break;

            buffer_rx[str_len] = '\0';
            
            int numero_recibido = atoi(buffer_rx);
            int numero_respuesta = numero_recibido + 1;            
            snprintf(buffer_tx, sizeof(buffer_tx), "%d\n", numero_respuesta);
            send(hClntSock, buffer_tx, strlen(buffer_tx), 0);
        }
        closesocket(hClntSock); 
        
    }

    closesocket(hServSock);
    WSACleanup();
    return 0;
}

void error_handling(char *message) {
    // linea corregida
    fprintf(stderr, "Error: %s (Codigo: %d)\n", message, WSAGetLastError());
    exit(1);
}