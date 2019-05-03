#include <stdlib.h>
#include <stdio.h>
#include "encadeada.h"

class meualoc{
	char* memoria; //char* pois eh byte a byte
    int politicaMem;
	Encadeada* espacosVazios = new Encadeada();
	public:
		//tamanhoMemoria vai definir o tamanho da memória que o alocador vai utilizar
		//politicaMem define como escolher o bloco de onde saira a memória
		meualoc(int tamanhoMemoria,int politicaMem);

		//Pega um pedaco da variavel memoria e aloca, retornando o ponteiro para o comeco dessa regiao e atualizando a lista de livres.
		char *aloca(unsigned short int tamanho);

		//Verifica se a posicao dada pelo ponteiro esta alocada (checar se ponteiro[posicao] eh valido). Retorna o tamanho se estiver e 0 se nao
		int verifica(char* ponteiro,int posicao=0);
		
		//Libera o espaco ocupado na posicao, de forma analoga ao free. Ou seja, liberar toda a memoria alocada para este ponteiro na funcao aloca.
		int libera(char* ponteiro);

		//Imprime o numero de elementos na lista de vazios, o maior e a media de tamanhos dos blocos vazios
		void imprimeDados();

		void imprimePolitica();

		~meualoc();
};

meualoc::meualoc(int tamanhoMemoria, int politicMem){
	memoria = (char *) malloc(sizeof(char)*tamanhoMemoria);
	politicaMem = politicMem;
	//LISTA COM ESPACO TODO VAZIO
	Elemento* blocao = new Elemento(memoria,tamanhoMemoria);
}

char* meualoc::aloca(unsigned short int tamanho){
	if(politicaMem == 0){//FIRST FIT
		return espacosVazios->buscar(tamanho,0);
	}
}

meualoc::~meualoc(){
	delete[] memoria;
	politicaMem = -1;
	printf("Objeto destruido!\n");
}

void meualoc::imprimePolitica(){
	printf("aqui e a politica: %d\n",politicaMem);
}