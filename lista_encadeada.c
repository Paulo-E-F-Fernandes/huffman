#include <stdlib.h> // NULL
#include <stdio.h> // printf
#include "lista_encadeada.h"

void inserir(lista **lista_enc, char simbolo)
{
	lista *temp;
	lista *lista_ant;
	nodo *nodo_aux;
	int adicionado = 0;

	// Caso a lista encadeada esteja vazia ainda, a mesma é iniciada e o primeiro nodo criado é adicionada nela
	if (*lista_enc == NULL)
	{
		nodo_aux = (nodo *) malloc(sizeof(nodo *));
		// Como é o primeiro nodo da lista, a frequência é 1, já que não existe nenhum outro nodo.
		nodo_aux->frequencia = 1;
		nodo_aux->simbolo = simbolo;
		nodo_aux->direita = NULL;
		nodo_aux->esquerda = NULL;

		*lista_enc = (lista *) malloc(sizeof(lista *));
		// "nodo_aux" é o primeiro nodo de "*lista_enc"
		(*lista_enc)->nodo = nodo_aux;
		// como "*lista_enc" tem apenas um nodo, não existe próximo
		(*lista_enc)->proximo = NULL;
	}
	else
	{
		temp = *lista_enc;
		lista_ant = NULL;
		while (temp != NULL && adicionado == 0)
		{
			nodo_aux = temp->nodo;
			// Caso tenha um nodo na lista encadeada com o símbolo atual
			if (nodo_aux->simbolo == simbolo)
			{
				// incrementa a frequência do nodo
				nodo_aux->frequencia = ++nodo_aux->frequencia;
				// Caso o nodo que terá a frequência incrementada sejá o primeiro nodo da lista encadeada,
				//  a "lista_ant" será NULL, então "lista_ant" será o próprio elemento da lista.
				if (lista_ant == NULL)
				{
					lista_ant = *lista_enc;
				}
				// Ordenar os nodos para que os nodos com menor frequência fiquem primeiro,
				//  para facilitar a criação da árvore de huffman
				ordenar(&temp, &lista_ant);

				adicionado = 1;
			}
			// Usando o lista_ant para manter o nodo anterior do temp atual, já que temp será
			//  atualizado na linha abaixo. Isso é necessário preciso disso para a ordenação
			lista_ant = temp;

			temp = temp->proximo;
		}

		// como não existe nenhum nodo com o símbolo atual, "adicionado" será igual a 0,
		//  então o nodo será criado com frequência igual a 1, pois não existe na lista
		//  encadeada ainda, então é adicionado como primeiro nodo da lista encadeada,
		//  assim já fica ordenado.
		if (adicionado == 0)
		{
			nodo_aux = (nodo *) malloc(sizeof(nodo *));
			nodo_aux->frequencia = 1;
			nodo_aux->simbolo = simbolo;
			nodo_aux->direita = NULL;
			nodo_aux->esquerda = NULL;

			temp = (lista *) malloc(sizeof(lista *));
			temp->nodo = nodo_aux;
			temp->proximo = *lista_enc;
			*lista_enc = temp;
		}
	}

	nodo_aux = NULL;
	free(nodo_aux);
	temp = NULL;
	free(temp);
}

// Extrair o nodo de menor frequência da lista_encadeada
nodo *extrair_min(lista **lista_enc)
{
	nodo *temp;

	// Obter o primeiro nodo da lista encadeada
	temp = (*lista_enc)->nodo;
	// O primeiro elemento da lista encadeada é atualizado para o próximo elemento, o segundo elemento no caso
	*lista_enc = (*lista_enc)->proximo;

	return temp;
}

// Ordena o elemento "nodo_atual" na lista encadeada
void ordenar(lista **nodo_atual, lista **anterior)
{
	lista *lista_aux;
	lista *anterior_2;

	if (((*nodo_atual)->proximo != NULL) && ((*nodo_atual)->nodo->frequencia > (*nodo_atual)->proximo->nodo->frequencia))
	{
		lista_aux = (*nodo_atual)->proximo;

		while (lista_aux != NULL && (*nodo_atual)->nodo->frequencia > lista_aux->nodo->frequencia)
		{
			anterior_2 = lista_aux;
			lista_aux = lista_aux->proximo;
		}

		if (lista_aux != (*nodo_atual)->proximo)
		{
			// Para quando o nodo_atual for igual à raiz
			if (*nodo_atual == *anterior)
			{
				*anterior = (*nodo_atual)->proximo;
			}
			else
			{
				(*anterior)->proximo = (*nodo_atual)->proximo;
			}

			(*nodo_atual)->proximo = lista_aux;
			anterior_2->proximo = *nodo_atual;
		}

		lista_aux = NULL;
		anterior_2 = NULL;
		free(lista_aux);
		free(anterior_2);
	}
}

void imprimir_nodos(nodo *raiz_huffman)
{
	lista *raiz_lista;
	lista *temp;
	lista *aux;

	raiz_lista = (lista *) malloc(sizeof(lista *));

	raiz_lista->nodo = raiz_huffman;
	raiz_lista->proximo = NULL;

	aux = temp = raiz_lista;

	while (temp != NULL)
	{
		if (temp->nodo->esquerda != NULL)
		{
			aux->proximo = (lista *) malloc(sizeof(lista *));
			aux = aux->proximo;
			aux->nodo = temp->nodo->esquerda;
		}

		if (temp->nodo->direita != NULL)
		{
			aux->proximo = (lista *) malloc(sizeof(lista *));
			aux = aux->proximo;
			aux->nodo = temp->nodo->direita;
		}

		temp = temp->proximo;
	}

	while (raiz_lista != NULL)
	{
		if (raiz_lista->nodo->simbolo == '\0')
		{
			printf("nodo pai - ");
		}
		printf("símbolo: %c, ", raiz_lista->nodo->simbolo);
		printf("ascii: %d; ", raiz_lista->nodo->simbolo);
		printf("frequência: %d\n", raiz_lista->nodo->frequencia);

		raiz_lista = raiz_lista->proximo;
	}

}
