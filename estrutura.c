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

jogador* find(jogador* lista, int id){
    jogador* atual = lista;

    while (atual != NULL && atual->id != id){
        atual = atual->prox;
    }

    return atual;
}

jogador* copyNode(jogador* original) {
    if (original == NULL) {
        return NULL;
    }

    jogador* novo = (jogador*) malloc(sizeof(jogador));
    if (novo == NULL) return NULL;

    novo->id = original->id;
    novo->pontos = original->pontos;

    if (original->nome != NULL) {
        novo->nome = (char*) malloc(strlen(original->nome) + 1);
        strcpy(novo->nome, original->nome);
    } else {
        novo->nome = NULL;
    }

    for (int i = 0; i < 5; i++) {
        if (original->respostas[i] != NULL) {
            novo->respostas[i] = (char*) malloc(strlen(original->respostas[i]) + 1);
            strcpy(novo->respostas[i], original->respostas[i]);
        } else {
            novo->respostas[i] = NULL;
        }
    }

    novo->prox = NULL;

    return novo;
}

jogador* sorteioJogador(jogador*lista, int tamanho){
    int vetor[tamanho], i;
    jogador* sorteados;
    jogador* adicionar;
    jogador *anterior = NULL;
    inicializar(&sorteados);

    for(i = 0; i < tamanho; i++)
        vetor[i] = 1;
    
    for(i = 0; i < tamanho; i++){
        int valor = rand() % tamanho;
        while(vetor[valor] != 1){
            valor = rand() % tamanho;
        }
        vetor[valor] = 0;

        adicionar = copyNode(find(lista, valor));

        if(anterior == NULL)
            sorteados = adicionar;
        else
            anterior->prox = adicionar;
        anterior = adicionar;
    }
    
    return sorteados;
}

int sorteioLetra(){
    int valor = rand() % 23;
    return valor;
}

int sorteioTemas(){
    int valor = rand() % 5;
    return valor;
}

void liberarLista(jogador** no) {
    jogador* atual = *no;
    jogador* proximo;
    
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual->nome);
        free(atual); 
        atual = proximo;
    }
    
    *no = NULL; 
}

void imprimirJogadores(jogador* no, int i){
    if (no == NULL)
        return;
    printf("%i. %s", no->nome);
    imprimirJogadores(no->prox, i+1);
}