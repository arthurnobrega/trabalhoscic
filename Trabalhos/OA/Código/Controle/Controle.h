/** Programa de Compactação e Descompactação utilizando Huffman e Lempel-Ziv.

Autores do programa:
Arthur Thiago Barbosa Nobrega - 06/31205
Davi Fantino da Silva - 06/40832

Versão 1.0
Data: 11/12/2007
Compilador: gcc 4.1.2 20061115 (prerelease) (Debian 4.1.1-21)

Descrição: Este programa tem por objetivo dispor ao usuário compactar e descompactar arquivos utilizando Huffman e Lempel-Ziv. O usuário também tem a opção de simplesmente mostrar a tabela de Huffman do arquivo fornecido ou o dicionário de Lempel-Ziv, além de poder comparar qual o melhor algorítmo para compactar aquele determinado arquivo.
*/

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
int c_compactarHuffman(char *narqEntrada, char *narqSaida, no_arv *arv, int *tamanho);

/** Descomprimi o arquivo compactado tanto com Huffman quanto com Lempel-Ziv.
 * narqEntrada: nome do arquivo texto de entrada.
 * narqSaida: nome do arquivo binário de saída.
*/
void c_descomprimirArquivo(char *narqEntrada, char *narqSaida);


tab *c_criarTabelaLempelZiv(char* narqEntrada);
int c_compactarLempelZiv(tab *pinicio, char* narqSaida);

int *c_gerarRelatorio(char* narqEntrada);
#endif
