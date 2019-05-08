#include "aloca.h"

//Construtor da classe meualoc
meualoc::meualoc(int tamanhoMemoria, int politicMem){
	memoria = (char *) malloc(sizeof(char)*tamanhoMemoria);
	politicaMem = politicMem;
	numeroMagico = 32384;
	//Lista de gerenciamento de memória livre
	espacosVazios = new MemoriaLivre();
	//Como a memória inteira está livre, o primeiro bloco de memória a ser inserido em MemoriaLivre é do tamanho da própria memória.
	espacosVazios->inserir(new Bloco(memoria,tamanhoMemoria));	//LUIZ ACHA ISSO MUITO FEIO, MAS SÓ ELE PENSA ASSIM.
}

//O tamanho solicitado para alocaçãopassado NÃO considera o tamanho do header do bloco de memória. É solicitado um tamanho N em BYTES, e caso esse esteja disponível, um SEGMENTO de N+4BYTES será subtraído da lista MemoriaLivre.
char* meualoc::aloca(unsigned short int tamanho){
	char* header;		//Ponteiro para o header
	char* bloco;		//Ponteiro para o primeito BYTE VÁLIDO do bloco alocado
	Valor tamanhoByte;
	Valor numeroMagicoByte;

	printf("[meualoc::aloca]: Alocando espaço...\n");

	//Ao alocarmos um novo bloco de memória, é necessário atualizar a lista MemoriaLivre, ou seja, remover um bloco da lista de memória livre.
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

/*
 * @brief Liberar um espaço alocado de memória é inserir um novo bloco em MemoriaLivre. Liberar um espaço de memória é inserir um bloco novo em MemoriaLivre.
 * 
 * @param ponteiro Endereço de memória do primeiro BYTE válido do bloco de memória a ser desalocado
 * @return int 
 */
int meualoc::libera(char* ponteiro){
	char* tempAddr;
	int tamanho = verifica(ponteiro, 0);

	printf("\n[LIBERA] Tamanho do bloco a ser liberado (sem o header): %d.\n", tamanho);

	if(	(tamanho <= 0)||(ponteiro == NULL)	){
		printf("\n[LIBERA] Erro: o endereço fornecido não se refere a um bloco válido de memória alocada.\n");
		return 1;
	}else{
		tamanho+=4;		//Tamanho do bloco somado ao tamanho do header.
		ponteiro-=4;	//Ponteiro agora aponta para o header.

		//Atualizando MemoriaLivre
		espacosVazios->inserir(new Bloco(ponteiro,tamanho));		
		
		//Liberando memória alocada
		while (tamanho >= 0)
		{
			tempAddr = ponteiro;
			tempAddr = NULL;
			--ponteiro;

			--tamanho;			
		}
		printf("\n[LIBERA] Bloco liberado com sucesso!\n");	

		espacosVazios->join(espacosVazios);
		return 0;	
	}
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