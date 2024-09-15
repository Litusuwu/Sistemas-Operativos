#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define h_addr h_addr_list[0]
void error(const char *msg){
    perror(msg);
    exit(0);
}
int main(int argc, char *argv[]){
    if(argc < 3){
        fprintf(stderr, "Por No not provided. Programa finalizado.");
        exit(1);
    }
    int sock, puerto;
    struct sockaddr_in servidor_dir;
    struct hostent *servidor;
    char buffer[200];

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

    while(1){
        memset(buffer, 0, sizeof(buffer));
        fgets(buffer, 200, stdin);

        write(sock, buffer, strlen(buffer));
        memset(buffer, 0, sizeof(buffer));
        read(sock, buffer, 200);
        printf("Litus Server: %s", buffer);
        
        if(strcmp("Adiosin", buffer)==0){
            break;
        }
    }
    close(sock);
    return 0;
}
