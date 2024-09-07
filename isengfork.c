#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int ii = 0;
    int padre = getpid();
    if (fork() == 0) ii++;
    //waitpid(-1, NULL, 0);
    if (fork() == 0) ii++;
    //waitpid(-1, NULL, 0);
    if (fork() == 0) ii++;
    //waitpid(-1, NULL, 0);
    printf("Result = %3.d \n", ii);
    if(padre == getpid()){
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "pstree -p %d", getpid());
        system(buffer);
    }
    else{
        sleep(1);
    }


    return 0;
}

