#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define BFSZ 100
#define READ 0
#define WRITE 1

int main(int argc, char *argv[]){
    int n = atoi(argv[1]);
    int parent = getpid();
    int pipes[2];
    srand(time(NULL));
    if(argc != 2 || n < 2){
        return 1;
    } 
    pipe(pipes);
    int i, k = (rand() % (n-1)) + 1;
    
    for(i = 0 ; i < n ; i++){
        if(fork()) break;
    }
    if(i==k){
        close(pipes[WRITE]);
        printf("El hijo seleccionado fue : %d [%d], el padre es %d\n", getpid(),i, parent);        
        int pids;
        char codigo[100];
        int procesosOrdenados[n-1], index = n-2;
        snprintf(codigo, sizeof(codigo), "pstree -s %d", getpid());
        while(read(pipes[READ],&pids, sizeof(pids)) > 0){
            procesosOrdenados[index] = pids;
            index--;
        }
        for(int j = 0 ; j < n-1 ; ++j){    
            if(procesosOrdenados[j] == parent)continue;
            printf("Eliminando el proceso con PID : [%d]\n", procesosOrdenados[j]);
            snprintf(codigo, sizeof(codigo), "kill %d", procesosOrdenados[j]);
            system(codigo);
            snprintf(codigo, sizeof(codigo), "pstree -p %d", parent);
            system(codigo);
        }
        printf("Eliminado al padre. [%d]\n", parent);
        snprintf(codigo, sizeof(codigo), "kill %d", parent);
        system(codigo);
        snprintf(codigo, sizeof(codigo), "pstree -p %d", parent);
        system(codigo);

        close(pipes[READ]);
        
    }
    else{
        close(pipes[READ]);
        int cod = getpid();
        write(pipes[WRITE], &cod, sizeof(cod));
        close(pipes[WRITE]);
        sleep(1);
    }
    return 0;
}
