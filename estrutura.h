typedef struct node{
    int id;
    char* nome;
    char* respostas[5];
    int pontos;
    struct node *prox;
} jogador;

void inicializar (jogador** l);

void inserir(jogador** l, int id, char* nome);

jogador* criarNode(int id, char* nome);

jogador* find(jogador* lista, int id);

jogador* copyNode(jogador* original);

int sorteioLetra ();

int sorteioTemas ();

jogador* sorteioJogador(jogador*lista, int tamanho);

void imprimirJogadores(jogador* no, int i);

void liberarLista(jogador** no);