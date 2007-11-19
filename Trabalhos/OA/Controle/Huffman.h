#ifndef HUFF_H
#define HUFF_H
#include "../Tipos.h"

no_arv *construirLista(char *nomeArq, int *tamanho);
no_arv *ordenarLista(no_arv *pinicio, int tamanho);
no_arv *construirArvore(no_arv *pinicio, int tamanho);
void gerarCodigos(no_arv *arv, int profundidade, char codigo[TAM_MAX]);
no_arv *buscarNoCaractere(no_arv *arv, const char caractere);
no_arv *buscarNoCodigo(no_arv *arv, char codigo[TAM_MAX], int profundidade);

#endif
