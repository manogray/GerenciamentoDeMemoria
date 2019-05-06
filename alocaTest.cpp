/* ARQUIVO DE TESTE PARA O ALOCADOR DE MEMORIA */
#include "aloca.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(){
    cout << "\tTESTE DE ALOCAÇÃO DE MEMÓRIA\n";

    //Criando bloco de memória principal (8MB = 8192BYTES)
    meualoc* memoTest = new meualoc(8192,0);
    printf("Imprimindo endereço inicial do bloco de memória principal : %p\n", memoTest);

    cout << "\tAlocando 4096 BYTES\n";
    char* addr1 = memoTest->aloca(4096);
    printf("Imprimindo endereço alocado : %p\n", addr1);

    cout << "\tAlocando 5096 BYTES\n";
    char* addr2 = memoTest->aloca(8192);
    printf("Imprimindo endereço alocado : %p\n", addr2);

    //TESTANDO VERIFICADOR DE BLOCOS
    printf("\tTeste do verificador de blocos com endereço válido: %d\n", memoTest->verifica(addr1));
    printf("\tTeste do verificador de blocos com endereço inválido: %d\n", memoTest->verifica(addr2));

    return 0;
}