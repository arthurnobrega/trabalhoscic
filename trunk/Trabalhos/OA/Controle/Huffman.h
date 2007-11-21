#ifndef HUFF_H
#define HUFF_H
#include "../Tipos.h"
#include <stdio.h>

/* Funções de construção da árvore de Huffman */
no_arv *construirLista(FILE *arq, int *tamanho);
no_arv *construirArvore(no_arv *pinicio, int tamanho);
void gerarCodigos(no_arv *arv, int profundidade, char *codigo);

/* Funções de procura na árvore de Huffman. */
no_arv *buscarNoCaractere(no_arv *arv, char caractere);
no_arv *buscarNoCodigo(no_arv *arv, char *codigo, int profundidade);

/* Função de compactação de um arquivo com o algoritmo de Huffman. */
void compactarArquivoHuffman(FILE *arqEntrada, FILE *arqSaida, no_arv *arv, int tamanho);

#endif
