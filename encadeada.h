/*  Classe da lista encadeada por onde o alocador de memória fará o gerenciamento de memória livre */

#include <stdlib.h>
#include <stdio.h>


class Elemento{
    public:
        //ATRIBUTOS
        char* addr;     //Ponteiro para o primeiro byte válido do bloco de memória alocado
        int tamanho;    //Tamanho em BYTES do bloco de memória alocado
        Elemento* proximo;

        //METODOS
        Elemento(char* ponteiro, int tam);

        ~Elemento();
};

//Construtor da classe
Elemento::Elemento(char* ponteiro, int tam){
    addr = ponteiro;
    tamanho = tam;
    proximo = NULL;
}

class Encadeada{
    public:
        //ATRIBUTOS
        Elemento* primeiro;     //Ponteiro para o primeiro elemento da lista
        
        int numElementos;       //Quantidade de elementos contidos na lista
        //METODOS
        Encadeada();

        void inserir(Elemento* elem);

        char* buscar(unsigned short int tamanho, int opcao);

        int remover(Elemento* elem);

        ~Encadeada();
};

Encadeada::Encadeada(){
    primeiro = NULL;
    numElementos = 0;
}

void Encadeada::inserir(Elemento* elem){
    if(primeiro==NULL){
        primeiro = elem;
        numElementos += 1;
        printf("EncadeadaInserir - inserido na cabeca\n");
    }else{
        elem->proximo = primeiro;
        primeiro = elem;
        printf("EncadeadaInserir - inserido no inicio\n");
        numElementos += 1;
        printf("tamanho atual: %d\n",numElementos);
    }

    printf("Fim EncadeadaInserir\n");
}

char* Encadeada::buscar(unsigned short int tamanho, int opcao){
    //Um bloco válido de memória é constituído de um cabecalho de de 4BYTES + tamanho solicitado para alocação
    unsigned short int tamanhoTotal = tamanho+(sizeof(char)*4);
    
    //FIRST FIT
    if(opcao == 0){
        Elemento* auxiliar =  primeiro;
        while(auxiliar != NULL){
            if(auxiliar->tamanho >= tamanhoTotal){
                printf("EncadeadaBuscar - espaco vazio encontrado FF");
                char* auxiliar2 = auxiliar->addr;
                auxiliar->addr += tamanhoTotal;
                auxiliar->tamanho = auxiliar->tamanho - tamanhoTotal;  
                return auxiliar2;
            }else {
                auxiliar = auxiliar->proximo;
            }
            if(auxiliar == NULL){
                printf("EncadeadaBuscar - Sem espaco vazio disponivel\n");
                return NULL;
            }
        }
    }
    //BEST FIT
    if(opcao == 1){
        Elemento* auxiliar = primeiro;
        Elemento* menorSpace = NULL;
        while(auxiliar != NULL){
            if(auxiliar->tamanho >= (tamanho+(sizeof(char)*4))){
                if(menorSpace == NULL){
                    menorSpace = auxiliar;
                }else{
                    if(auxiliar->tamanho <= menorSpace->tamanho) {
                        menorSpace = auxiliar;
                    }
                }
            }
            auxiliar = auxiliar->proximo;
        }
        return menorSpace->addr;
    }
}