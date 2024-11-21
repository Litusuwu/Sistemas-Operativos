#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <math.h>

double final;
char cadena[60];
void crea_procesos(int);


int main(int argc, char *argv[]) {
    int n;
    int pipefd[2];

    // Crear un pipe para capturar la salida de los procesos hijos
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    n = atoi(argv[1]);
    final = pow(2, (n-1));

    pid_t pid = fork();
    if (pid == 0) { // Proceso hijo
        // Redireccionar la salida estándar al pipe
        close(pipefd[0]); // Cerrar el lado de lectura del pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]); // Cerrar el lado de escritura original
        crea_procesos(1);
        exit(0);
    } else { // Proceso padre
        // Cerrar el lado de escritura del pipe
        close(pipefd[1]);

        // Esperar a que el proceso hijo termine
        wait(NULL);

        // Redirigir la entrada del pipe al proceso sort
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]); // Cerrar el lado de lectura original del pipe

        // Ejecutar el comando sort para ordenar la salida
        execl("/usr/bin/sort", "sort", (char *)NULL);
        // perror("execl");
        // exit(EXIT_FAILURE);
    }

    return 0;
}
void crea_procesos(int x){
    int size;
    size = sprintf(cadena, "Proceso # %0.2d: pid=%d, ppid=%d\n", x, getpid(), getppid());
    write(1, cadena, size);
    if (x >= final) return;
    if (!fork()) { crea_procesos(2*x); exit(0); }
    if (!fork()) { crea_procesos(2*x+1); exit(0); }
    wait(NULL);
    wait(NULL);
}