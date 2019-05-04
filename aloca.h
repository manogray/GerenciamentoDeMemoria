#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "encadeada.h"


union Valor
{
    uint32_t dword;

    struct
    {
        uint32_t valor;
    };

    struct
    {
        uint16_t word0;
        uint16_t word1;
    };

    struct
    {
        uint8_t byte0;
        uint8_t byte1;
        uint8_t byte2;
        uint8_t byte3;
    };
};

class meualoc{
	char* memoria; //char* pois eh byte a byte
    int politicaMem;
	unsigned short int numeroMagico;
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
		Encadeada* espacosVazios;
};

meualoc::meualoc(int tamanhoMemoria, int politicMem){
	memoria = (char *) malloc(sizeof(char)*tamanhoMemoria);
	politicaMem = politicMem;
	numeroMagico = 20596;
	espacosVazios = new Encadeada();
	//LISTA COM ESPACO TODO VAZIO
	Elemento* blocao = new Elemento(memoria,tamanhoMemoria);
	espacosVazios->inserir(blocao);
	
}

char* meualoc::aloca(unsigned short int tamanho){
	char* retorno;
	char* inicio;
	Valor numero1;
	Valor numero2;
	if(politicaMem == 0){//FIRST FIT
		printf("meualocAloca - vou alocar espaco FF\n");
		inicio = espacosVazios->buscar(tamanho,0);
		retorno = inicio + (sizeof(char)*4); //JA ALOCOU
		numero1.valor = tamanho;
		numero2.valor = numeroMagico;
		inicio[0] = numero1.byte1;
		inicio[1] = numero1.byte0;//SALVOU DADOS DE HEADER
		inicio[2] = numero2.byte1;
		inicio[3] = numero2.byte0;
		
	}
	if(politicaMem == 1){
		return espacosVazios->buscar(tamanho,1);
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

int meualoc::verifica(char* ponteiro, int posicao = 0){
	ponteiro -= 2;
	Valor nMagic;
	nMagic.valor = 0;
	nMagic.byte1 = ponteiro[0];
	nMagic.byte0 = ponteiro[1];
	
	if(nMagic.valor == numeroMagico){
		ponteiro -=2;
		Valor tamanho;
		tamanho.valor = 0;
		tamanho.byte1 = ponteiro[0];
		tamanho.byte0 = ponteiro[1];
		return tamanho.valor;
	}else{
		return 0;
	}
}