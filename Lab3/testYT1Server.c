#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
void error(const char *msg){
    perror(msg);
    exit(0);
}
int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(stderr, "Por No not provided. Programa finalizado.");
        exit(1);
    }
    int sockIni, nuevoSock, puertoNum;
    char buffer[200];
    struct sockaddr_in server_direccion = {0}, cliente_direccion = {0};
    socklen_t clienteLen;

    //Inicializar el socket 
    sockIni = socket(AF_INET, SOCK_STREAM, 0);
    //HACER TODOS LOS VALORES A 0 DEL ADDRESS
    //bzero((char *)&server_direccion, sizeof(server_direccion));
    //asignar puerto
    puertoNum = atoi(argv[1]);
    //asignar valores a los atribnutos del sockadrr_in
    server_direccion.sin_family = AF_INET;
    server_direccion.sin_addr.s_addr = INADDR_ANY;
    server_direccion.sin_port = htons(puertoNum);
    //asignamos a nuestro socket, los valores del servidor 
    if(bind(sockIni, (struct sockaddr *)&server_direccion, sizeof(server_direccion)) < 0){
        error("Bind fallando : ");
    }
    //ahora debe hacer listen, escucha a 5 simultaneamente como maximo
    if(listen(sockIni, 5)<0){
        error("Listen fallando : ");
    }
    

    //preparamos el socket del cliente
    clienteLen = sizeof(cliente_direccion);
    nuevoSock = accept(sockIni, (struct sockaddr *)&cliente_direccion, &clienteLen);
    if(nuevoSock < 0){
        perror("Erro en accept");
        exit(1);
    }
    while(1){
        //colocamos el buffer en 0
        memset(buffer, 0, sizeof(buffer));
        read(nuevoSock, buffer, 200);
        printf("Litus Cliente: %s", buffer);
        
        memset(buffer, 0, sizeof(buffer));
        fgets(buffer, 200, stdin);

        write(nuevoSock, buffer, strlen(buffer));
        if(strcmp("Adiosin", buffer)==0){
            break;
        }
    }
    close(sockIni);
    close(nuevoSock);
    return 0;
}
