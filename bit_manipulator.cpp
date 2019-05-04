#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <bitset>
#include <sstream>
#include <string.h>



// FUNCTIONS PROTOTYPE
const char* decToHex(unsigned short int decimal);

int main(int argc, char** argv){

    char* cabecalho = (char*)malloc(sizeof(char)*4);
    unsigned short int* subCabecalho = (unsigned short int*)(malloc(sizeof(int)*2));

    // Tamanho do bloco em bytes
    unsigned short int tamanhoBloco = 110;      
    // Número aleatório para determinar se um bloco de memória foi ou não alocado.
    unsigned short int numeroMagico = 32384;       
    // Máscara de bits
    unsigned short int mascara = 255;

    subCabecalho[0] = (numeroMagico & mascara);
    
    std::cout << "Antes da operação : " << numeroMagico << "\n";
    std::cout << "Aplicando a máscara: numeroMagico & mascara = " 
    << subCabecalho[0] << "\n";
    printf("subCabecalho[0] = %u\n", subCabecalho[0]);
    
    // Deslocamento à direita
    numeroMagico = numeroMagico >> 8;

    subCabecalho[1] = (numeroMagico & mascara);

    std::cout << "Depois do shift : " << numeroMagico << "\n";
    std::cout << "Aplicando a máscara: numeroMagico & mascara = " 
    << subCabecalho[1] << "\n";
    printf("subCabecalho[1] = %u\n", subCabecalho[1]);

    // DECIMAL TO HEX
    const char* test = decToHex(subCabecalho[0]);
    //? ADICIONAR CHARS INDIVIDUALMENTE NO CABECALHO
    std::cout << "Printing cabecalho[0] = test[0] : " << cabecalho[0] << "\n";
    test = decToHex(subCabecalho[1]);
    

    

    return 0;
}

// FUNCTIONS
const char* decToHex(unsigned short int decimal){
    const char* numberHex;
    std::stringstream ss;
    ss<< std::hex << decimal; // int decimal_value
    std::string res (ss.str());
    numberHex = res.c_str();
    std::cout << "Imprimindo decimal em hex : " << numberHex << "\n";

    return numberHex;
};

/*
unsigned short int hexToDec(char* hexNumber){}
    std::stringstream ss;
    ss  << hex_value ; // std::string hex_value
    ss >> std::hex >> decimal_value ; //int decimal_value
    std::cout << decimal_value ;

}*/