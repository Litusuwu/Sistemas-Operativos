#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {  // Verificamos si hay 4 argumentos (incluyendo argv[0])
        fprintf(stderr, "Uso: %s <letra1> <letra2> <otro argumento> %d\n", argv[0], argc);
        exit(1);
    }

    // argv[1] es la primera letra, argv[2] es la segunda letra
    char letter1 = argv[1][0];
    char letter2 = argv[2][0];

    // Verificamos que argv[1] y argv[2] sean letras válidas
    if (letter1 < 'A' || letter1 > 'Z' || letter2 < 'A' || letter2 > 'Z') {
        fprintf(stderr, "Las letras deben estar en el rango A-Z.\n");
        exit(1);
    }

    // Condición de terminación: si argv[1] y argv[2] son iguales, se sale
    if (letter1 == letter2) {
        printf("Las letras %c y %c son iguales. Proceso finalizado.\n", letter1, letter2);
        exit(0);
    }

    // Creamos un proceso hijo con fork
    int pid = fork();

    if (pid < 0) {  // Si hubo error en fork
        perror("fork error");
        exit(1);
    }
    char new_argv1[2];
    new_argv1[0] = argv[1][0] + 1;  // Incrementamos la letra
    new_argv1[1] = '\0';  // Aseguramos que la cadena esté terminada

    // Llamamos a execl con la copia de los argumentos modificados
    printf("Proceso hijo: ejecutando execl con argv[1] = %c\n", new_argv1[0]);
    execl(argv[0], argv[0], new_argv1, argv[2], argv[3], (char *) NULL);

    // Si execl falla, imprimimos un mensaje de error y terminamos
    perror("execl error");
    exit(1);
    

    return 0;
}
