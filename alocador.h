/*  Classe da lista encadeada por onde o alocador de memória fará o gerenciamento de memória livre */

#include <stdlib.h>
//#include <stdio.h>

//Célula contendo o endereço e o tamanho de um segmento de memória livre, e um ponteiro para a próxima célula do mesmo tipo, ambas dentro do bloco principal de memória,
class Segmento{
    public:
        //ATRIBUTOS
        char* addr;     //Ponteiro para o primeiro byte válido do bloco de memória alocado. Como o bloco de memória principal é um vetor de char, para armazenar um endereço desse bloco utiliza-se um ponteiro para char.
        int tamanho;    //Tamanho em BYTES do segmento de memória alocado
        Segmento* proximo;  //Ponteiro para o próximo Segmento da lista.

        //METODOS
        //Construtor
        Segmento(char* ponteiro, int tam);
        //Destrutor
        ~Segmento();
};

//Construtor Segmento
Segmento::Segmento(char* ponteiro, int tam){
    addr = ponteiro;
    tamanho = tam;
    proximo = NULL;
}

//Lista de segmentos (elementos) de memória livre dentro do bloco de memória principal
class MemoriaLivre{
    public:
        //ATRIBUTOS
        Segmento* primeiro;     //Ponteiro para o primeiro elemento da lista   
        int numSegmentos;       //Quantidade de elementos contidos na lista
        
        //METODOS -  Operações a serem realizadas na lista
        MemoriaLivre();

        void inserir(Segmento* elem);   //Inserir novo elemento na lista

        char* buscar(unsigned short int tamanho, int politicaMemoria);    //Buscar por um espaço

        int remover(Segmento* elem);

        ~MemoriaLivre();
};

//Construtor MemoriaLivre
MemoriaLivre::MemoriaLivre(){
    printf("Criando lista encadeada de MemoriaLivre\n");
    primeiro = NULL;
    numSegmentos = 0;
}

void MemoriaLivre::inserir(Segmento* segmento){
//Se um novo segmento é inserido na LISTA DE ESPAÇOS LIVRES, significa que a memória está sendo menos utilizada.
    //A lista de MemoriaLivre está vazia. Novo segmento é inserido na cabeça da lista.
    if(primeiro==NULL){
        primeiro = segmento;
        numSegmentos += 1;
        printf("MemoriaLivreInserir - inserido na cabeca\n");
    }else{
        segmento->proximo = primeiro;
        primeiro = segmento;
        printf("MemoriaLivreInserir - inserido no inicio\n");
        numSegmentos += 1;
        printf("tamanho atual: %d\n",numSegmentos);
    }
    printf("Fim MemoriaLivreInserir\n");
}

//Retorna um PONTEIRO para o HEADER do ENDEREÇO DO BLOCO DE MEMÓRIA suficientemente grande para comportar a quantidade de memória solicitada para alocação. A busca automaticamente remove de MemoriaLivre o bloco de memória solicitado para alocação. Alocar memória é subtrair da MemoriaLivre.
char* MemoriaLivre::buscar(unsigned short int tamanho, int politicaMemoria){
    //Um bloco válido de memória é constituído de um header de 4BYTES + tamanho solicitado para alocação
    unsigned short int tamanhoTotal = tamanho+(sizeof(char)*4);
    char* addrAux;
    Segmento* segmentoAux =  primeiro;  //Primeiro Segmento da lista MemoriaLivre.
    

    //FIRST FIT
    if(politicaMemoria == 0){
        while(segmentoAux != NULL){
            printf("Imprimindo tamanho do segmento em verificação em MemoriaLivre::buscar %d\n", segmentoAux->tamanho);
            if(segmentoAux->tamanho >= tamanhoTotal){
                printf("[FIRST FIT] Memória disponível para alocação: %d\n", segmentoAux->tamanho);
                addrAux = segmentoAux->addr;
                segmentoAux->addr += tamanhoTotal;
                segmentoAux->tamanho = segmentoAux->tamanho - tamanhoTotal;
                return addrAux;
            }else {
                segmentoAux = segmentoAux->proximo;
            }            
        }
        if(segmentoAux == NULL){
            printf("Sem espaco livre disponivel\n");
            return NULL;
        }
    //BEST FIT
    }else{
        Segmento* bestFit = NULL;
        while(segmentoAux != NULL){
            printf("Imprimindo tamanho do segmento em verificação em MemoriaLivre::buscar %d\n", segmentoAux->tamanho);
            //SegmentoAux possui espaço suficiente para alocar a quantidade de memória solicitada.
            if(segmentoAux->tamanho >= tamanhoTotal){
                //Na primeira iteração da busca, o primeiro segmento no qual o bloco requisitado couber, será considerado como a melhor opção para a alocação de memória.
                if(bestFit == NULL){
                    bestFit = segmentoAux;
                    printf("[BEST FIT] Memória disponível para alocação: %d\n", bestFit->tamanho);
                }else{
                    //Após a primeira iteração da busca, se houver um espaço livre menor no qual a quantidade de memória solicitada couber, esse espaço será considerado como o best fit para a alocação.
                    if(segmentoAux->tamanho <= bestFit->tamanho) {
                        bestFit = segmentoAux;
                    }
                }
            }
            //Continua a busca através da lista.
            segmentoAux = segmentoAux->proximo;
        }
        if(bestFit == NULL){
            printf("Sem espaco vazio disponivel\n");
            return NULL;
        }else{
            addrAux = bestFit->addr;
            bestFit->addr += tamanhoTotal;
            bestFit->tamanho = bestFit->tamanho - tamanhoTotal;
            return addrAux;
        }
    } 
}


