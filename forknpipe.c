#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(void){
    char buffer[100];
    char message[]="Holiboli mundo!\n";
    
    int index, rw0[2];
    pipe(rw0);
    int children = fork();

    if(children==0){
        close(rw0[0]);
        write(rw0[1], message, strlen(message)+1);
        close(rw0[1]);
        printf("Como hijo, he escrito:  %s", message);
    }
    else{
        close(rw0[1]);
        read(rw0[0], buffer, sizeof(buffer));
        close(rw0[0]);
        printf("Como padre recibi : %s", buffer);
    }


    return 0;
}
