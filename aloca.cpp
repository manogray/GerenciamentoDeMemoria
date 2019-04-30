#include "aloca.h"
#include "encadeada.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(){

    Encadeada* listaEncadeada = new Encadeada();

    char letra = 'c';

    Elemento* element = new Elemento(&letra,10);

    listaEncadeada->inserir(element);

    listaEncadeada->inserir(element);

    listaEncadeada->inserir(element);

    return 0;
}