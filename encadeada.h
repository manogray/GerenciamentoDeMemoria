/*  Classe da lista encadeada por onde o alocador de memória fará o gerenciamento de memória livre */

#include <stdlib.h>
#include <stdio.h>

//Célula contendo o endereço e o tamanho de um segmento de memória livre, e um ponteiro para a próxima célula do mesmo tipo, ambas dentro do bloco principal de memória,
class Elemento{
    public:
        //ATRIBUTOS
        char* addr;     //Ponteiro para o primeiro byte válido do bloco de memória alocado. Como o bloco de memória principal é um vetor de char, para armazenar um endereço desse bloco utiliza-se um ponteiro para char.
        int tamanho;    //Tamanho em BYTES do segmento de memória alocado
        
        Elemento* proximo;  //Ponteiro para uma segunda instância da classe Elemento.

        //METODOS
        //Construtor
        Elemento(char* ponteiro, int tam);
        //Destrutor
        ~Elemento();
};

//Construtor Elemento
Elemento::Elemento(char* ponteiro, int tam){
    addr = ponteiro;
    tamanho = tam;
    proximo = NULL;
}

//Lista de segmentos (elementos) de memória livre dentro do bloco de memória principal
class Encadeada{
    public:
        //ATRIBUTOS
        Elemento* primeiro;     //Ponteiro para o primeiro elemento da lista   
        int numElementos;       //Quantidade de elementos contidos na lista
        
        //METODOS -  Operações a serem realizadas na lista
        Encadeada();

        void inserir(Elemento* elem);   //Inserir novo elemento na lista

        char* buscar(unsigned short int tamanho, int politicaMemoria);    //Buscar por um espaço

        int remover(Elemento* elem);

        ~Encadeada();
};

//Construtor Encadeada
Encadeada::Encadeada(){
    primeiro = NULL;
    numElementos = 0;
}

void Encadeada::inserir(Elemento* elem){
//Se um novo elemento é inserido na LISTA DE ESPAÇOS LIVRES, significa que a memória está sendo menos utilizada.
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

//Retorna um PONTEIRO com para o HEADER do ENDEREÇO DO BLOCO DE MEMÓRIA suficientemente livre para comportar a quantidade de memória solicitada para alocação.
char* Encadeada::buscar(unsigned short int tamanho, int politicaMemoria){
    //Um bloco válido de memória é constituído de um cabecalho de 4BYTES + tamanho solicitado para alocação
    unsigned short int tamanhoTotal = tamanho+(sizeof(char)*4);
    char* addrAux;
    Elemento* elementoAux =  primeiro;

    printf("EncadeadaBuscar\n");
    //FIRST FIT
    if(politicaMemoria == 0){
        while(elementoAux != NULL){
            if(elementoAux->tamanho >= tamanhoTotal){
                printf("Espaco vazio encontrado FF.\n");
                addrAux = elementoAux->addr;
                elementoAux->addr += tamanhoTotal;
                elementoAux->tamanho = elementoAux->tamanho - tamanhoTotal;
                printf("Alocado com sucesso!\n"); 
                return addrAux;
            }else {
                elementoAux = elementoAux->proximo;
            }            
        }
        if(elementoAux == NULL){
            printf("Sem espaco vazio disponivel\n");
            return NULL;
        }
    //BEST FIT
    }else{
        Elemento* bestFit = NULL;
        while(elementoAux != NULL){
            //ElementoAux possui espaço suficiente para alocar a quantidade de memória solicitada.
            if(elementoAux->tamanho >= tamanhoTotal){
                //Na primeira iteração da busca, o primeiro segmento no qual o bloco requisitado couber, será considerado como a melhor opção para a alocação de memória.
                if(bestFit == NULL){
                    printf("Espaco vazio encontrado BF.\n");
                    bestFit = elementoAux;
                }else{
                    //Após a primeira iteração da busca, se houver um espaço livre menor no qual a quantidade de memória solicitada couber, esse espaço será considerado como o best fit para a alocação.
                    if(elementoAux->tamanho <= bestFit->tamanho) {
                        bestFit = elementoAux;
                    }
                }
            }
            //Continua a busca através da lista.
            elementoAux = elementoAux->proximo;
        }
        if(bestFit == NULL){
            printf("Sem espaco vazio disponivel\n");
            return NULL;
        }else{
            addrAux = bestFit->addr;
            bestFit->addr += tamanhoTotal;
            bestFit->tamanho = bestFit->tamanho - tamanhoTotal;
            printf("Alocado com sucesso!\n\n");
            return addrAux;
        }
    } 
}