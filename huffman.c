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

void contar_caracteres(FILE *arquivo, nodo **lista)
{
	int simbolo_atual;

	while ((simbolo_atual = fgetc(arquivo)) != EOF)
	{
		inserir(lista, (char) simbolo_atual);
	}
}

void gerar_arvore_huffman(nodo **raiz)
{
	nodo *z;

	while ((*raiz)->proximo != NULL)
	{
		z = (nodo *) malloc(sizeof(nodo *));

		z->esquerda = extrair_min(raiz);
		z->direita = extrair_min(raiz);
		//extrair_min(raiz, &z->esquerda);
		//extrair_min(raiz, &z->direita);
		z->frequencia = z->esquerda->frequencia + z->direita->frequencia;
		z->proximo = *raiz;
		*raiz = z;

		//ordenar(&z, raiz);
	}
}

void executar(char *arquivo_nome)
{
	FILE *arquivo;
	nodo *raiz;

	abrir_arquivo(&arquivo, arquivo_nome);
	contar_caracteres(arquivo, &raiz);
	gerar_arvore_huffman(&raiz);

	do
	{
		printf("\n   ***   \n");
		printf("raiz.frequencia: %d - ", raiz->frequencia);
		printf("raiz.simbolo: %c\n", raiz->simbolo);
		printf("raiz.proximo: %p\n", raiz->proximo);
		printf("raiz->esquerda: %p\n", raiz->esquerda);
		printf("raiz->esquerda->esquerda: %p\n", raiz->esquerda->esquerda);
		printf("raiz->esquerda->direita: %p\n", raiz->esquerda->direita);

		printf("raiz->direita: %p\n", raiz->direita);
		printf("raiz->direita->esquerda: %p\n", raiz->direita->esquerda);
		printf("raiz->direita->direita: %p\n", raiz->direita->direita);

		printf("raiz->direita->esquerda->frequencia: %d\n", raiz->direita->esquerda->frequencia);
		printf("raiz->direita->direita->frequencia: %d\n", raiz->direita->direita->frequencia);

		printf("RAIZ_1: %p\n", raiz);
		raiz = raiz->proximo;
		printf("RAIZ_2: %p\n", raiz);
	} while (raiz != NULL);

	free(raiz);
	// O "fclose(arquivo)" começou a dar "Segmentation fault (core dumped)", por isso está comentado.
	//fclose(arquivo);
}
