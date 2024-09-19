#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>

#define SOCKET_PATH "/tmp/chatuni2"



int locura(int n){
    int fibo[10000];fibo[0]=0;fibo[1]=1;
    for(int i = 2 ; i <= n ; i++){
        fibo[i]=fibo[i-2]+fibo[i-1];
    }
    return fibo[n];
    
}
void error(const char* msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]){
    // fib[1]=1;fib[0]=0;
    // memset(fib, 0, sizeof(fib));
    int sockServidor, sockCliente;
    struct sockaddr_un dirServer, dirCliente;
    char buffer[255];
    //creando socket
    //direccion del server
    memset(&dirServer, 0, sizeof(dirServer));
    memset(&dirCliente, 0, sizeof(dirCliente));
    dirServer.sun_family = AF_UNIX;
    strncpy(dirServer.sun_path, SOCKET_PATH, sizeof(dirServer.sun_path) - 1);
    sockServidor = socket(AF_UNIX, SOCK_STREAM, 0);
    //vincular
    if(bind(sockServidor, (struct sockaddr *)&dirServer, sizeof(dirServer))==-1){
        perror("Error en el bind");
    }
    if(listen(sockServidor, 10) == -1){
        perror("listen");
    }
    while(1){
        pthread_t hiloLectura, hiloEscritura;
        sockCliente = accept(sockServidor, NULL, NULL);
        int num , num2; 
        read(sockCliente,&num, sizeof(int));
        num2 = locura(num);
        // printf("%d", num2);
        write(sockCliente, &num2, sizeof(int));           
        //pthread_create(&hiloLectura, NULL, lecturaFuncion, (void*)sockCliente);
        //phtread_create(&hiloEscritura, NULL, escrituraFuncion, (void *)sockCliente);
        close(sockCliente);
    }
    close(sockServidor);
    return 0;
}