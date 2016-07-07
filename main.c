#include <stdio.h> // fprintf, stderr
#include <stdlib.h> // exit, EXIT_FAILURE, EXIT_SUCCESS
#include "huffman.h" // executar

int main (int argc, char *argv[])
{
	// argc == 2, além do nome do programa, recebe também o nome do arquivo que será aberto como parâmetro.
	// argv[0] = nome do programa
	// argv[1] = nome do arquivo que será aberto
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

