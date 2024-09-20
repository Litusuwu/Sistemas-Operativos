#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define SV_SOCK_PATH "/tmp/us_x2"
#define BUF_SIZE 100

int main(int argc, char *argv[]) {
    int n, m, arr[1000];

    // Inicializar el arreglo con valores negativos (para debug)
    memset(arr, -1, sizeof(arr));

    // Obtener números desde la línea de comandos o desde entrada estándar
    if (argc > 1) {
        n = atoi(argv[1]);
        for (int i = 0; i < n; i++) {
            arr[i] = atoi(argv[i + 2]);
        }
    } else {
        printf("Escriba cantidad de números: ");
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            printf("Escriba número %d: ", i + 1);
            scanf("%d", &m);
            arr[i] = m;
        }
    }

    // Configurar el socket
    struct sockaddr_un addr;
    int sfd;
    char buf[BUF_SIZE];

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);  // Crear socket
    if (sfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    // Conectar al servidor
    if (connect(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // Enviar la cantidad de números al servidor
    if (write(sfd, &n, sizeof(n)) != sizeof(n)) {
        perror("write cantidad");
        exit(EXIT_FAILURE);
    }

    // Enviar los números al servidor
    for (int i = 0; i < n; i++) {
        if (write(sfd, &arr[i], sizeof(arr[i])) != sizeof(arr[i])) {
            perror("write números");
            exit(EXIT_FAILURE);
        }
    }

    // Leer la respuesta del servidor y mostrarla
    while (read(sfd, &m, sizeof(m)) > 0) {
        fprintf(stderr,"%d", m);  // Imprimir la respuesta recibida
    }
    fprintf(stderr, "NO hubo nd\n");
    // Cerrar el socket
    close(sfd);
    printf("Conexión cerrada.\n");

    return 0;
}
