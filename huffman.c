#include <stdio.h> // fprintf, stderr, fgetc
#include <stdlib.h> // exit, EXIT_FAILURE
#include "huffman.h"

void abrir_arquivo(FILE **arquivo, char *arquivo_nome)
{
	// Abre o arquivo de nome igual "arquivo_nome" que foi passado como parâmetro do programa.
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

/*
 * Lê os caracteres do arquivo que foi passado como parâmetro e vai inserindo na lista encadeada ordenado pela
 *  frequência dos caracteres.
 */
void contar_caracteres(FILE *arquivo, lista **lista)
{
	int simbolo;

	// o fgets retorna o ascii do caracteres, por isso faço o cast para char quando vou inserir na lista encadeada
	while ((simbolo = fgetc(arquivo)) != EOF)
	{
		// Insere na lista encadeada "lista" o caracter representado por simbolo de maneira ordenada pela frequência que
		//  o caracter aparece.
		inserir(lista, (char) simbolo);
	}
}

// Gera a árvore de huffman
// PSEUDOCÓDIGO HUFFMAN - Livro  Algoritmos: Teoria e Prática, Thomas Cormen
void gerar_arvore_huffman(lista **lista_enc)
{
	lista *lista_aux;

	// enquanto existir elementos na lista encadeada que foi populada em "conta_caracteres"
	while ((*lista_enc)->proximo != NULL)
	{
		// aloca um novo elemento para a lista encadeada
		lista_aux = (lista *) malloc(sizeof(lista *));
		// aloca um novo nodo na lista criada acima
		lista_aux->nodo = (nodo *) malloc(sizeof(nodo *));
		// busca o elemento de menor frequencia da lista encadeada, e coloca como filho da esquerda do nodo criado acima
		lista_aux->nodo->esquerda = extrair_min(lista_enc);
		lista_aux->nodo->esquerda->aresta = '1';
		// busca o segundo elemento de menor frequencia da lista encadeada, e coloca como filho da direita do nodo criado acima
		lista_aux->nodo->direita = extrair_min(lista_enc);
		lista_aux->nodo->direita->aresta = '0';
		// calcula a frequência do nodo criado acima, sendo que a frequência será a soma das frequeências dos filhos
		lista_aux->nodo->frequencia = 0;
		if (lista_aux->nodo->esquerda != NULL)
		{
			lista_aux->nodo->frequencia = lista_aux->nodo->esquerda->frequencia;
		}
		if (lista_aux->nodo->direita != NULL)
		{
			lista_aux->nodo->frequencia = lista_aux->nodo->frequencia + lista_aux->nodo->direita->frequencia;
		}

		// adiciona o novo elemento como o primeiro elemento da lista encadeada
		lista_aux->proximo = *lista_enc;
		*lista_enc = lista_aux;

		// ordena o novo elemento na lista encadeada, deixando os nodos com menor frequencia antes dos nodos com maior frequencia
		ordenar(&lista_aux, lista_enc);
	}
}

void executar(char *arquivo_nome)
{
	FILE *arquivo;
	lista *lista_enc;

	// Abre o arquivo de nome "arquivo_nome" para leitura e armazena em "*arquivo"
	abrir_arquivo(&arquivo, arquivo_nome);
	// Cria os nodos da lista encadeada, ordenando pela frequência que eles aparecem, com base nos caracteres extraidos de arquivo.
	contar_caracteres(arquivo, &lista_enc);
	// Gera a árvore de huffman
	gerar_arvore_huffman(&lista_enc);


	// Só um teste para imprimir o primeiro nome. Preciso fazer a leitura de todos os nodos da árvore.
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
	fclose(arquivo);
}
