//#include "nodo.h"
#include "lista_encadeada.h"

void abrir_arquivo(FILE **arquivo, char *arquivo_nome);

void contar_caracteres(FILE *arquivo, lista **lista);

//void conta_caracteres(FILE *arquivo, nodo *lista);

void executar(char *arquivo_nome);

void gerar_arvore_huffman(lista **lista_enc);
