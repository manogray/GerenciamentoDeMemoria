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

    cout << "\tAlocando 4096 BYTES\n";
    char* addr1 = memoTest->aloca(2048);
    
    cout << "\tAlocando 2048 BYTES\n";
    char* addr2 = memoTest->aloca(4096);
    
    cout << "\tAlocando 4096 BYTES\n";
    char* addr3 = memoTest->aloca(4096);
    
    //TESTANDO VERIFICADOR DE BLOCOS
    printf("\tTeste do verificador de blocos: %d\n", memoTest->verifica(addr1));
    printf("\tTeste do verificador de blocos: %d\n", memoTest->verifica(addr2));
    printf("\tTeste do verificador de blocos: %d\n", memoTest->verifica(addr3));

    return 0;
}