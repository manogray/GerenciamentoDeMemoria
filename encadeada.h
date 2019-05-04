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

char* Encadeada::buscar(int tamanho, int opcao){
    if(opcao == 0){//FIRST FIT
        Elemento* auxiliar =  primeiro;
        while(auxiliar != NULL){
            if(auxiliar->tamanho >= (tamanho+(sizeof(char)*4))){
                printf("EncadeadaBuscar - espaco vazio encontrado FF");
                return auxiliar->addr;
            }else {
                auxiliar = auxiliar->proximo;
            }
            if(auxiliar == NULL){
                printf("EncadeadaBuscar - Sem espaco vazio disponivel\n");
                return NULL;
            }
        }
    }

    if(opcao == 1){//BEST FIT
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