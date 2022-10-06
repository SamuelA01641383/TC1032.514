#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int terminar;
void hola(int signalNumb){
    printf("Recibi la senal %d", signalNumb);
}

void terminarWhile(int sigNumber){
    if(sigNumber == 12){
            terminar = 1;
            printf("Terminando while\n");
        }
}

int main(){
    terminar = 0;
   //matar al recibir señal 12
    signal(12, hola); //Señal y función a ejecutar
    signal(12, terminarWhile);
    //signal(2, hola); //Control C
    while(terminar == 0){
        printf("trabajando\n");
        sleep(1);
    }
    printf("Aqui nunca llega");
    return 0;
}