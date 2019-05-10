/*  Classe da lista encadeada por onde o alocador de memória fará o gerenciamento de memória livre */
using namespace std;

//Célula contendo o endereço e o tamanho de um segmento de memória livre, e um ponteiro para a próxima célula do mesmo tipo, ambas dentro do segmento principal de memória,
class Segmento{
    public:
        //ATRIBUTOS
        char* addr;     //Ponteiro para o primeiro byte válido do segmento de memória alocado. Como o segmento de memória principal é um vetor de char, para armazenar um endereço desse segmento utiliza-se um ponteiro para char.
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

//Lista de segmentos de memória livre dentro do segmento de memória principal
class MemoriaLivre{
    public:
        //ATRIBUTOS
        Segmento* primeiro;     //Ponteiro para o primeiro segmento da lista   
        int numSegmentos;       //Quantidade de segmentos contidos na lista
        
        //METODOS -  Operações a serem realizadas na lista
        MemoriaLivre();

        void inserir(Segmento* segmento);   //Inserir novo segmento na lista

        char* buscar(unsigned short int tamanho, int politicaMemoria);    //Buscar por um espaço

        void join(MemoriaLivre* memoriaLivre);

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
        printf("\n\n[INSERIR] Inserido na cabeca\n");
    }else{
        segmento->proximo = primeiro;
        primeiro = segmento;
        printf("\n[INSERIR] Inserido no inicio, ");
        numSegmentos += 1;
        printf("número de segmentos livres: %d\n",numSegmentos);
    }
    printf("[INSERIR] Fim\n\n");
}

//Retorna um PONTEIRO para o HEADER do ENDEREÇO DO BLOCO DE MEMÓRIA suficientemente grande para comportar a quantidade de memória solicitada para alocação. A busca automaticamente subtrai de MemoriaLivre o segmento de memória solicitado para alocação. Alocar memória é subtrair da MemoriaLivre.
char* MemoriaLivre::buscar(unsigned short int tamanho, int politicaMemoria){
    //Um segmento válido de memória é constituído de um header de 4BYTES + tamanho solicitado para alocação
    unsigned short int tamanhoTotal = tamanho+(sizeof(char)*4);
    char* addrAux;
    Segmento* segmentoAux =  primeiro;  //Primeiro Segmento da lista MemoriaLivre.
    

    //FIRST FIT
    if(politicaMemoria == 0){
        while(segmentoAux != NULL){
            printf("[POLÍTICA DE ALOCAÇÃO: FIRST FIT]\n\tTamanho do segmento disponível para alocação: %d BYTES\n\tTamanho total solicitado: %d BYTES.\n\n", segmentoAux->tamanho, tamanhoTotal);
            if(segmentoAux->tamanho >= tamanhoTotal){
                addrAux = segmentoAux->addr;
                segmentoAux->addr += tamanhoTotal+1;
                segmentoAux->tamanho = segmentoAux->tamanho - tamanhoTotal;
                printf("\t[FIRST FIT] Tamanho do segmento selecionado para alocação: %d\n", segmentoAux->tamanho);     
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
        Segmento* segmentoAnterior = NULL;
        Segmento* segmentoBuffer = primeiro;

        while(segmentoAux != NULL){
            //SegmentoAux possui espaço suficiente para alocar a quantidade de memória solicitada.
            printf("[POLÍTICA DE ALOCAÇÃO: BEST FIT]\n\tTamanho do segmento disponível para alocação: %d BYTES\n\tTamanho total solicitado: %d BYTES.\n\n", segmentoAux->tamanho, tamanhoTotal);
            if(segmentoAux->tamanho >= tamanhoTotal){
                //Na primeira iteração da busca, o primeiro segmento no qual o segmento requisitado couber, será considerado como a melhor opção para a alocação de memória.
                if(bestFit == NULL){
                    bestFit = segmentoAux;
                }else{
                    //Após a primeira iteração da busca, se houver um espaço livre menor no qual a quantidade de memória solicitada couber, esse espaço será considerado como o best fit para a alocação.
                    if(segmentoAux->tamanho <= bestFit->tamanho){
                        bestFit = segmentoAux;
                        printf("\t[BEST FIT] Tamanho do segmento selecionado para alocação: %d\n", bestFit->tamanho);
                        segmentoAnterior = segmentoBuffer;
                        segmentoAnterior->proximo = bestFit;
                    }
                }
            }
            //Continua a busca através da lista.
            segmentoBuffer = segmentoAux;              
            segmentoAux = segmentoAux->proximo;            
        }
        if(bestFit == NULL){
            printf("Sem espaço vazio disponivel\n");
            return NULL;
        }else{
            addrAux = bestFit->addr;            
            bestFit->addr += tamanhoTotal+5; //addr APONTA PARA O PRIMEIRO BYTE VÁLIDO DE MEMÓRIA ALOCADA, NÃO PARA O HEADER DO SEGMENTO.            
            bestFit->tamanho = bestFit->tamanho - tamanhoTotal;
            
            return addrAux;
        }
    } 
}

void MemoriaLivre::join(MemoriaLivre* MemoriaLivre){
    Segmento* atual = MemoriaLivre->primeiro;
    char* addrAtual = atual->addr;
    int tamanhoAtual = atual->tamanho;
    Segmento* seguinte;

    
    while(atual->proximo != NULL){
        seguinte = atual->proximo;
        char* addrSeguinte = seguinte->addr;
        int tamanhoSeguinte = seguinte->tamanho;

        //Segmentos contíguos encontrados
        if( (addrSeguinte-1) == (addrAtual+tamanhoAtual)  ){
            printf("\t[JOIN] Segmentos contíguos encontrados nos endereços %p e %p.\n", addrAtual, addrSeguinte);
            atual->proximo = seguinte->proximo;
            atual->tamanho = atual->tamanho + (seguinte->tamanho) + 4;   //4BYTES do header
            MemoriaLivre->numSegmentos-=1;
            seguinte->proximo = NULL;

            //Limpando o header antigo
            char* aux = addrSeguinte;
            for(int i=0; i<4; i++){
                addrSeguinte=NULL;
                addrSeguinte=aux++;
            }
            aux = NULL;
        }else{
            atual = atual->proximo;
        }
    }
}

MemoriaLivre::~MemoriaLivre(){
    Segmento* auxSeg;

	printf("[MEMORIA LIVRE] Destruindo elementos de MemoriaLivre.\n");
	for(int i = 0; numSegmentos >0; i++){
		printf("[DESTRUCTOR] Faltam %d elementos em MemoriaLivre.\n", numSegmentos);
		auxSeg = primeiro;
        auxSeg->~Segmento();
        numSegmentos--;

		if(primeiro->proximo != NULL){
			primeiro = primeiro->proximo;
		}
		
	}
    printf("[MEMORIA LIVRE] Objeto destruido!\n");
}

Segmento::~Segmento(){
    printf("\n\t[SEGMENTO] Destruído!\n\n");
    addr =  NULL;
    delete addr;
    proximo = NULL;
    delete proximo;
}