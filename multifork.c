#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DISPLAY1 "PID INDUK= ** pid (%5.d) ** ************\n"
#define DISPLAY2 "val1(%5.d) val2(%5.d) val3(%5.d)\n"

int main(void) {
    pid_t val1, val2, val3;
    int vl = getpid();
    printf(DISPLAY1, (int) getpid());
    fflush(stdout);
    val1 = fork();
    //waitpid(-1, NULL, 0);
    val2 = fork();
    //waitpid(-1, NULL, 0);
    val3 = fork();
    //waitpid(-1, NULL, 0);
    printf(DISPLAY2, (int) val1, (int) val2, (int) val3);
    
    if(vl == getpid()){
        char nom[50];
        snprintf(nom, sizeof(nom), "pstree -p %d", vl);
        system(nom);
    }
    else{
        sleep(1);
    }
    return 0;
}

