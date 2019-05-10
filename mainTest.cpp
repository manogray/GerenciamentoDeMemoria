/* ARQUIVO DE TESTE PARA O ALOCADOR DE MEMORIA */
#include "aloca.h"
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

int main(){
    //Valores de teste para alocação de memória
    int a = 1024, b = 2048, c = 4096, d = 8192;
    cout << "\tTESTE DE ALOCAÇÃO DE MEMÓRIA\n";
    
    //Criando bloco de memória principal (8MB = 8192BYTES)
    meualoc* memoTest = new meualoc(d,1);

    printf("\tAlocando %d BYTES\n", a);
    char* addr1 = memoTest->aloca(a);

    printf("\tAlocando %d BYTES\n", b);
    char* addr2 = memoTest->aloca(b);

    printf("\tAlocando %d BYTES\n", c);
    char* addr3 = memoTest->aloca(c);

    //IMPRIMINDO ELEMENTOS EM MEMORIALIVRE
    memoTest->imprimeDados();
           
    
    //TESTANDO VERIFICADOR DE BLOCOS
    memoTest->verifica(addr1, 0);
    memoTest->verifica(addr2, 0);
    memoTest->verifica(addr3, 0);
    
    printf("\tAlocando %d BYTES\n", d);
    char* addr4 = memoTest->aloca(d);

    memoTest->verifica(addr1, 5120);
    memoTest->verifica(addr4, 5120);

    memoTest->libera(addr1);
    
    //IMPRIMINDO ELEMENTOS EM MEMORIALIVRE
    memoTest->imprimeDados();
    memoTest->libera(addr2);
    
    //IMPRIMINDO ELEMENTOS EM MEMORIALIVRE
    memoTest->imprimeDados();

    printf("\tAlocando %d BYTES\n", a);
    addr1 = memoTest->aloca(a);    

    //IMPRIMINDO ELEMENTOS EM MEMORIALIVRE
    memoTest->imprimeDados();

    memoTest->libera(addr1);
    memoTest->libera(addr3);
    memoTest->libera(addr4);

    //IMPRIMINDO ELEMENTOS EM MEMORIALIVRE
    memoTest->imprimeDados();

    memoTest->~meualoc();

    //IMPRIMINDO ELEMENTOS EM MEMORIALIVRE
    memoTest->imprimeDados();


    return 0;
}