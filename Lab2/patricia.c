#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h> //para usar kill


#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

waitpid(pid, &status, 0);

snprintf(command,sizeof(command),"pstree -p %d > multifork.txt",pid_padre);    
system(command);

LAB2-Temas 8
int main(void){
 pid_t child;
 if((child=fork())){ //SE crean 2 procesos. EL hijo es copi
 fprintf(stderr,"\nFork() devolvió %d por tanto soy el 
 }
 else{
 fprintf(stderr,"\nFork() devolvió %d por tanto soy el 
 }
}
/*El hijo crea una copia del padre, pero ahora child tiene 0*/

//a) y b)
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
    pid_t child;
    if((child=fork())){
        fprintf(stderr,"\nFork() devolvió %d por tanto soy el padre con ID = %d", child,getpid());
        wait(NULL);
    }
    else{
        fprintf(stderr,"\nFork() devolvió %d por tanto soy el hijo con ID = %d", child,getpid());
        system("pstree > aprocesos.txt");
    }
}
//a) WAit permite que salga el padre en la captura
//b) sh se llama porque pstree se llama con bahs
//c) Conseguimos la rama cambiando al comando -p en pstree y especificando su pid.
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
#include <stdlib.h>

int main(void){
    pid_t child;
    if((child=fork())){
        fprintf(stderr,"\nFork() devolvió %d por tanto soy el padre con ID = %d", child,getpid());
        wait(NULL);
    }
    else{
        fprintf(stderr,"\nFork() devolvió %d por tanto soy el hijo con ID = %d", child,getpid());
        char command[PATH_MAX];
        snprintf(command,sizeof(command),"pstree -p %d > aprocesos.txt",getpid());
        system(command);
    }
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
#include <stdlib.h>

int main(void){
    int i, status;
    pid_t child;
    pid_t pidPrincipal=getpid();

    for(i=1; i<4;++i) if((child=fork())) break;
    fprintf(stderr,"Esta es la vuelta Nro %d\n",i);
    fprintf(stderr,"Recibi de fork el valor de %d\n",child);
    fprintf(stderr,"Soy el proceso %d con padre %d\n\n",getpid(),getppid());
    
    if(child==0){
        char command[PATH_MAX];
        snprintf(command,sizeof(command),"pstree -p %d > chainp.txt",pidPrincipal);
        system(command);
    }
    else wait(&status);
    
    return 0;
}
/* Se crean 3 hijos en cadena aparte del padre. Usamos wait para que el padre espera al hijo.
 El último hijo toma la foto y los procesos dejan de esperar*/

 #include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
#include <stdlib.h>

int main(void){
    int i, status;
    pid_t child, pid_padre;

    pid_padre=getpid();

    for(i=1; i<4;++i) 
        if((child=fork())<=0) break;
        else fprintf(stderr,"Este es el ciclo Nro. %d y se está creando el proceso %d\n",i,child);
    
    if(pid_padre==getpid()){
        
        char command[PATH_MAX];
        snprintf(command,sizeof(command),"pstree -p %d > fanp.txt",pid_padre);
        system(command);
        for(i=1; i<4; ++i)wait(&status);
    }
    //else waitpid(pid_padre,&status,0);
    
    fprintf(stderr,"Este es el proceso %d con el padre %d\n",getpid(),getppid());
    sleep(1);
    return 0;
}

/*multifork*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
#include <stdlib.h>
#define DISPLAY1 "PID INDUK** ** pid(%5.5d) ** ************\n"
#define DISPLAY2 "val1(%5.5d) -- val2(%5.5d) -- val3(%5.5d)\n"
int main(void){
    pid_t val1, val2,val3, pid_padre;
    int status;
    pid_padre=getpid();
    printf(DISPLAY1,(int)getpid());
    fflush(stdout);
    val1=fork();
    //waitpid(-1,NULL,0);
    val2=fork();
    //waitpid(-1,NULL,0);
    val3=fork();
    //waitpid(-1,NULL,0);
    

    if(getpid()==pid_padre){
        char command[PATH_MAX];
        snprintf(command,sizeof(command),"pstree -p %d > multifork.txt",pid_padre);  
        system(command);
    }
    else sleep(1);
    
    for(int i=0; i<3; ++i)waitpid(-1,NULL,0);
    printf(DISPLAY2,(int)val1,(int)val2, (int)val3);

    /*
    Los procesos se van a ejecutar y cuando duerman, 
    el padre seguirá generando hijos. Cuando el padre tome la foto, 
    todos estarán allí porque solo estaban durmiendo
    NOTA: E display ya no sale igual que antes. 
    */
    return 0;
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
#include <stdlib.h>
int main(void){
    int ii=0;
    pid_t padre=getpid();
    if(fork()==0) ii++;
    //waitpid(-1,NULL,0);
    if(fork()==0) ii++;
    //waitpid(-1,NULL,0);
    if(fork()==0) ii++;
    //waitpid(-1,NULL,0);
    if(padre==getpid()){
        char command[PATH_MAX];
        snprintf(command,sizeof(command),"pstree -p %d > isengfork.txt",padre);  
        system(command);
    }
    else sleep(2.5);
    printf("Result = %3.3d \n", ii);
    waitpid(-1,NULL,0);
    return 0;
}

/*Similar al anterior, en isengfork hace que el 
padre tome la foto y los hijos se duerman*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>
int final;
void creaArbol(int num){

    //preorden 
    char cadena[60];
    sprintf(cadena,"Soy el proceso %d con pid %d y ppid %d \n",num,getpid(),getppid());
    write(1,cadena,strlen(cadena));
    if(num>=final)return;
    if(!fork()) {creaArbol(2*num);exit(0);}
    if(!fork()) {creaArbol(2*num+1);exit(0);}
    wait(NULL);
    wait(NULL);
}
int main(int narg, char*argv[]){
    int n=atoi(argv[1]);
    final=pow(2,(n-1));
    creaArbol(1);
    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int final;

void maketree(int x) {
    char s[60];
    sprintf(s, "I am process %d with %d and ppid %d\n", x, getpid(), getppid());
    write(1, s, strlen(s));
    if (x>=final) return;
    if (!fork()) { maketree(2*x); sleep(1); exit(0); }
    if (!fork()) { maketree(2*x+1); sleep(1); exit(0); }
    // wait(NULL);
    // wait(NULL);
}

int main(int narg, char** argv) {
    int n = atoi(argv[1]);
    final = 1<<(n-1);
    maketree(1);
    // only parent reaches here
    char cmd[200];
    snprintf(cmd, sizeof(cmd), "pstree -c %d > btree.txt", getpid());
    system(cmd);
    return EXIT_SUCCESS;
}

/* explanation:
* children sleep before dying
*/

int fd[2]
pipe(fd) //guarda los descriptores desde donde vamos a leer y escribir.

int fd = open("output.txt", O_WRONLY);
write(fd, "Hello", 5);
// Si no usas close(fd), puede que los datos "Hello" no se escriban en el disco.
close(fd);  // Asegura que los datos sean escritos en el archivo.

write(fd_pipe[p_this][1], buffer1, BUFSIZE-1);
//close(fd_pipe[p_this][1]); //OCASIONA UN DEADLOCK porque la comunicacion sigue abierta
//si no lo cierras, el read jamás retornará 0
while ((read(fd_pipe[p_prev][0], buffer2, BUFSIZE-1)) != 0) {//se quda en bucle
     waitpid(-1, NULL, 0);//
     printf("%d PID[%d] IS WAITING:\n%s\n", ii+jj,(int) mypid, buffer2);
}
close(fd_pipe[p_prev][0]);//ya no va a leer más

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BUFSIZE 64
#define WLOOP 5
int main(void){
    //0--READ
    //1--WRITE
    char buffer[BUFSIZE];
    char message[]="Hello, what's up?\n";
    int ii, pipe_fd[2];
    pipe(pipe_fd); //copias los files descriptors
    if(fork()==0){
        close(pipe_fd[0]); //cerramos la lectura porque no se leera desde e hijo
        printf("I am PID[%d] (child).\n",getpid());
        for(ii=0;ii<WLOOP;ii++)
            write(pipe_fd[1],message,sizeof(message)-1);
        close(pipe_fd[1]); //terminaste de escribir
    }else{
        close(pipe_fd[1]);//cierra el descrptor de escritura, porque solo amos a leer
        printf("I am PID[%d] (parent)\n",(int)getpid());
        while((ii=read(pipe_fd[0],buffer,BUFSIZE-1))!=0){
            printf("PARENT READ[%d]:\n%s\n",(int) ii,buffer);
            memset(buffer,0,sizeof(buffer));
        }
        close(pipe_fd[0]);        
    }
    /**
     EL hijo escribe 1 mensaje
     El padre lee el mensaje
     EL hijo escribe otro mensaje
     EL padre lee otro mensaje
     ...(se repite 5 veces en total)
    */
    return 0;
}

/* forkpipe2.c (C) 2007-2009 Rahmat M. Samik-Ibrahim, GPL-like */
#define BUFSIZE 64
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(void){
    char buffer1[BUFSIZE], buffer2[BUFSIZE];
    int p_this, p_prev, p_nol, p_no2;
    int fd_pipe[4][2], ii, jj;
    pid_t mypid;

    memset(buffer1, 0, BUFSIZE);
    memset(buffer2, 0, BUFSIZE);

    for (ii=0; ii<4; ii++)
        pipe(fd_pipe[ii]);

    ii = (fork() != 0) ? 0 : 2;
    jj = (fork() != 0) ? 0 : 1;

    p_this = ii + jj;
    close(fd_pipe[p_this][0]);

    p_prev = (p_this + 3) % 4;
    close(fd_pipe[p_prev][1]);

    p_nol = (p_this + 1) % 4;
    close(fd_pipe[p_nol][0]);
    close(fd_pipe[p_nol][1]);

    p_no2 = (p_this + 2) % 4;
    close(fd_pipe[p_no2][0]);
    close(fd_pipe[p_no2][1]);

    mypid = getpid();
    sprintf(buffer1, " A message from PID[%d].\n", (int) mypid);
    write(fd_pipe[p_this][1], buffer1, BUFSIZE-1);
    close(fd_pipe[p_this][1]); //Ya no va a escribir más

    while ((read(fd_pipe[p_prev][0], buffer2, BUFSIZE-1)) != 0) {
        waitpid(-1, NULL, 0);//
        printf("%d PID[%d] IS WAITING:\n%s\n", ii+jj,(int) mypid, buffer2);
    }
    close(fd_pipe[p_prev][0]);//ya no va a leer más
    /*
    HAY 4 PIPES. SE crean 4 procesos. Cada proceso tiene los descriptores 
    de los 4 pipes
    Para el proceso 0, será necesario cerrar la lectura en el pipe 0, 
    cerrar la escritura en el pipe 3
    cerrar completamente los pipes 1 y 2 porque no nos srive para la comunicacion
    Para cada proceso habrá que cerrar las comunicaciones y solo dejar 
    aquellas descriptores 
    por los cuales se leera y se escribirá
    */
   return 0;
}
#define BUFSIZE 64
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
void calcular(int *p_this,int *p_prev,int i,int n){
    (*p_this)=i;
    (*p_prev)=((*p_this+n-1)%n);
}

void configPipas(int i, int **fd, int n){
    int p_this,p_prev;
    calcular(&p_this,&p_prev,i,n);
    //configuramos las entradas y saldias
    close(fd[p_prev][1]);
    close(fd[p_this][0]);

    for(int j=0; j<n; j++){
        //cerramos el resto porque no nos comunicaremos por acá
        if(p_this!=j && p_prev!=j){
            close(fd[j][0]); //Ya no va a escribir más
            close(fd[j][1]); //Ya no va a escribir más
        }
    }
}
int main(int argc,char **argv){
    //cadena de procesos 
    pid_t childpid;
    char buffer1[BUFSIZE], buffer2[BUFSIZE];
    int nprocess=atoi(argv[1]);
    int **fd=(int **)malloc(nprocess*sizeof(int *));
    for(int i=0; i<nprocess; i++){
        fd[i]=(int *)malloc(2*sizeof(int));
    }
    //creamos varios pipes
    
    for (int ii=0; ii<nprocess; ii++) pipe(fd[ii]);
    int i=0;
    int p_this,p_prev;
    for(i=0; i<nprocess; i++){
        calcular(&p_this,&p_prev,i, nprocess);
        if(fork()!=0){
            configPipas(i,fd,nprocess); //cerramos las que no usamos
            if(i==0){
                pid_t mypid = getpid();
                sprintf(buffer1, "A message from PID[%d].\n", (int) mypid);
                write(fd[p_this][1], buffer1, BUFSIZE-1);
                printf("Process %d PID[%d] SENT  a message\n",i,(int) mypid);
                close(fd[p_this][1]); //Ya no va a escribir más
                waitpid(-1, NULL, 0);//
                read(fd[p_prev][0], buffer2, BUFSIZE-1);
                printf("PROCESS %d MESSAGE RECEIVED : %s",i,buffer2);
                close(fd[p_prev][0]); 
            }
            else{
                //leemos el mensaje
                read(fd[p_prev][0], buffer2, BUFSIZE-1);
                close(fd[p_prev][0]); 
                printf("PROCESS %d MESSAGE RECEIVED : %s",i,buffer2);
                write(fd[p_this][1], buffer2, BUFSIZE-1);
                close(fd[p_this][1]); 
                waitpid(-1, NULL, 0);//
                //enviamos
            }
            break;
        }
    }
    return 0;
}

#define BUFSIZE 64
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
void calcular(int *p_this,int *p_prev,int i,int n){
    (*p_this)=i;
    (*p_prev)=((*p_this+n-1)%n);
}

void configPipas(int i, int **fd, int n){
    int p_this,p_prev;
    calcular(&p_this,&p_prev,i,n);
    //configuramos las entradas y saldias
    close(fd[p_prev][1]);
    close(fd[p_this][0]);

    for(int j=0; j<n; j++){
        //cerramos el resto porque no nos comunicaremos por acá
        if(p_this!=j && p_prev!=j){
            close(fd[j][0]); //Ya no va a leer por este pipe
            close(fd[j][1]); //Ya no va a escribir más
        }
    }
}

void proceso1(int **fd,int p_this,int p_prev){
    char buffer1[BUFSIZE];
    printf("Por favor ingrese una cadena: ");
    fgets(buffer1,sizeof(buffer1),stdin);
    buffer1[strlen(buffer1)-1]=0;//le borramos el \n
    write(fd[p_this][1], buffer1, BUFSIZE-1);
    close(fd[p_this][1]); //Ya no va a escribir más
    waitpid(-1, NULL, 0);//esperamos a que su hijo termine de ejecutarse
    memset(buffer1,0,sizeof(buffer1));
    read(fd[p_prev][0], buffer1, BUFSIZE-1);
    printf("La cadena procesada es: %s\n",buffer1);
    close(fd[p_prev][0]);
}

void proceso2(int **fd,int p_this,int p_prev){
    char buffer1[BUFSIZE],buffer2[BUFSIZE];
    memset(buffer2,0,sizeof(buffer2));
    memset(buffer1,0,sizeof(buffer1));
    read(fd[p_prev][0], buffer1, BUFSIZE-1);
    close(fd[p_this][0]);
    int tam=strlen(buffer1);
    for(int i=tam-1,k=0; i>=0; i--,k++){
        buffer2[k]=buffer1[i];
    }
    write(fd[p_this][1], buffer2, BUFSIZE-1);
    close(fd[p_this][1]); //Ya no va a escribir más
    waitpid(-1, NULL, 0);//esperamos a que su hijo termine de ejecutarse
}

void proceso3(int **fd,int p_this,int p_prev){
    char buffer1[BUFSIZE];
    memset(buffer1,0,sizeof(buffer1));
    read(fd[p_prev][0], buffer1, BUFSIZE-1);
    close(fd[p_this][0]);
    int tam=strlen(buffer1);
    for(int i=0; i<tam; i++){
        buffer1[i]='a'<=buffer1[i] && buffer1[i]<='z'? buffer1[i]-('a'-'A'):buffer1[i];
    }
    write(fd[p_this][1], buffer1, BUFSIZE-1);
    close(fd[p_this][1]);
}

int main(int argc,char **argv){
    //cadena de procesos 

    int **fd=(int **)malloc(3*sizeof(int *));
    for(int i=0; i<3; i++){
        fd[i]=(int *)malloc(2*sizeof(int));
    }
    //creamos varios pipes
    
    for (int ii=0; ii<3; ii++) pipe(fd[ii]);

    int i=0;
    int p_this,p_prev;
    for(i=0; i<3; i++){
        calcular(&p_this,&p_prev,i, 3);
        if(fork()!=0){
            configPipas(i,fd,3); //cerramos las que no usamos
            if(i==0){
                proceso1(fd,p_this,p_prev);
            }
            else if(i==1){
                //leemos el mensaje
                proceso2(fd,p_this,p_prev);
                //enviamos
            }
            else {
                proceso3(fd,p_this,p_prev);
            }
            break;
        }
    }
    
    return 0;
}


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int na, char *argv[]){
	int **fd=(int **)malloc(3*sizeof(int *));
    for(int i=0; i<3; i++){
        fd[i]=(int *)malloc(2*sizeof(int));
    }
	for(int i=0; i<3; i++) pipe(fd[i]);
	int n,i,pid;
	if(na != 2) {
		fprintf(stderr, "Uso: %s <n>\n",argv[0]);
		exit(1);
	}
	n = atoi(argv[1]);
	int p_par,p_impar,p_12;
	for(i=0;i<3;i++) {
		if(!(pid = fork())) {//si es un proceso hijo
			int j,r, mypid;
			mypid = getpid();
			srand(mypid);
			int cont=0;			
			for(j=0;j<n;j++) { //
			    r = rand() % 528;
				if(r%2==0){ //si es par
					write(fd[0][1],&r,sizeof(r)); // escribe en el fd correspondiente
				}else write(fd[1][1],&r,sizeof(r));

				if(r%10==1 || r%10==2){ //si termina en 1 o 2 se le asigna a este pipe
					write(fd[2][1],&r,sizeof(r));
				}
				//printf("%d %d\n",mypid,r);
			} 
			int valor;
			for(int k=0; k<3; k++)close(fd[k][1]);
			int bytes;//imprimimos del pipe correspondiente
			while((bytes=read(fd[i][0],&valor,sizeof(valor)))>0){ //lee enteros hasta que se acaben
				printf("Numero %d impreso por el proceso %d\n",valor,mypid);
				cont++;
			}
			if(cont==0) printf("PID %d: Conjunto vacio\n",mypid);
			exit(0);//el hijo termina y sale del bucle   .
		}	
	}
	for(int k=0; k<3; k++){
		close(fd[k][0]);
		close(fd[k][1]);
	}
	
	exit(0);	
}	

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc,char*argv[]){
    int n=atoi(argv[1]);
	int **fd=(int **)malloc(n*sizeof(int *));
    for(int i=0; i<n; i++) fd[i]=(int *)malloc(2*sizeof(int));
    for(int i=0; i<n; i++) {
        if(pipe(fd[i])==-1){
            perror("pipe");
        }
    }
    int padre=getpid();
    int i;
    for(i=0;i<n-1; i++) {
        if(fork()!=0)break;
    }
    
    if(i==0){
        //elige un hijo y le digo que mate a todos
        int proOrden=(rand()%n);
        //printf("ORDEN %d\n",proOrden);
        for(int i=0; i<n; i++){
            write(fd[i][1],&proOrden,sizeof(proOrden)); //les digo 
        }
    }

    char command[20];
    int valor;
    //printf("fino %d\n",i);
    int bytes=read(fd[i][0],&valor,sizeof(valor)); //MUY IMPORTANTE RECIBIR ALGO, sino se queda en loop
    //printf("%d %d bytes\n",i,bytes);
    if(valor==i){ //este es el matador
        //cierro mi lectura y escritura
        snprintf(command,sizeof(command),"pstree -p %d",padre);
        system(command);
        close(fd[i][0]);
        close(fd[i][1]);
        int id;
        for(int j=1; j<n; j++){
            if(j<i){
                read(fd[j][0],&id,sizeof(id));
                snprintf(command,sizeof(command),"pstree -p %d",id);
                system(command);
                kill(id,SIGTERM);
                close(fd[j][0]);
                close(fd[j][1]);
            }else break;
        }
        
        for(int k=n-1; k>=0; k--){
            if(k>i){
                read(fd[k][0],&id,sizeof(id));
                snprintf(command,sizeof(command),"pstree -p %d",id);
                system(command);
                kill(id,SIGTERM);
                close(fd[k][0]);
                close(fd[k][1]);
            }
            else break;
        }
        //eliminamos al padre
        snprintf(command,sizeof(command),"pstree -p %d",padre);
        system(command);
        kill(padre,SIGTERM);
        snprintf(command,sizeof(command),"pstree -p %d",getpid());
        system(command);
    }
    else{
        //envio info por mi pipe sobre my pid
        int mypid=getpid();
        //printf("REACH %d \n",i);
        write(fd[i][1],&mypid,sizeof(mypid));
        close(fd[i][1]);
        //printf("LLEGUE %d \n",i);
        for(int k=0; k<n; k++){
            close(fd[k][0]);
            close(fd[k][1]);
        }
        pause();
    }
    return 0;
}

