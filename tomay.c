//PRACTICA 3
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

int main(){
    char c;
    char may;
    int n;

//Escribir algo
//Ctrl d para terminar
    do{
        char num = '1';
        n = read(STDIN_FILENO,&c,1);
        may = toupper(c);
        write(STDOUT_FILENO,&may,1);
    }while(n != 0);
    printf("\n");
}