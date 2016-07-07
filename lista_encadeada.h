typedef struct nodo nodo;

struct nodo
{
	int frequencia;
	char simbolo;
	char aresta;
	nodo *direita;
	nodo *esquerda;
};

typedef struct lista lista;

struct lista
{
	lista *proximo;
	nodo *nodo;
};

void inserir(lista **lista_enc, char valor);

nodo *extrair_min(lista **lista_enc);

void ordenar(lista **nodo_atual, lista **anterior);
