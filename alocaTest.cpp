#include "aloca.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(){
    //  TESTE DE ALOCAÇÃO
    meualoc* memoTest = new meualoc(8192,0);

    char* addr1 = memoTest->aloca(4096);

    printf("Imprimindo endereço alocado : %p\n", addr1);

    char* addr2 = memoTest->aloca(5096);

    printf("Imprimindo endereço alocado : %p", addr2);

    //  TESTE DE VERIFICAÇÃO
    printf("Teste do verifica: %d\n", memoTest->verifica(addr2));

    return 0;
}