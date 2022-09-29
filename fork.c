#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
    int pid = fork();   //clona proceso que esta corriendo. 0 es hijo !=0 tiene un hijo.
    if(pid == 0){
         printf("Soy el proceso hijo\n");
         //execl("/workspace/TC1032.514/hola.exe", "hola.exe", NULL);
         //Puedes actualizar la carpeta de ejecutables para utilizar 
          execl("hola.exe", "hola.exe", NULL);
         sleep(5);
         printf("nunca");
    }else{
         printf("Soy el proceso padre\n");
         wait(NULL);
    }

return 0;
}