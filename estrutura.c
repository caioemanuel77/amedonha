#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estrutura.h"

void inicializar (jogador** l){
    *l = NULL;
}

// Cria um novo jogador e insere no início da lista
void inserir(jogador** l, int id, char* nome){
    jogador* primeiro = *l;
    jogador* novo = criarNode(id, nome);
    *l = novo;
    novo->prox = primeiro;
}

// Cria um novo jogador com os dados fornecidos
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

// Procura um jogador na lista pelo ID, retornando o ponteiro para o jogador encontrado
jogador* find(jogador* lista, int id){
    jogador* atual = lista;
    // Percorre a lista até encontrar o jogador com o ID correspondente
    while (atual != NULL && atual->id != id){
        atual = atual->prox;
    }

    return atual;
}

// Cria uma cópia de um jogador, alocando nova memória
jogador* copyNode(jogador* original) {
    if (original == NULL) {
        return NULL;
    }

    jogador* novo = (jogador*) malloc(sizeof(jogador));
    if (novo == NULL) return NULL;

    novo->id = original->id;
    novo->pontos = original->pontos;

    // Faz um novo alocamento para o nome
    if (original->nome != NULL) {
        novo->nome = (char*) malloc(strlen(original->nome) + 1);
        strcpy(novo->nome, original->nome);
    } else {
        novo->nome = NULL;
    }

    // Faz um novo alocamento para as respostas
    for (int i = 0; i < 5; i++) {
        if (original->respostas[i] != NULL) {
            strcpy(novo->respostas[i], original->respostas[i]);
        } else
            novo->respostas[i][0] = '\0';
    }

    novo->prox = NULL;

    return novo;
}

// Realiza um sorteio dos jogadores, retornando uma nova lista com a ordem sorteada
jogador* sorteioJogador(jogador* lista, int tamanho){
    int indices[tamanho];
    int i, j, temp;
    
    jogador* sorteados;
    jogador* adicionar;
    jogador* anterior = NULL;
    
    inicializar(&sorteados);

    // Preenche o vetor com os IDS sequenciais (0, 1, 2, 3, ...)
    for(i = 0; i < tamanho; i++) {
        indices[i] = i;
    }

    // Embaralha o vetor de índices, para cada posição, troca com uma aleatória anterior
    for (i = tamanho - 1; i > 0; i--) {
        j = rand() % (i + 1); // Escolhe um índice aleatório entre 0 e i
        
        temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Agora percorre o vetor embaralhado, pegando o ID que está na posição i do vetor embaralhado
    for(i = 0; i < tamanho; i++){
        int valorSorteado = indices[i];

        // Procura o nó do jogador pelo ID e faz uma cópia desse nó para não alterar a lista principal.
        adicionar = copyNode(find(lista, valorSorteado));

        if(anterior == NULL) // Caso seja o primeiro jogador sorteado
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

// Imprime os jogadores na ordem que foram sorteados.
void imprimirJogadores(jogador* no, int a){
    if (no == NULL)
        return;
    printf("  %d. %s\n", a, no->nome);
    imprimirJogadores(no->prox, a+1);
}