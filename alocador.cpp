#include "alocador.h"
#include <iostream>

//Construtor MemoriaLivre
MemoriaLivre::MemoriaLivre(){
    printf("Criando lista encadeada de MemoriaLivre\n");
    primeiro = NULL;
    numBlocos = 0;
}

void MemoriaLivre::inserir(Bloco* bloco){
//Se um novo bloco é inserido na LISTA DE ESPAÇOS LIVRES, significa que a memória está sendo menos utilizada.
    //A lista de MemoriaLivre está vazia. Novo bloco é inserido na cabeça da lista.
    if(primeiro==NULL){
        primeiro = bloco;
        numBlocos += 1;
        printf("MemoriaLivreInserir - inserido na cabeca\n");
    }else{
        bloco->proximo = primeiro;
        primeiro = bloco;
        printf("MemoriaLivreInserir - inserido no inicio\n");
        numBlocos += 1;
        printf("tamanho atual: %d\n",numBlocos);
    }
    printf("Fim MemoriaLivreInserir\n");
}

//Retorna um PONTEIRO para o HEADER do ENDEREÇO DO BLOCO DE MEMÓRIA suficientemente grande para comportar a quantidade de memória solicitada para alocação. A busca automaticamente remove de MemoriaLivre o bloco de memória solicitado para alocação. Alocar memória é subtrair da MemoriaLivre.
char* MemoriaLivre::buscar(unsigned short int tamanho, int politicaMemoria){
    //Um bloco válido de memória é constituído de um header de 4BYTES + tamanho solicitado para alocação
    unsigned short int tamanhoTotal = tamanho+(sizeof(char)*4);
    char* addrAux;
    Bloco* blocoAux =  primeiro;  //Primeiro Bloco da lista MemoriaLivre.
    

    //FIRST FIT
    if(politicaMemoria == 0){
        while(blocoAux != NULL){
            printf("Imprimindo tamanho do bloco em verificação em MemoriaLivre::buscar %d\n", blocoAux->tamanho);
            if(blocoAux->tamanho >= tamanhoTotal){
                printf("[FIRST FIT] Memória disponível para alocação: %d\n", blocoAux->tamanho);
                addrAux = blocoAux->addr;
                blocoAux->addr += tamanhoTotal;
                blocoAux->tamanho = blocoAux->tamanho - tamanhoTotal;
                return addrAux;
            }else {
                blocoAux = blocoAux->proximo;
            }            
        }
        if(blocoAux == NULL){
            printf("Sem espaco livre disponivel\n");
            return NULL;
        }
    //BEST FIT
    }else{
        Bloco* bestFit = NULL;
        while(blocoAux != NULL){
            printf("Imprimindo tamanho do bloco em verificação em MemoriaLivre::buscar %d\n", blocoAux->tamanho);
            //BlocoAux possui espaço suficiente para alocar a quantidade de memória solicitada.
            if(blocoAux->tamanho >= tamanhoTotal){
                //Na primeira iteração da busca, o primeiro bloco no qual o bloco requisitado couber, será considerado como a melhor opção para a alocação de memória.
                if(bestFit == NULL){
                    bestFit = blocoAux;
                    printf("[BEST FIT] Memória disponível para alocação: %d\n", bestFit->tamanho);
                }else{
                    //Após a primeira iteração da busca, se houver um espaço livre menor no qual a quantidade de memória solicitada couber, esse espaço será considerado como o best fit para a alocação.
                    if(blocoAux->tamanho <= bestFit->tamanho) {
                        bestFit = blocoAux;
                    }
                }
            }
            //Continua a busca através da lista.
            blocoAux = blocoAux->proximo;
        }
        if(bestFit == NULL){
            printf("Sem espaco vazio disponivel\n");
            return NULL;
        }else{
            addrAux = bestFit->addr;
            bestFit->addr += tamanhoTotal;
            bestFit->tamanho = bestFit->tamanho - tamanhoTotal;
            //Removendo bloco da lista MemoriaLivre
            return addrAux;
        }
    } 
}

void MemoriaLivre::join(MemoriaLivre* MemoriaLivre){
    Bloco* atual = MemoriaLivre->primeiro;
    char* addrAtual = atual->addr;
    int tamanhoAtual = atual->tamanho;
    Bloco* seguinte;
    
    printf("\n[JOIN]\n");
    
    while(atual->proximo != NULL){
        printf("\n\t[JOIN] Entrou no while\n");
        seguinte = atual->proximo;
        char* addrSeguinte = seguinte->addr;
        int tamanhoSeguinte = seguinte->tamanho;

        printf("\n\t\t[JOIN] Antes do if\n");
        if( (addrSeguinte-1) == (addrAtual+tamanhoAtual)  ){
            printf("[JOIN] Encontrados blocos contíguos de memória livre.\n");
            atual->proximo = seguinte->proximo;
            atual->tamanho = (seguinte->tamanho) + 4;   //4BYTES do header

            seguinte->proximo = NULL;
            for(int i=0; i<4;i++){
                addrSeguinte=NULL;
                addrSeguinte++;
            }
        }else{
            atual = atual->proximo;
        }
    }
}