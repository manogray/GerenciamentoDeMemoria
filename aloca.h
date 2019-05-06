#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "encadeada.h"

//Decompõe um interio em BYTES e vice-versa
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
		int verifica(char* ponteiro);
		
		//Libera o espaco ocupado na posicao, de forma analoga ao free. Ou seja, liberar toda a memoria alocada para este ponteiro na funcao aloca.
		int libera(char* ponteiro);

		//Imprime o numero de elementos na lista de vazios, o maior e a media de tamanhos dos blocos vazios
		void imprimeDados();

		void imprimePolitica();

		~meualoc();
		Encadeada* espacosVazios;
};

//Construtor da classe meualoc
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
	char* header;
	char* bloco;
	Valor tamanhoByte;
	Valor numeroMagicoByte;

	//FIRST FIT
	if(politicaMem == 0){
		header = NULL;
		printf("meualocAloca - vou alocar espaco FF\n");
		bloco = espacosVazios->buscar(tamanho, politicaMem);
		if(bloco != NULL){
			header = bloco + (sizeof(char)*4); //JA ALOCOU
			tamanhoByte.valor = tamanho;
			numeroMagicoByte.valor = numeroMagico;
			bloco[0] = tamanhoByte.byte1;
			bloco[1] = tamanhoByte.byte0;//SALVOU DADOS DE HEADER
			bloco[2] = numeroMagicoByte.byte1;
			bloco[3] = numeroMagicoByte.byte0;
		}
		return header;		
	}
	//BEST FIT
	if(politicaMem == 1){
		return espacosVazios->buscar(tamanho, politicaMem);
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

int meualoc::verifica(char* ponteiro){
	if(ponteiro == NULL){
		return 0;
	}else{
		ponteiro -= 2;
		//Reconstruindo Número Mágico do endereço fornecido em formato unsigned short(2BYTES)
		Valor nMagic;
		nMagic.valor = 0;
		nMagic.byte1 = ponteiro[0];
		nMagic.byte0 = ponteiro[1];
		//Comparando Número Mágico do alocador com o Número Mágico do endereço fornecido
		//Se os números forem compatíveis, o endereço é de um bloco de válido memória alocada
		if(nMagic.valor == numeroMagico){
			ponteiro -=2;
			//Reconstruindo tamnho do bloco alocado em formato unsigned short (2BYTES)
			Valor tamanho;
			tamanho.valor = 0;
			tamanho.byte1 = ponteiro[0];
			tamanho.byte0 = ponteiro[1];
			//Retornando tamanho do bloco alocado
			return tamanho.valor;
		}else{
			//O endereço não corresponde a um bloco válido de memória alocada.
			return 0;
		}
	}
}