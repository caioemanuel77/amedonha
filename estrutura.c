#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estrutura.h"

void inicializar (jogador** l){
    *l = NULL;
}

void inserir(jogador** l, int id, char* nome){
    jogador* primeiro = *l;
    jogador* novo = criarNode(id, nome);

    *l = novo;
    novo->prox = primeiro;
}

jogador* criarNode(int id, char* nome){
    jogador* novo = (jogador*) malloc(sizeof(jogador));

    if(novo){
        novo->id = id;

        novo->nome = (char*) malloc( (strlen(nome)+1) * sizeof(char) );
        strcpy(novo->nome, nome);

        novo->pontos = 0;

        novo->prox = NULL;
    }

    return novo;
}