#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/wait.h>

#define SV_SOCK_PATH "/tmp/us_x2"
#define BUF_SIZE 100
#define BACKLOG 5
#define WRITE_END 1
#define READ_END 0

// Función que atiende a un cliente (se ejecuta en un hilo)
void *atenderCliente(void *arg) {
    int cfd = (int)(long)arg;
    int cant, number;
    char comando[100], buffer[BUF_SIZE];

    // Leer la cantidad de números
    if (read(cfd, &cant, sizeof(cant)) <= 0) {
        perror("Error al leer cantidad de números");
        close(cfd);
        return NULL;
    }

    // Crear pipes para comunicar con los hijos que ejecutan factor
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        close(cfd);
        return NULL;
    }

    for (int i = 0; i < cant; i++) {
        // Leer cada número enviado por el cliente
        if (read(cfd, &number, sizeof(number)) <= 0) {
            perror("Error al leer número");
            close(cfd);
            return NULL;
        }
        fprintf(stderr, "%d\n", number);
        // Crear un proceso hijo para ejecutar 'factor'
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            close(cfd);
            return NULL;
        }

        if (pid == 0) {  // Proceso hijo
            close(pipefd[READ_END]);  // Cerrar el lado de lectura del pipe
            // Redirigir la salida estándar al pipe
            dup2(pipefd[WRITE_END], STDOUT_FILENO);

            // Preparar el comando 'factor' para el número actual
            snprintf(comando, sizeof(comando), "factor %d", number);
            fprintf(stderr, "estoy llorando\n");
            execl("/usr/bin/bash", "bash", "-c", comando, (char *)NULL);

            
            perror("execl");  // Si execl falla
            exit(EXIT_FAILURE);
        } else {  // Proceso padre
            close(pipefd[WRITE_END]);  // Cerrar el lado de escritura del pipe

            // Leer la salida del comando 'factor' desde el pipe
            memset(buffer, 0, BUF_SIZE);
            if (read(pipefd[READ_END], buffer, BUF_SIZE) > 0) {
                // Verificar si el número es primo (la salida de factor será del tipo "N: N")
                // char *prime = strchr(buffer, ':') + 2;  // Saltar el "N: "
                // fprintf(stderr, "%s", buffer);
                // if (atoi(prime) == number) {
                    // Es un número primo, enviarlo al cliente
                    
                    write(cfd, &number, sizeof(number));

                // }
            }

            wait(NULL);  // Esperar al proceso hijo
        }
    }

    // Cerrar el socket del cliente
    close(cfd);
    return NULL;
}

int main() {
    struct sockaddr_un addr;
    int sfd, cfd;
    pthread_t hilo;

    // Crear socket UNIX
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Eliminar archivo de socket si existe
    if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT) {
        perror("remove");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del socket
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    // Enlazar el socket
    if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(sfd, BACKLOG) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Servidor esperando conexiones...\n");

    // Aceptar conexiones y atender clientes concurrentemente
    for (;;) {
        cfd = accept(sfd, NULL, NULL);
        if (cfd == -1) {
            perror("accept");
            continue;
        }

        // Crear un hilo para atender al cliente
        if (pthread_create(&hilo, NULL, atenderCliente, (void *)(long)cfd) != 0) {
            perror("pthread_create");
            close(cfd);
        }

        // Detach del hilo para evitar bloqueos
        pthread_detach(hilo);
    }

    close(sfd);
    return 0;
}
