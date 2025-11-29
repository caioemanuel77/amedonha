#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

int main (int narg, char * argv[]) {
    int N;
    jogador * lista_jogadores;
    inicializar (&lista_jogadores);

    printf("*** JOGO AMEDONHA ***\n\n");
    printf("Quantos jogadores? ");
    scanf("%d",&N);

    for (int i=0; i<N; i++) { // Alocação dos jogadores na lista de jogadores
        char nome[13];
        printf("Qual o nome do jogador %d? (No máximo 12 letras) ",i+1);
        scanf("%s",nome);
        while (strlen(nome) > 12){  // Tratamento de erro: nome acima de 12 caracteres
            printf("Qual o nome do jogador %d? (NO MÁXIMO 12 LETRAS) ",i+1);
            scanf("%s",nome);
        }
        inserir(&lista_jogadores,i,nome);
    }

    char * letras[23] = {"A","B","C","D","E","G","H","I","J","L","M","N","O","P","Q",
    "R","S","T","U","V","X","Z"};

    char* temas[5] = {"Nomes de Pessoas", "Cidades", "Animais", "Comidas", "Profissões"};

    for (int i=0; i<5; i++) {   // Início do jogo

        system("clear");
        
        printf("*** JOGO AMEDONHA ***\n\n");

        // Sorteio da letra

            int indice1 = sorteioLetra();

            /* K será utilizado como parâmetro para saber se uma letra já foi sorteada.
            O vetor de letras recebe K exatamente na posição da letra que for sorteada, 
            o que indica que ela não pode mais ser escolhida.*/
            
            while ( strcmp(letras[indice1],"K") == 0 ) 
                indice1 = sorteioLetra();   // Realiza novo sorteio de letra
            printf("-> A letra desta rodada é %s\n",letras[indice1]);
            letras[indice1] = "K";   // Anula a possibilidade da letra escolhida sair de novo.

        // Sorteio do tema

            int indice2 = sorteioTemas();

            /* A estratégia agora é usar o X para indicar que o tema já saiu */

            while ( strcmp(temas[indice2],"X") == 0 ) 
                indice2 = sorteioTemas();  // Realiza novo sorteio de tema
            printf("-> A categoria desta rodada é %s\n",temas[indice2]);
            temas[indice2] = "X";   // Anula a possibilidade do tema escolhido sair de novo.

        //  Sorteio dos jogadores

            /* Cria uma lista que recebe a lista de ordem de sorteio dos jogadores */
            jogador *ordem = sorteioJogador(lista_jogadores,N);

            /* Imprime a ordem de sorteio dos jogadores */
            printf("\nOrdem de Jogadores:\n");
            imprimirJogadores (ordem,1);

        // Iniciando o jogo

            char c;
            getchar();
            printf("Tecle [Enter] para iniciar a rodada: ");
            scanf(" %c",&c); // Limpa o buffer do teclado
            while (c != '\n') {
                printf("Tecle [Enter] para iniciar a rodada: ");
                scanf("%c",&c);
            }
    }
}