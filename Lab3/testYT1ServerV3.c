#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#define MAXCLIENTES 5
int clientes[MAXCLIENTES];
char nombresClientes[MAXCLIENTES][100];
int cantClientes = 0;

void *lecturaServidor(void *arg){
    long nuevoSock = (long)arg;
    char buffer[200];
    char nombre[100];
    read(nuevoSock, nombre, sizeof(nombre));
    strcpy(nombresClientes[cantClientes], nombre);
    // nombresClientes[cantClientes] = nombre;
    clientes[cantClientes] = nuevoSock;
    cantClientes++;
    while(1){
        memset(buffer, 0, sizeof(buffer));
        if(read(nuevoSock, buffer, sizeof(buffer))>0){
            for(int i = 0 ; i < cantClientes ; i++){
                if(clientes[i]==nuevoSock){
                    printf("%s: %s", nombresClientes[i], buffer);
                //write(clientes[i], buffer, sizeof(buffer));
                    if(strcmp("Adiosin", buffer)==0){
                        break;
                    }
                }
            }
        }
        // printf("LitusCliente : %s", buffer);
    }
}
// void *escrituraServidor(void *arg){
//     long nuevoSock = (long)arg;
//     char buffer[200];
//     while(1){
//         memset(buffer, 0, sizeof(buffer));
//         // printf("LitusServer : ");
//         fgets(buffer, 200, stdin);
//         write(nuevoSock, buffer, strlen(buffer)+1);
        
//     }

// }
void error(const char *msg){
    perror(msg);
    exit(0);
}
int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(stderr, "Por No not provided. Programa finalizado.");
        exit(1);
    }
    long sockIni, nuevoSock, puertoNum;
    char buffer[200];
    struct sockaddr_in server_direccion = {0}, cliente_direccion = {0};
    socklen_t clienteLen;
    sockIni = socket(AF_INET, SOCK_STREAM, 0);
    puertoNum = atoi(argv[1]);
    server_direccion.sin_family = AF_INET;
    server_direccion.sin_addr.s_addr = INADDR_ANY;
    server_direccion.sin_port = htons(puertoNum);
    if(bind(sockIni, (struct sockaddr *)&server_direccion, sizeof(server_direccion)) < 0){
        error("Bind fallando : ");
    }
    if(listen(sockIni, 5)<0){
        error("Listen fallando : ");
    } 
    clienteLen = sizeof(cliente_direccion);
    
    
    //Creamos el thread de lectura y escritura
    while(1){
        nuevoSock = accept(sockIni, (struct sockaddr *)&cliente_direccion, &clienteLen);
        if(nuevoSock < 0){
            perror("Erro en accept");
            exit(1);
        }
        pthread_t hiloLectura, hiloEscritura;
        pthread_create(&hiloLectura, NULL, lecturaServidor, (void *)nuevoSock);
        // pthread_create(&hiloEscritura, NULL, escrituraServidor, (void *)nuevoSock);
    }
    // pthread_join(hiloLectura, NULL);
    // pthread_join(hiloEscritura, NULL);
    close(sockIni);
    close(nuevoSock);
    return 0;
}
