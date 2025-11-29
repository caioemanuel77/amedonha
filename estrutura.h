typedef struct node{
    int id;
    char* nome;
    int pontos;
    struct node *prox;
}jogador;

void inserir(jogador** l, int id, char* nome);

jogador* criarNode(int id, char* nome);

jogador sorteio_jogador(jogador**lista);

void liberarLista(jogador** no);