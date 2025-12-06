#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "estrutura.h"
#include <ctype.h>
#include <math.h>

int main (int narg, char * argv[]) {
    int N;
    jogador * lista_jogadores;
    inicializar (&lista_jogadores);
    struct timeval inicio, fim;
    double tempo_seg = 1.0;
    char* letra[5];
    char* tema[5];

    printf("============= JOGO AMEDONHA =============\n\n");
    printf("Quantos jogadores? ");
    scanf("%d",&N);
    while(N > 10 || N < 2){  // Tratamento de erro: número de jogadores inválido
        printf("Quantos jogadores? (Mínimo 2, máximo 10): ");
        scanf("%d",&N);
    }

    for (int i=0; i<N; i++) { // Alocação dos jogadores na lista de jogadores
        char nome[13];
        printf("Qual o nome do jogador %d? (No máximo 12 letras) ",i+1);
        scanf("%s",nome);
        while (strlen(nome) > 12){  // Tratamento de erro: nome acima de 12 caracteres
            printf("Qual o nome do jogador %d? (NO MÁXIMO 12 LETRAS) ",i+1);
            scanf("%s",nome);
        }
        nome[0] = toupper(nome[0]);
        inserir(&lista_jogadores,i,nome);
    }

    limparBuffer();

    char * letras[23] = {"A","B","C","D","E","G","H","I","J","L","M","N","O","P","Q",
    "R","S","T","U","V","X","Z"};

    char* temas[5] = {"Nomes de Pessoas", "Cidades", "Animais", "Comidas", "Profissões"};

    for (int i=0; i<5; i++) {   // Início do jogo

        system("clear");
        
        printf("============= JOGO AMEDONHA =============\n\n");

        // Sorteio da letra

            int indice1 = sorteioLetra();

            /* K será utilizado como parâmetro para saber se uma letra já foi sorteada.
            O vetor de letras recebe K exatamente na posição da letra que for sorteada, 
            o que indica que ela não pode mais ser escolhida.*/
            
            while ( strcmp(letras[indice1],"K") == 0 ) 
                indice1 = sorteioLetra();   // Realiza novo sorteio de letra
            printf("-> A letra desta rodada é %s\n",letras[indice1]);
            letra[i] = letras[indice1];
            letras[indice1] = "K";   // Anula a possibilidade da letra escolhida sair de novo.

        // Sorteio do tema

            int indice2 = sorteioTemas();

            /* A estratégia agora é usar o X para indicar que o tema já saiu */

            while ( strcmp(temas[indice2],"X") == 0 ) 
                indice2 = sorteioTemas();  // Realiza novo sorteio de tema
            printf("-> A categoria desta rodada é %s\n",temas[indice2]);
            tema[i] = temas[indice2];
            temas[indice2] = "X";   // Anula a possibilidade do tema escolhido sair de novo.

        //  Sorteio dos jogadores

            /* Cria uma lista que recebe a lista de ordem de sorteio dos jogadores */
            jogador *ordem = sorteioJogador(lista_jogadores,N);

            /* Imprime a ordem de sorteio dos jogadores */
            printf("\nOrdem de Jogadores:\n");
            imprimirJogadores (ordem,1);

        // Iniciando o jogo (coletando a tecla Enter)

            printf("\nTecle [Enter] para iniciar a rodada: ");
            fflush(stdout);

            getchar();

        // Coletando as respostas dos jogadores em cada rodada

            jogador* atual = ordem; // Ponteiro para a cabeça da lista que mostra a ordem dos jogadores
            int cont = 0;

            while (atual != NULL && cont < N) {

                system("clear");
                printf("============= JOGO AMEDONHA =============\n\n");
                printf("-> A letra desta rodada é %s\n", letra[i]);
                printf("-> A categoria desta rodada é %s\n", tema[i]);
                printf("_________________________________________\n");
                char resposta[30];
                int tempo_jogador = (8 + 2*N - 2*cont);
                
                //  Coletando o tempo que a resposta custou

                gettimeofday(&inicio,NULL);

                    printf("\n%s, você deve entrar %s com a letra %s em %d segundos: ",atual->nome,tema[i],letra[i],tempo_jogador);
                    scanf(" %[^\n]",resposta);
                    
                    //  Tratamento de respostas: resposta maior que 30 caracteres ou letra inicial diferente da sorteada
                    while (strlen(resposta) > 29 || toupper(resposta[0]) != letra[i][0]) {
                        printf("Resposta inválida! Tente novamente\n");
                        printf("\nJogador %s, qual a sua resposta? ",atual->nome);
                        scanf(" %[^\n]",resposta);
                    }

                gettimeofday (&fim,NULL);

                limparBuffer();

                tempo_seg = (double) (fim.tv_usec - inicio.tv_usec) / 1000000 + (double) (fim.tv_sec - inicio.tv_sec);

                jogador* jogadorOriginal = find(lista_jogadores, atual->id);
                
                jogadorOriginal->tempo[i] = tempo_seg;

                if (tempo_seg <= tempo_jogador) {
                    if ( strcmp(tema[i],"Nomes de Pessoas") == 0 ) { // Tratamento do caso "Nome de Pessoa" e nome simples
                        char resp[30];

                        int j = 0;
                        while (resposta[j] != ' ' && resposta[j] != '\0' && j < 29) { // Caso seja nome de pessoa, só pode ler até o primeiro espaço em branco
                            resp[j] = resposta[j];
                            j++;
                        }
                        resp[j] = '\0';
                        resp[0] = toupper(resp[0]);
                        strcpy(jogadorOriginal->respostas[i], resp);
                    } 
                    else {
                        resposta[0] = toupper(resposta[0]);
                        strcpy(jogadorOriginal->respostas[i], resposta);
                    }
                } else
                    strcpy(jogadorOriginal->respostas[i], "Resposta Fora do Tempo"); // Caso o tempo tenha estourado, a resposta será "erro"

                atual = atual->prox; 
                cont++;
            }   // Fim de rodada  

            int* repete = respostasIguais(lista_jogadores, N, i);

            int idx = 0;
            for (atual = lista_jogadores; atual != NULL; atual = atual->prox) {


                if (strcmp(atual->respostas[i], "Resposta Fora do Tempo") == 0) {
                    atual->pontos[i] = 0;
                } else {
                    atual->pontos[i] = ceil((double) strlen(atual->respostas[i]) / repete[idx]);
                }
                idx++;
            }
            free(repete);
            liberarLista(&ordem); // Libera a lista de ordem de jogadores sorteados
            system("clear");

            if(i < 4){
                printf("================= JOGO AMEDONHA ==================\n\n");
                // Exibe as respostas desta rodada
                imprimirRespostasRodada(lista_jogadores, i);

                // Exibe pontuação parcial/final
                imprimirPontuacao(lista_jogadores, tema, i);

                // Pausar
                printf("Tecle [Enter] para continuar: ");
                fflush(stdout);
                getchar();
            }else{
                printf("==================== JOGO AMEDONHA ====================\n\n");
                printf("FIM DE JOGO! Tecle [Enter] para ver o resultado final: ");
                fflush(stdout);
                getchar();
                system("clear");
                printf("================================================================ JOGO AMEDONHA ==================================================================\n\n");
                printf("%*sO VENCEDOR É: %s\n\n", 62, "", vencedor(lista_jogadores, N));
                imprimirPontuacao(lista_jogadores, tema, i);
                
            }
    }

    liberarLista(&lista_jogadores);
}