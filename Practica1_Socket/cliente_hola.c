#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <IP> <puerto>\n", argv[0]);
        exit(1);
    }
    
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in serv_addr;
    char buffer_usuario[1024] = {0};
    char buffer_envio[1024] = {0};
    char buffer_rx[1024] = {0};

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    printf("Conectado\n");

    //recibe mensake inicial
    int str_len = recv(sock, buffer_rx, sizeof(buffer_rx) - 1, 0);
    buffer_rx[str_len] = '\0';
    printf("Servidor: %s\n", buffer_rx);

    // Bucle infinito para la conversación
    while (1) {
        fgets(buffer_usuario, sizeof(buffer_usuario), stdin);
        buffer_usuario[strcspn(buffer_usuario, "\r\n")] = 0;

        snprintf(buffer_envio, sizeof(buffer_envio), "%s\n", buffer_usuario);
        send(sock, buffer_envio, strlen(buffer_envio), 0);

        str_len = recv(sock, buffer_rx, sizeof(buffer_rx) - 1, 0);

        /*  if (str_len <= 0) {
            printf("El servidor cerro la conexion\n");
            break;
        }*/


        buffer_rx[str_len] = '\0';
        printf("Servidor: %s", buffer_rx);
    }
    
    closesocket(sock);
    WSACleanup();
    printf("Conversacion finalizada\n");

    return 0;
}
