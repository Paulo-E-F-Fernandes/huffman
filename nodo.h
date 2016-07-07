typedef struct nodo nodo;

struct nodo
{
	int frequencia;
	char simbolo;
	nodo *direita;
	nodo *esquerda;
};

/*
void inserir(nodo **lista, char simbolo);

//void ordenar(nodo **nodo_atual, nodo **anterior);

void ordenar(nodo **nodo_atual, nodo **anterior);



//void extrair_min(nodo **raiz, nodo **abc);
*/
