#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

int main (int narg, char * argv[]) {
    int N;
    jogador lista_jogadores;
    inicializar (&lista_jogadores);

    printf("*** JOGO AMEDONHA ***\n\n");
    printf("Quantos jogadores? ");
    scanf("%d",&N);

    for (int i=0; i<N; i++) { // Alocação dos jogadores na lista de jogadores
        char * nome[12];
        printf("Qual o nome do jogador %d? (No máximo 12 letras) ",i+1);
        scanf("%s",nome);
        while (strlen(nome) > 12)   // Tratamento de erro: nome acima de 12 caracteres
            printf("Qual o nome do jogador %d? (NO MÁXIMO 12 LETRAS) ",i+1);
        inserir(&lista_jogadores,i,nome);
    }

    char * letras[23] = {"A","B","C","D","E","G","H","I","J","L","M","N","O","P","Q",
    "R","S","T","U","V","X","Z"};

    char* temas[5] = {"Nomes de Pessoas", "Cidades", "Animais", "Comidas", "Profissões"};

    for (int i=0; i<5; i++) {   // Início do jogo
        
        // Sorteio da letra
        int indice = sorteio_letra();

        /* K será utilizado como parâmetro para saber se uma letra já foi sorteada.
        O vetor de letras recebe K exatamente na posição da letra que for sorteada, 
        o que indica que ela não pode mais ser escolhida.*/
         
        while ( strcmp(letras[indice],"K") == 0 ) 
            indice = sorteio_letra();   // Realiza novo sorteio de letra
        printf("A letra desta rodada é %c",letras[indice]);
        letras[indice] = "K";   // Anula a possibilidade da letra escolhida sair de novo.

        // Sorteio do primeiro tema


    }
}