#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define WRITE 1
#define READ 0


int main(int argc, char *argv[]){
    char palabra[100];
    strcpy(palabra, argv[1]);
    int n = 3;
    int pipes[n][2];
    for(int i = 0 ; i < n ; i++){
        pipe(pipes[i]);
    }
    int i = 0;
    for(i = 0 ; i < n ; i ++){
        if(fork())break;
    }
    int ant = (i+(n-1))%n;
    close(pipes[i][READ]);
    close(pipes[ant][WRITE]);
    for(int k = 0 ; k < n ; ++k){
        if(k != i && k != ant){
            close(pipes[k][READ]);
            close(pipes[k][WRITE]);
        }
    }
    if(i==0){
        char str[100];
        write(pipes[i][WRITE], palabra, sizeof(palabra));
        close(pipes[i][WRITE]);
        while(read(pipes[ant][READ], str, sizeof(str))){
            printf("El mensaje recibido fue : %s\n", str);
        }
    }
    else if(i==1){
        char str[100];
        char reverseStr[100];
        while(read(pipes[ant][READ], str, sizeof(str))){
            //close(pipes[i][READ]);
            for(int i = 0 ; i < strlen(str); i++){
                reverseStr[i] = str[strlen(str) - i - 1];  
            }
            reverseStr[strlen(str)] = 0;
            write(pipes[i][WRITE], reverseStr, sizeof(reverseStr));
            
        }
    }
    else{
        char str[100];
        char mayus[100];
        while(read(pipes[ant][READ], str, sizeof(str))){
            //close(pipes[i][READ]);
            for(int i = 0 ; i < strlen(str); i++){
                if(str[i] >= 'a')mayus[i] = str[i] - ('a' - 'A');
                else mayus[i] = str[i]; 
                // mayus[i] = str[i]; 
            }
            mayus[strlen(str)] = 0;
            write(pipes[i][WRITE], mayus, sizeof(mayus));
            close(pipes[i][WRITE]);
        }
    }

    close(pipes[ant][READ]);
    // printf("%s", palabra);    
    return 0;
}