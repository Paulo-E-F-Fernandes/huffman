typedef struct nodo nodo;

struct nodo
{
	int frequencia;
	char simbolo;
	nodo *proximo;
	nodo *direita;
	nodo *esquerda;
};

void inserir(nodo **lista, char valor);

//void ordenar(nodo **nodo_atual, nodo **anterior);

void ordenar(nodo **nodo_atual, nodo **anterior);

nodo *extrair_min(nodo **raiz);

//void extrair_min(nodo **raiz, nodo **abc);
