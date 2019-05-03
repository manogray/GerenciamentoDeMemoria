#include <stdlib.h>
#include <stdio.h>

class Elemento{
    public:
        //ATRIBUTOS
        char* addr;
        int tamanho;
        Elemento* proximo;
        //METODOS
        Elemento(char* ponteiro, int tam);

        ~Elemento();
};

Elemento::Elemento(char* ponteiro, int tam){
    addr = ponteiro;
    tamanho = tam;
    proximo = NULL;
}

class Encadeada{
    public:
        //ATRIBUTOS
        Elemento* primeiro;
        
        int numElementos;
        //METODOS
        Encadeada();

        void inserir(Elemento* elem);

        char* buscar(int tamanho, int opcao);

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

char* Encadeada::buscar(int tamanho, int opcao){
    if(opcao == 0){//FIRST FIT
        Elemento* auxiliar = primeiro;
        while(auxiliar != NULL){
            if(auxiliar->tamanho >= (tamanho+(sizeof(char)*4))){
                return auxiliar->addr;
            }else {
                auxiliar = auxiliar->proximo;
            }
        }
    }

    if(opcao == 1){//BEST FIT

    }
}