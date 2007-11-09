#ifndef HUFF_H
#define HUFF_H
#include "../Tipos.h"

no_arv *construirLista(char *nomeArq, int *tamanho);
no_arv *ordenarLista(no_arv *pinicio, int tamanho);
no_arv *construirArvore(no_arv *pinicio, int tamanho);
void gerarCodigos(no_arv *arv, int profundidade, int codigo);

#endif