#include <stdio.h>

int main() {
    FILE *file = fopen("miarchivo.txt", "r");  // Abrir archivo en modo lectura
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;  // Termina si no se pudo abrir
    }
    
    // Si fopen() es exitoso, continuamos...
    printf("Archivo abierto exitosamente.\n");
    
    fclose(file);  // No olvides cerrar el archivo después de usarlo
    return 0;
}
#include <stdio.h>

int main() {
    FILE *file = fopen("miarchivo.txt", "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }
    
    char c;
    while ((c = fgetc(file)) != EOF) {  // Lee carácter por carácter hasta EOF
        putchar(c);  // Imprime el carácter leído
    }
    
    fclose(file);
    return 0;
}
#include <stdio.h>

int main() {
    FILE *file = fopen("miarchivo.txt", "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }
    
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {  // Lee línea por línea
        printf("%s", buffer);  // Imprime la línea leída
    }
    
    fclose(file);
    return 0;
}
#include <stdio.h>

int main() {
    FILE *file = fopen("miarchivo.dat", "rb");  // "rb" es para archivos binarios
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char buffer[100];
    size_t bytes_leidos = fread(buffer, sizeof(char), 100, file); // Lee hasta 100 bytes
    printf("Bytes leídos: %zu\n", bytes_leidos);

    fclose(file);
    return 0;
}