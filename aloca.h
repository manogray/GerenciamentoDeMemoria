#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "alocador.h"

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

		MemoriaLivre* espacosVazios;
	
		//tamanhoMemoria vai definir o tamanho da memória que o alocador vai utilizar
		//politicaMem define como escolher o bloco de onde saira a memória
		meualoc(int tamanhoMemoria,int politicaMem);

		//Pega um pedaco da variavel memoria e aloca, retornando o ponteiro para o comeco dessa regiao e atualizando a lista de espaços livres.
		char *aloca(unsigned short int tamanho);

		
		/* 
		 * @brief Verifica se a posicao dada pelo ponteiro esta alocada (checar se ponteiro[posicao] eh valido). Retorna o tamanho se estiver e 0 se nao.
		 * 
		 * @param ponteiro Endereço de memória no bloco principal.
		 * @return int Tamanho do bloco alocado; 0.
		 */
		int verifica(char* ponteiro, int posicao);
		
		int verificaNumeroMagico(char* ponteiro);
		
		//Libera o espaco ocupado na posicao, de forma analoga ao free. Ou seja, liberar toda a memoria alocada para este ponteiro na funcao aloca.
		int libera(char* ponteiro);

		//Imprime o numero de elementos na lista de vazios, o maior e a media de tamanhos dos blocos vazios
		void imprimeDados();

		void imprimePolitica();

		~meualoc();
};

//Construtor da classe meualoc
meualoc::meualoc(int tamanhoMemoria, int politicMem){
	memoria = (char *) malloc(sizeof(char)*tamanhoMemoria);
	politicaMem = politicMem;
	numeroMagico = 32384;
	//Lista de gerenciamento de memória livre
	espacosVazios = new MemoriaLivre();
	//Como a memória inteira está livre, o primeiro segmento de memória a ser inserido em MemoriaLivre é do tamanho da própria memória.
	espacosVazios->inserir(new Segmento(memoria,tamanhoMemoria));	//LUIZ ACHA ISSO MUITO FEIO, MAS SÓ ELE PENSA ASSIM.
}

//O tamanho solicitado para alocaçãopassado NÃO considera o tamanho do header do bloco de memória. É solicitado um tamanho N em BYTES, e caso esse esteja disponível, um SEGMENTO de N+4BYTES será subtraído da lista MemoriaLivre.
char* meualoc::aloca(unsigned short int tamanho){
	char* header;		//Ponteiro para o header
	char* bloco;		//Ponteiro para o primeito BYTE VÁLIDO do bloco alocado
	Valor tamanhoByte;
	Valor numeroMagicoByte;

	printf("[meualoc::aloca]: Alocando espaço...\n");

	//Ao alocarmos um novo bloco de memória, é necessário atualizar a lista MemoriaLivre.
	header = NULL;	
	header = espacosVazios->buscar(tamanho, politicaMem);
	if(header != NULL){
		bloco = header + (sizeof(char)*4); //JA ALOCOU
		tamanhoByte.valor = tamanho;
		numeroMagicoByte.valor = numeroMagico;
		header[0] = tamanhoByte.byte1;
		header[1] = tamanhoByte.byte0;
		header[2] = numeroMagicoByte.byte1;
		header[3] = numeroMagicoByte.byte0;	//SALVOU DADOS DE HEADER
		printf("%d BYTES alocados em %p\n\n", tamanhoByte.valor, bloco);

		return bloco;	

	}else{
		printf("Memória não alterada.\n");
		return NULL;
	}	
}

int meualoc::verifica(char* ponteiro, int posicao){
	if(ponteiro == NULL){
		printf("[VERIFICA] ERRO: ponteiro nulo!\n");
		return -1;
	}

	char* header = ponteiro-4;
	char* addrSobConsulta = ponteiro+posicao;
	Valor tamanhoSobConsulta;

	if(verificaNumeroMagico(ponteiro) == 0){
		tamanhoSobConsulta.byte1 = header[0];
		tamanhoSobConsulta.byte0 = header[1];

		if(	(ponteiro+tamanhoSobConsulta.valor) >= addrSobConsulta	){
			return tamanhoSobConsulta.valor;
		}else{
			printf("[VERIFICA] Erro: offset fora dos limites do bloco alocado.\n");
		}
	}else{
		return 0;
	}
}

int meualoc::verificaNumeroMagico(char* ponteiro){
	char* halfHeader = ponteiro-2;
	char* aux = NULL;
	Valor tamanhoTotal, auxNumeroMagico;
	
	//Verificando se ponteiro se refere a um bloco válido de alocação
	auxNumeroMagico.byte1 = halfHeader[0];
	auxNumeroMagico.byte0 = halfHeader[1];

	if(numeroMagico != auxNumeroMagico.valor){
		printf("[VERIFICA NUMERO MAGICO] Erro: o endereço fornecido não corresponde a um bloco válido de memória alocada.\n");
		return 1;
	}else{
		printf("[VERIFICA NUMERO MAGICO] Endereço válido.\n");
		return 0;
	}
}

/**
 * @brief Liberar um espaço alocado de memória é inserir um novo bloco em MemoriaLivre
 * 
 * @param ponteiro Endereço de memória do primeiro BYTE válido do bloco de memória a ser desalocado
 * @return int 
 */
int meualoc::libera(char* ponteiro){
	if(ponteiro == NULL){
		printf("[LIBERA] ERROR: ponteiro nulo!\n");
		return 1;
	}
	char* header = ponteiro-4;
	char* aux = NULL;
	Valor tamanhoTotal;
	
	if(verificaNumeroMagico(ponteiro) == 0){
		printf("Der certo %d\n", verificaNumeroMagico(ponteiro));
	};

};


void imprimeDados();

void meualoc::imprimePolitica(){
	printf("aqui e a politica: %d\n",politicaMem);
}

meualoc::~meualoc(){
	delete[] memoria;
	politicaMem = -1;
	printf("Objeto destruido!\n");
}