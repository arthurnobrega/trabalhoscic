#ifndef CONT_H
#define CONT_H
#include "../Tipos.h"

/** Gera a árvore de Huffman. 
 * nomeArq: nome do arquivo onde se encontra o texto que se quer gerar a árvore de Huffman.
 * tamanho: ponteiro para um inteiro onde será armazenado o número de caracteres no texto.
*/
no_arv *c_gerarArvoreHuffman(char *nomeArq, int *tamanho);

/** Compacta o arquivo com o algoritmo de Huffman.
 * narqEntrada: nome do arquivo texto de entrada.
 * narqSaida: nome do arquivo binário de saída.
 * arv: ponteiro para a raiz da árvore de Huffman.
 * tamanho: ponteiro para um inteiro onde será armazenado o número de caracteres no texto.
*/
void c_compactarHuffman(char *narqEntrada, char *narqSaida, no_arv *arv, int *tamanho);

/** Descomprimi o arquivo compactado tanto com Huffman quanto com Lempel-Ziv.
 * narqEntrada: nome do arquivo texto de entrada.
 * narqSaida: nome do arquivo binário de saída.
*/
void c_descomprimirArquivo(char *narqEntrada, char *narqSaida);


tab *c_criarTabelaLempelZiv(char* narqEntrada);
void c_compactarLempelZiv(tab *pinicio, char* narqSaida);
#endif
