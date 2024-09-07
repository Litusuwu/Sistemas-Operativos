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
    int cant = atoi(argv[1]);
    int pids[cant][2];
    int i;
    int parent = getpid();
    for(i = 0 ; i < cant ; ++i){
        pipe(pids[i]);
    }
    for(i = 0 ; i < cant ; ++i ){
        if(fork())break;
    }
    int prev = (i+(cant-1))%cant; //index anterior
    close(pids[i][READ]);
    close(pids[prev][WRITE]);
    for(int j = 0 ; j < cant ; ++j){
        if(j != i && j != prev){            
            close(pids[j][READ]);
            close(pids[j][WRITE]);
        }
    }
    if(getpid()==parent){
        char buffer[]="Mensajin."; 
        char ans[100];
        write(pids[i][WRITE], buffer, sizeof(buffer));
        close(pids[i][WRITE]);
        printf("Mensaje enviado desde %d: %s\n",i, ans);
        while(read(pids[prev][READ], ans, sizeof(ans))){
            printf("Mensaje recibido desde %d: %s\n",prev, ans);
        }
    }
    else{
        char ans[100];
        while(read(pids[prev][READ], ans, sizeof(ans))){
            write(pids[i][WRITE], ans, sizeof(ans));
        }
        close(pids[i][WRITE]);
        printf("Mensaje enviado desde: Proceso %d\n",i);
    }
    
    close(pids[prev][READ]); 
    return 0;
}