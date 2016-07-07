#include <stdio.h>
#include <stdlib.h> //EXIT_FAILURE
#include "huffman.h"

void abrir_arquivo(FILE **arquivo, char *arquivo_nome)
{
	// Abre o arquivo de nome igual "arquivo_nome" que foi passado por parâmetro
	*arquivo = fopen(arquivo_nome, "r");

	// Caso dê algum erro na abertura do arquivo o ponteiro "*arquivo" será nulo,
	//  com isso o programa finaliza e sinaliza o erro.
	//
	// Para testar esse erro é só passar o nome de um arquivo que não exista como parâmetro na execução do programa.
	if (*arquivo == NULL)
	{
		fprintf(stderr, "O arquivo %s não pode ser aberto!\n", arquivo_nome);
		exit(EXIT_FAILURE);
	}
}

void contar_caracteres(FILE *arquivo, lista **lista)
{
	int simbolo;

	while ((simbolo = fgetc(arquivo)) != EOF)
	{
		inserir(lista, (char) simbolo);
	}
}

void gerar_arvore_huffman(lista **lista_enc)
{
	lista *lista_aux;

	while ((*lista_enc)->proximo != NULL)
	{
		lista_aux = (lista *) malloc(sizeof(lista *));
		lista_aux->nodo = (nodo *) malloc(sizeof(nodo *));
		lista_aux->nodo->esquerda = extrair_min(lista_enc);
		lista_aux->nodo->direita = extrair_min(lista_enc);

		lista_aux->nodo->frequencia = 0;
		if (lista_aux->nodo->esquerda != NULL)
		{
			lista_aux->nodo->frequencia = lista_aux->nodo->esquerda->frequencia;
		}
		if (lista_aux->nodo->direita != NULL)
		{
			lista_aux->nodo->frequencia = lista_aux->nodo->frequencia + lista_aux->nodo->direita->frequencia;
		}

		lista_aux->proximo = *lista_enc;
		*lista_enc = lista_aux;

		ordenar(&lista_aux, lista_enc);
	}
}

void executar(char *arquivo_nome)
{
	FILE *arquivo;
	lista *lista_enc;

	abrir_arquivo(&arquivo, arquivo_nome);
	contar_caracteres(arquivo, &lista_enc);
	gerar_arvore_huffman(&lista_enc);

	do
	{
		printf("\n   ***   \n");
		printf("frequencia: %d - ", lista_enc->nodo->frequencia);
		printf("simbolo: %c\n", lista_enc->nodo->simbolo);
		printf("direita: %p\n", lista_enc->nodo->direita);
		printf("esquerda: %p\n", lista_enc->nodo->esquerda);

		lista_enc = lista_enc->proximo;
	} while (lista_enc != NULL);

	free(lista_enc);
	// O "fclose(arquivo)" começou a dar "Segmentation fault (core dumped)", por isso está comentado.
	fclose(arquivo);
}
