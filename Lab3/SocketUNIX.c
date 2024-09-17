#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/chat_socket"

void error(const char* msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]){
    int sockServidor, sockCliente;
    struct sockaddr_un dirServer, dirCliente;
    char buffer[255];
    //creando socket
    if((sockServidor = socket(AF_UNIX, SOCK_STREAM, 0) )< 0){
        error("Error al crear socket");
    }
    //direccion del server
    memset(&dirServer, 0, sizeof(dirServer));
    dirServer.sun_family = AF_UNIX;
    strncpy(dirServer.sun_path, SOCKET_PATH, sizeof(dirServer.sun_path) - 1);
    //vincular
    if(bind(sockServidor, (struct sockaddr *)&dirServer, sizeof(dirServer) < 0)){
        fprintf(stderr, "Error en el bind");
    }

    return 0;
}