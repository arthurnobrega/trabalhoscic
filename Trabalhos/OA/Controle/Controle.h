#ifndef CONT_H
#define CONT_H
#include "../Tipos.h"

no_arv *gerarArvoreHuffman(char nomeArq[TAM_MAX], int *tamanho);
void gerarArquivoHuffman(char nomeArq[TAM_MAX], no_arv *arv, int *tamanho);

#endif
