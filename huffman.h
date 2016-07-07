#include "nodo.h"

void abrir_arquivo(FILE **arquivo, char *arquivo_nome);

void contar_caracteres(FILE *arquivo, nodo **lista);

//void conta_caracteres(FILE *arquivo, nodo *lista);

void executar(char *arquivo_nome);

void gerar_arvore_huffman(nodo **raiz);
