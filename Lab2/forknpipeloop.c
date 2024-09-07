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
        for(int ii = 0 ; ii < 10 ; ++ii){
            snprintf(buffer, sizeof(buffer), "Locuras #%d\n",ii);
            write(rw0[1], buffer, sizeof(buffer));
            // sleep(0.1);
        }
        close(rw0[1]);
       }
    else{
        close(rw0[1]);
        // for(int ii = 0 ; ii < 10 ; ++ii){
            while(read(rw0[0], buffer, sizeof(buffer))){
                printf("Como padre recibi : %s", buffer);
            }
        // }
        close(rw0[0]);
    }
    return 0;
}
