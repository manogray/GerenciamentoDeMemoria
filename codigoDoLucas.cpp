#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    char* vetor = (char*) malloc(sizeof(char)*20);

    unsigned short int valor = 32384;

    vetor = (char*)&valor;
    printf("%p = %p \n",(char*)&valor,vetor);

    unsigned short int* con = (unsigned short int*) vetor;
    unsigned short int confirma = *con;
    printf("%d = %d",valor,confirma);

    return 0;
}