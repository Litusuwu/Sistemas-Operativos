#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


void arbolito(int w, int limite){
    
    if(w >= limite)return;
    if(!fork()){
        sleep(1);
        arbolito(2*w, limite);
        printf("Proceso numero %d\n", 2*w);
        exit(0);
    }
    if(!fork()){
        sleep(1);
        arbolito(2*w + 1, limite);
        printf("Proceso numero %d\n", 2*w + 1);
        exit(0);
    } 
}

int main(int narg, char *argv[]){
    int val = atoi(argv[1]);
    arbolito(1, (1<<(val-1)));
    char nom[100];
    snprintf(nom, sizeof(nom), "pstree -c %d \n", getpid());
    system(nom);
    return 0;
}
