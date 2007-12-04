#ifndef HUFF_H
#define HUFF_H
#include "../Tipos.h"
#include <stdio.h>

/* Funções de construção da árvore de Huffman */

/** Constroi a lista de caracteres com as respectivas frequências. 
 * arq: arquivo texto de entrada, onde está o texto original.
 * tamanho: ponteiro para um inteiro onde será armazenado o número de caracteres no texto.
*/
no_arv *construirLista(FILE *arq, int *tamanho);

/** Constroi a árvore de acordo com o algoritmo de Huffman.
 * pinicio: ponteiro para a raiz da árvore de Huffman.
 * tamanho: número de caracteres no texto.
*/
no_arv *construirArvore(no_arv *pinicio, int tamanho);

/** Função recursiva que gera os códigos para os nós de acordo com a posição dos mesmos na árvore. 
 * arv: nó da árvore onde será armazenado o código.
 * profundidade: profundidade do nó na árvore.
 * codigo: código que será armazenado no nó.
*/
void gerarCodigos(no_arv *arv, int profundidade, char *codigo);

/* Funções de procura na árvore de Huffman. */
no_arv *buscarNoCaractere(no_arv *arv, char caractere);
no_arv *buscarNoCodigo(no_arv *arv, char *codigo, int profundidade);

/* Função de compactação de um arquivo com o algoritmo de Huffman. */
void compactarArquivoHuffman(FILE *arqEntrada, FILE *arqSaida, no_arv *arv, int tamanho);

#endif
