#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMERO_DE_HILOS 10

void *imprimir_hola_mundo(void *tid)
{
    /* Esta funcion imprime el identificador del hilo y después termina. */
    long id = (long)tid;
    fprintf(stderr, "Hola mundo.Saludos del hilo %ld\n", id);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    /* El programa principal crea 10 hilos y después termina. */
    pthread_t hilos[NUMERO_DE_HILOS];
    int estado;
    long i;
    for (i = 0; i < NUMERO_DE_HILOS; i++)
    {
        fprintf(stderr,"Aqui main.Creando hilo %ld\n", i);
        estado = pthread_create(&hilos[i], NULL, imprimir_hola_mundo, (void *)i);
        if (estado != 0)
        {
            printf("Ups. pthread_create devolvió el codigo de error %d", estado);
            exit(-1);
        }
    }
    pthread_join(hilos[NUMERO_DE_HILOS-1], NULL);
    return 0;
}