/*  Programa manipulador de bits    */
/*  NÃO ESTÁ FUNCIONANDO    */
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <bitset>
#include <cstddef>

//  ENVIRONMENT VARIABLES
using namespace std;

//  PROTOTYPES



int main(int argc, char** argv){
    
    char* header = (char*)malloc(sizeof(char)*4);   //  HEADER HAS LENGHT OF 4 BYTES
                                                    //  HEADER = {SIZE, MAGICNUMBER}
    unsigned int magicNumber = 32384;               //  MEMORY BLOCK VERIFICATION NUMBER
    unsigned int size = 110;                        //  SIZE OF THE ALOCATED BLOCK OF MEMORY
    unsigned int bitMask = 255;
    unsigned char maskedByte1, maskedByte2;


    maskedByte2 = (magicNumber & bitMask);

    uint8_t slidePressure = (uint8_t)atoi(maskedByte2);
    uint8_t masked = (uint8_t)maskedByte2;
    printf("masked %d\n", masked);
    header[0] = masked;
    printf("header[0]: %d\n", header[0]);
    if(masked < 0){
        masked = ~masked;
        printf("masked %d\n", masked);

    }
 
    printf("unsigned short maskedByte2 : %u\tsize: ", maskedByte2);
    cout << sizeof(maskedByte2) << "\n";

    magicNumber = magicNumber >> 8;

    maskedByte1 = (magicNumber & bitMask);
    printf("unsigned short maskedByte1 : %d\tsize: ", maskedByte1);
    cout << sizeof(maskedByte1) << "\n";

   

    


    return 0;
}




//  BEGIN FUNCTIONS
/*
 std::byte x = (std::byte)maskedByte2;
    std::cout << sizeof((char)x) << std::endl;
    std::cout << (char)x << std::endl;
    std::byte y = (std::byte)maskedByte1;    
    std::cout << (int)y << std::endl;

    //std::byte myByte{ 2 };
    //std::cout << std::to_integer<int>(myByte) << std::endl;
    //memcpy(header, &headerAux ,sizeof(unsigned char));
    
*/

//  END FUNCTIONS