#include <stdlib.h> // NULL
#include "lista_encadeada.h"

void inserir(lista **lista_enc, char simbolo)
{
	lista *temp;
	lista *lista_ant;
	nodo *nodo_aux;
	int adicionado = 0;

	if (*lista_enc == NULL)
	{
		nodo_aux = (nodo *) malloc(sizeof(nodo *));
		nodo_aux->frequencia = 1;
		nodo_aux->simbolo = simbolo;
		nodo_aux->direita = NULL;
		nodo_aux->esquerda = NULL;

		*lista_enc = (lista *) malloc(sizeof(lista *));
		(*lista_enc)->nodo = nodo_aux;
		(*lista_enc)->proximo = NULL;
	}
	else
	{
		temp = *lista_enc;
		lista_ant = NULL;
		while (temp != NULL && adicionado == 0)
		{
			nodo_aux = temp->nodo;
			if (nodo_aux->simbolo == simbolo)
			{
				nodo_aux->frequencia = ++nodo_aux->frequencia;
				if (lista_ant == NULL)
				{
					lista_ant = *lista_enc;
				}
				ordenar(&temp, &lista_ant); // Ordenar os nodos para que os com menor frequência fiquem primeiro, para
									        //  facilitar a criação da árvore de huffman
				adicionado = 1;
			}
			lista_ant = temp; // Usando o aux para manter o nodo anterior do temp atual, já que tempo será o próximo dele na linha abaixo
						      // Preciso disso para a ordenação
			temp = temp->proximo;
		}

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

nodo *extrair_min(lista **lista_enc)
{
	nodo *temp;

	temp = (*lista_enc)->nodo;
	*lista_enc = (*lista_enc)->proximo;

	return temp;
}

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
