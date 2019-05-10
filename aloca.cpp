/* ARQUIVO DE TESTE PARA O ALOCADOR DE MEMORIA */
/**
 * @file aloca.cpp
 * @author EVALDO PATRIK DOS SANTOS CARDOSO - 21453640
 * @author JONATHAS GREGORIO KERBER - 21351288
 * @author LUIZ DE GONZAGA MOTA PINTO FILHO - 21753684
 * 
 * @version 0.1
 * @date 2019-05-10
 * 
 * @copyright Copyright (c) 2019
 */



#include "aloca.h"
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

int main(){
    //Valores de teste para alocação de memória
    int a = 1024, b = 2048, c = 4096, d = 65534;
    cout << "\t[TESTE DE ALOCAÇÃO DE MEMÓRIA]\n";
    printf("\n****************************************\n");
    printf("Máximo tamanho disponível para alocação:\n65530 BYTES (+4 BYTES HEADER)");
    printf("\n****************************************\n\n");
    
    //Criando bloco de memória principal (8KB = 8192BYTES)
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
    
    printf("\tAlocando %d BYTES\n", d-4);
    char* addr4 = memoTest->aloca(d-4);

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

    printf("\n****************************************\n");
    printf("Máximo tamanho disponível para alocação:\n65530 BYTES (+4 BYTES HEADER)");
    printf("\n****************************************\n\n");

    return 0;
}