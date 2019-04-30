#include "aloca.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(){

    meualoc *aloc1 = new meualoc(200,10);

    aloc1->imprimePolitica();

    aloc1->~meualoc();

    aloc1->imprimePolitica();

    return 0;
}