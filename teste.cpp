#include <stdio.h>
#include <stdlib.h>

int main (){

    char* vetor = (char*) malloc(sizeof(char)*20);

    unsigned short int tamanho = 35;

    unsigned short int mascara = 255;

    unsigned short int numMagico = 32384;

    printf("tamanho antes: %u\nmascara: %u\n\n",numMagico,mascara);
    vetor[1] = (char) tamanho & mascara; //ULTIMOS 8 BITS DA VARIAVEL
    vetor[0] = (char) (tamanho >> 8) & mascara; //AVANCA 8 BITS E PEGA OS ULTIMOS 8BITS SEGUINTES

    vetor[5] = (char) numMagico & mascara;
    vetor[4] = (char) (numMagico >> 8) & mascara;

    
    unsigned short int tamanhoRecuperado = (vetor[0] * 256) + vetor[1]; //UNIR 8BITS + 8BITS PARA VARIAVEL DE 16BITS

    unsigned short int numMagicoRecuperado = (vetor[4] * 256) + vetor[5];

    printf("tamanho: %u\n\nnumeroMagico: %u\n\nchar1Magico: %u\nchar2Magico: %u\n\n",tamanhoRecuperado,numMagicoRecuperado,vetor[4],vetor[5]);

    return 0;
}