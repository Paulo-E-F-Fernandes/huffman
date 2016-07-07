#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main (int argc, char *argv[])
{
	if (argc == 2)
	{
		executar(argv[1]);
	}
	else
	{
		fprintf(stderr, "Erro na passagem de parâmetros: Usar teste_huffman <nome_arquivo>\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

