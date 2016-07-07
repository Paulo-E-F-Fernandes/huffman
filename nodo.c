#include <stdlib.h> // NULL
#include <stdio.h>
#include "nodo.h"

/*
void inserir(nodo **lista, char simbolo)
{
	nodo *temp;
	nodo *aux;
	int adicionado = 0;

	if (*lista == NULL)
	{
		*lista = (nodo *) malloc(sizeof(nodo *));
		(*lista)->frequencia = 1;
		(*lista)->simbolo = simbolo;
		(*lista)->proximo = NULL;
		(*lista)->direita = NULL;
		/*
		 * Se colocar somente "aux->esquerda = NULL;" durante a execução deu o erro:
		 *  "main: malloc.c:2372: sysmalloc: Assertion `(old_top == (((mbinptr) (((char *) &((av)->bins[((1) - 1) * 2])) -
		 *    __builtin_offsetof (struct malloc_chunk, fd)))) && old_size == 0) || ((unsigned long) (old_size) >= (unsigned
		 *    long)((((__builtin_offsetof (struct malloc_chunk, fd_nextsize))+((2 *(sizeof(size_t))) - 1)) & ~((2 *(sizeof(
		 *    size_t))) - 1))) && ((old_top)->size & 0x1) && ((unsigned long) old_end & pagemask) == 0)' failed.
		 *   Aborted (core dumped)"
		 *
		 * Colocando o "aux->esquerda = (nodo *) malloc(sizeof(nodo *));" antes do "aux->esquerda = NULL;" não dá este problema.
		 *
		 * NÃO SEI PORQUÊ. Pelo que li é um problema do gcc do ubuntu.
		 * / *************
		(*lista)->esquerda = (nodo *) malloc(sizeof(nodo *));
		(*lista)->esquerda = NULL;
	}
	else
	{
		temp = *lista;
		aux = NULL; // Usando o aux para manter o nodo anterior do temp atual, começo com NULL pois não existe nada antes do *lista

		while (temp != NULL && adicionado == 0)
		{
			if (temp->simbolo == simbolo)
			{
				temp->frequencia = ++temp->frequencia;
				if (aux == NULL)
				{
					aux = *lista;
				}
				ordenar(&temp, &aux); // Ordenar os nodos para que os com menor frequência fiquem primeiro, para
									  //  facilitar a criação da árvore de huffman
				adicionado = 1;
			}
			aux = temp; // Usando o aux para manter o nodo anterior do temp atual, já que tempo será o próximo dele na linha abaixo
						// Preciso disso para a ordenação
			temp = temp->proximo;
		}

		if (adicionado == 0) {
			aux = (nodo *) malloc(sizeof(nodo *));
			aux->frequencia = 1;
			aux->simbolo = simbolo;
			aux->proximo = *lista;
			aux->direita = NULL;
			/*
			 * Se colocar somente "aux->esquerda = NULL;" durante a execução deu o erro:
			 *  "main: malloc.c:2372: sysmalloc: Assertion `(old_top == (((mbinptr) (((char *) &((av)->bins[((1) - 1) * 2])) -
			 *    __builtin_offsetof (struct malloc_chunk, fd)))) && old_size == 0) || ((unsigned long) (old_size) >= (unsigned
			 *    long)((((__builtin_offsetof (struct malloc_chunk, fd_nextsize))+((2 *(sizeof(size_t))) - 1)) & ~((2 *(sizeof(
			 *    size_t))) - 1))) && ((old_top)->size & 0x1) && ((unsigned long) old_end & pagemask) == 0)' failed.
			 *   Aborted (core dumped)"
			 *
			 * Colocando o "aux->esquerda = (nodo *) malloc(sizeof(nodo *));" antes do "aux->esquerda = NULL;" não dá este problema.
			 *
			 * NÃO SEI PORQUÊ. Pelo que li é um problema do gcc do ubuntu.
			 * / *************
			aux->esquerda = (nodo *) malloc(sizeof(nodo *));
			aux->esquerda = NULL;
/*
			printf("\nfrequencia: %d\n", aux->frequencia);
			printf("simbolo: %c\n", aux->simbolo);
			printf("proximo: %p\n", aux->proximo);
			printf("direita: %p\n", aux->direita);
			printf("esquerda: %p\n\n", aux->esquerda);
* / *************

			*lista = aux;
		}
	}

	aux = NULL;
	temp = NULL;
	free(aux);
	free(temp);
}

/*
void ordenar(nodo **nodo_atual, nodo **anterior)
{
	nodo *aux;
	nodo *anterior2;
	int i = 0;

	aux = (*nodo_atual)->proximo;

	printf("freq: %d\n", (*nodo_atual)->frequencia);

	while (aux != NULL && (*nodo_atual)->frequencia > aux->frequencia)
	{
		anterior2 = aux;
		aux = aux->proximo;
	}

	if (aux != (*nodo_atual)->proximo)
	{
		(*anterior)->proximo = (*nodo_atual)->proximo;
		(*nodo_atual)->proximo = aux;
		anterior2->proximo = *nodo_atual;
	}

	aux = NULL;
	anterior2 = NULL;
	free(aux);
	free(anterior2);
}
* / *****************

void ordenar(nodo **nodo_atual, nodo **anterior)
{
	nodo *aux;
	nodo *anterior2;
	int i = 0;

	// Se o "nodo_atual" possui próximo e a frequência deste for menor que a atual.
	//
	// Caso o "nodo_atual" não possui próximo, significa que ele é o último da lista,
	//  então ele é o com maior frequência e já está ordenado.
	//
	// Caso a frequência do "nodo_atual" for igual a frequência de seu próximo,
	//  ele já está ordenado.
	if (((*nodo_atual)->proximo != NULL) && ((*nodo_atual)->frequencia > (*nodo_atual)->proximo->frequencia))
	{
		aux = (*nodo_atual)->proximo;
		printf("freq: %d\n", (*nodo_atual)->frequencia);

		while (aux != NULL && (*nodo_atual)->frequencia > aux->frequencia)
		{
			anterior2 = aux;
			aux = aux->proximo;
		}

		if (aux != (*nodo_atual)->proximo)
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

			(*nodo_atual)->proximo = aux;
			anterior2->proximo = *nodo_atual;
		}
/*
		aux = NULL;
		anterior2 = NULL;
		free(aux);
		free(anterior2);
* / *************	}
}


nodo *extrair_min(nodo **raiz)
{
	nodo *temp;

	temp = *raiz;
	*raiz = (*raiz)->proximo;

	temp->proximo = NULL;

	return temp;
}
*/
/*
void extrair_min(nodo **raiz, nodo **abc)
{
	//nodo *temp;

	*abc = *raiz;
	*raiz = (*raiz)->proximo;

	(*abc)->proximo = NULL;

	//temp = NULL;
	//free(temp);
}
*/
