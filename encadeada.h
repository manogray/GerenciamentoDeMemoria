#include <stdlib.h>
#include <stdio.h>

class Elemento{
    public:
        char* addr;
        int tamanho;
        Elemento* proximo;
        Elemento(char* ponteiro, int tam);

        ~Elemento();
};

Elemento::Elemento(char* ponteiro, int tam){
    addr = ponteiro;
    tamanho = tamanho;
    proximo = NULL;
}

class Encadeada{
    Elemento* primeiro;
    int numElementos;
    public:
        Encadeada();

        void inserir(Elemento* elem);

        int buscar(Elemento* elem);

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
        printf("lista vazia - inserido na cabeca\n");
    }else{
        elem->proximo = primeiro;
        primeiro = elem;
        printf("lista com %d elementos - inserido no inicio\n",numElementos);
        numElementos += 1;
        printf("tamanho atual: %d\n",numElementos);
    }
}