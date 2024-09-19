#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

#define h_addr h_addr_list[0]

void *lecturaServidor(void *arg){
    printf("sdada\n");
    long nuevoSock = (long)arg;
    char buffer[200];
    while(1){
        memset(buffer, 0, sizeof(buffer));
        if(read(nuevoSock, buffer, sizeof(buffer)) > 0){
            printf("LitusServer : %s", buffer);
            if(strcmp("Adiosin", buffer)==0){
                break;
            }
        }
    }
    pthread_exit(NULL);   
}
void *escrituraServidor(void *arg){
    
    long nuevoSock = (long)arg;
    char buffer[200];
    while(1){
        memset(buffer, 0, sizeof(buffer));
        fgets(buffer, 200, stdin);
        write(nuevoSock, buffer, strlen(buffer)+1);
        printf("LitusCliente : %s",buffer);
    }
    pthread_exit(NULL);
}
void error(const char *msg){
    perror(msg);
    exit(0);
}
int main(int argc, char *argv[]){
    if(argc < 3){
        fprintf(stderr, "Por No not provided. Programa finalizado.");
        exit(1);
    }
    long sock, puerto;
    struct sockaddr_in servidor_dir;
    struct hostent *servidor;
    puerto = atoi(argv[2]);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        fprintf(stderr, "No se pudo inicializar el socekt\n");
        exit(2);
    }
    servidor = gethostbyname(argv[1]);
    if(servidor == NULL)fprintf(stderr, "No hay host.");

    memset(&servidor_dir, 0, sizeof(servidor_dir));
    servidor_dir.sin_family = AF_INET;
    memcpy(&servidor_dir.sin_addr.s_addr, servidor->h_addr, servidor->h_length);
    servidor_dir.sin_port = htons(puerto);
    if(connect(sock, (struct sockaddr *) &servidor_dir, sizeof(servidor_dir))<0){
        error("Conexion fallida");
    }
    pthread_t hiloLectura, hiloEscritura;
    pthread_create(&hiloEscritura, NULL, escrituraServidor, (void *)sock);
    pthread_create(&hiloLectura, NULL, lecturaServidor, (void *)sock);
    pthread_join(hiloLectura, NULL);
    pthread_join(hiloEscritura, NULL);
    close(sock);
    return 0;
}
