#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define WRITE 1
#define READ 0
#define IMPAR 0
#define PAR 1
#define DOSUNO 2
int main(int na, char *argv[]){
	int n,i,pid;
	int paips[3][2];
	if(na != 2) {
		fprintf(stderr, "Uso: %s <n>\n",argv[0]);
		exit(1);
	}
	n = atoi(argv[1]);
    for(int i = 0 ; i < 3 ; i++){
        pipe(paips[i]);
    }

	for(i=0;i<3;i++) {
		if(!(pid = fork())) {
			int j,r, mypid;
			if(i==IMPAR){
                close(paips[PAR][READ]);
                close(paips[DOSUNO][READ]);
            }
            else if(i==PAR){
                close(paips[IMPAR][READ]);
                close(paips[DOSUNO][READ]);
            }
            else{
                close(paips[PAR][READ]);
                close(paips[IMPAR][READ]);
            }
			mypid = getpid();
			srand(mypid);			
			for(j=0;j<n;j++) {
			    r = rand() % 528;
			    printf("%d %d\n",mypid,r);
				if(r%2==0){
					write(paips[PAR][WRITE], &r, sizeof(r));	
				}
				else{
					write(paips[IMPAR][WRITE], &r, sizeof(r));	
				}
				if(r%10 == 1 || r%10 ==2){
					write(paips[DOSUNO][WRITE], &r, sizeof(r));	
				}
			}
			close(paips[PAR][WRITE]);
			close(paips[IMPAR][WRITE]);
			close(paips[DOSUNO][WRITE]);
			if(i==IMPAR){	
				int x;
				printf("El proceso %d (impares) imprime : ", getpid());
				while(read(paips[IMPAR][READ], &x, sizeof(x))){
					printf("%d ", x);
				}
				printf("\n");
            }
            else if(i==PAR){
				int x;
				printf("El proceso %d (pares) imprime : ", getpid());
				while(read(paips[PAR][READ], &x, sizeof(x))){
					printf("%d ", x);
				}
				printf("\n");
            }
            else{
				int x;
				printf("El proceso %d (terminan en 1 o 2) imprime : ", getpid());
				while(read(paips[DOSUNO][READ], &x, sizeof(x))){
					printf("%d ", x);
				}
				printf("\n");
            }    
			exit(0);    
		}	
	}
	exit(0);	
}	