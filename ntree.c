#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WRITE 1
#define READ 0

int final;
int depth;
void creaArbol(int num, int da, int lvl){
    if(lvl > depth)return;
    char cadena[60];
    printf("Soy el proceso %d con pid : y ppid : %d \n", getpid(), getppid());
    for(int j = 1 ; j <= da ; j++){
        if(!fork()){
            creaArbol(2*num + 1, da, lvl+1);
            sleep(1);
            exit(0);
        }
    }
    return;   
}
int main(int argc, char *argv[]){
    depth = atoi(argv[1]);
    int parent = getpid();
    if(argc != 2 || depth <=1){
        printf("Numero incorrecto de argumentos.\n");
        return 2;
    }
    creaArbol(1, depth, 1);
    printf("%d %d %d", final, depth, parent);
    if(getpid() == parent){
        char comando[100];
        snprintf(comando, sizeof(comando), "pstree -p %d > intro.txt", parent);
        system(comando);
    }
    return 0;
}