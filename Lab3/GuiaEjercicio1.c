#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/chat_socket"

int main(){
    int socketServidor, socketClientel;
    struct sockaddr_un direccion;
    char buffer[250];

    socketServidor = socket(AF_UNIX, SOCK_STREAM, 0);
    //CREAR DIRECCION

    memset(&direccion, 0, sizeof(direccion));
    direccion.sun_family = AF_UNIX;
    strncpy(direccion.sun_path, SOCKET_PATH, sizeof(direccion.sun_path) - 1 );

    if(bind(socketServidor, (struct sockaddr *)direccion, sizeof(direccion)) < 0 )

    return 0;
}