#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>

#define SOCKET_PATH "/tmp/chatuni2"

int main(int argc, char *argv[]){
    int sockServidor, num, num2;
    struct sockaddr_un dirServer;
    char buffer[255];
    //creando socket
    //direccion del server
    
    //vincular
    while(1){
        printf("Ingrese un numero : ");
        scanf("%d", &num);
        sockServidor = socket(AF_UNIX, SOCK_STREAM, 0);
        memset(&dirServer, 0, sizeof(dirServer));
        dirServer.sun_family = AF_UNIX;
        strncpy(dirServer.sun_path, SOCKET_PATH, sizeof(dirServer.sun_path) - 1);
        connect(sockServidor, (struct sockaddr *)&dirServer, sizeof(dirServer));
        write(sockServidor, &num, sizeof(num));
    
        while(read(sockServidor, &num2, sizeof(num2)) > 0);

        printf("Su fibonacci es : %d\n", num2);
        close(sockServidor);
    }
    return 0;
}