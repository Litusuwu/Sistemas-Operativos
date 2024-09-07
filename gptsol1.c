#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 64

int main(void) {
    int n = 2;  // Número de bifurcaciones (n). Cambia este valor según el número de niveles de fork.
    
    int num_procesos = 1 << n;  // 2^n procesos en total
    int fd_pipe[num_procesos][2];  // Crear tantos pipes como procesos
    pid_t pids[num_procesos];  // Array para almacenar los PIDs de los procesos
    char buffer1[BUFSIZE], buffer2[BUFSIZE];
    int my_index = 0;  // Para identificar el índice del proceso actual

    // Inicializar los pipes
    for (int i = 0; i < num_procesos; i++) {
        pipe(fd_pipe[i]);
    }

    // Crear los procesos con un bucle for y múltiples forks
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Proceso hijo
            my_index += 1 << i;  // Actualiza el índice del proceso actual basado en el nivel
        } else {
            // Proceso padre guarda el PID
            pids[my_index] = pid;
            break;  // El padre no continúa bifurcando
        }
    }

    // Cada proceso tiene su propio índice (my_index), que es único
    pid_t mypid = getpid();
    sprintf(buffer1, "A message from PID[%d] (Proceso %d).\n", (int)mypid, my_index);

    // Comunicación por pipe
    // Cada proceso escribe su mensaje en su pipe correspondiente
    close(fd_pipe[my_index][0]);  // Cerrar lado de lectura
    write(fd_pipe[my_index][1], buffer1, BUFSIZE - 1);
    close(fd_pipe[my_index][1]);  // Cerrar lado de escritura

    // Ahora leeremos del proceso "anterior" en el ciclo
    int prev_index = (my_index + num_procesos - 1) % num_procesos;
    close(fd_pipe[prev_index][1]);  // Cerrar lado de escritura del proceso anterior
    read(fd_pipe[prev_index][0], buffer2, BUFSIZE - 1);
    printf("PID[%d] (Proceso %d) recibió: %s", (int)mypid, my_index, buffer2);
    close(fd_pipe[prev_index][0]);

    // Esperar a que terminen los procesos hijos
    waitpid(-1, NULL, 0);

    return 0;
}
