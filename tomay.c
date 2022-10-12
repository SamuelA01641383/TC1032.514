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
        if( may == 'A' || may == 'E' || may == 'I' || may == 'O' || may == 'U'){
            //printf("1");
             write(STDOUT_FILENO,&num,1);
        }
    }while(n != 0);
    printf("\n");
}