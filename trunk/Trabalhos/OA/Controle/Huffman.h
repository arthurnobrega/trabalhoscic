/** Programa de Compactação e Descompactação utilizando Huffman e Lempel-Ziv.

Autores do programa:
Arthur Thiago Barbosa Nobrega - 06/31205
Davi Fantino da Silva - 06/40832

Versão 1.0
Data: 11/12/2007
Compilador: gcc 4.1.2 20061115 (prerelease) (Debian 4.1.1-21)

Descrição: Este programa tem por objetivo dispor ao usuário compactar e descompactar arquivos utilizando Huffman e Lempel-Ziv. O usuário também tem a opção de simplesmente mostrar a tabela de Huffman do arquivo fornecido ou o dicionário de Lempel-Ziv, além de poder comparar qual o melhor algorítmo para compactar aquele determinado arquivo.
*/

#ifndef HUFF_H
#define HUFF_H
#include "../Tipos.h"
#include <stdio.h>

/** Constroi a lista de caracteres com as respectivas frequências. 
 * arq: arquivo texto de entrada, onde está o texto original.
 * tamanho: ponteiro para um inteiro onde será armazenado o número de caracteres no texto.
 */


/** Constroi a lista de caracteres com as respectivas frequências.
 * Data: 10/12/2007
 * Versão: 1.0
 * Autores:
     Arthur Thiago Barbosa Nobrega - 06/31205
     Davi Fantino da Silva - 06/40832
 * @param arq Arquivo de entrada.
 * @param tamanho Armazena o número de caracteres no texto.
 * @return O início da lista.
 */
no_arv *construirLista(FILE *arq, int *tamanho);


/** Constroi a árvore de acordo com o algoritmo de Huffman.
 * Data: 10/12/2007
 * Versão: 1.0
 * Autores:
     Arthur Thiago Barbosa Nobrega - 06/31205
     Davi Fantino da Silva - 06/40832
 * @param pinicio Ponteiro de início da lista.
 * @param tamanho O número de caracteres no texto.
 * @return O início da árvore.
 */
no_arv *construirArvore(no_arv *pinicio, int tamanho);

/** Função recursiva que gera os códigos para os nós de acordo com a posição dos mesmos na árvore.
 * Data: 10/12/2007
 * Versão: 1.0
 * Autores:
     Arthur Thiago Barbosa Nobrega - 06/31205
     Davi Fantino da Silva - 06/40832
 * @param arv Nó da árvore onde será armazenado o código.
 * @param profundidade Profundidade do nó na árvore.
 * @param codigo Código que será armazenado no nó.
 */
void gerarCodigos(no_arv *arv, int profundidade, char *codigo);


/** Buscar nó na árvore usando caractere como parâmetro.
 * Data: 10/12/2007
 * Versão: 1.0
 * Autores:
     Arthur Thiago Barbosa Nobrega - 06/31205
     Davi Fantino da Silva - 06/40832
 * @param arv Nó da árvore onde será armazenado o código.
 * @param caractere Caractere procurado.
 * @return Ponteiro para o nó onde se encontra o caractere.
 */
/* Funções de procura na árvore de Huffman. */
no_arv *buscarNoCaractere(no_arv *arv, char caractere);

/** Buscar nó na árvore usando codigo como parâmetro.
 * Data: 10/12/2007
 * Versão: 1.0
 * Autores:
     Arthur Thiago Barbosa Nobrega - 06/31205
     Davi Fantino da Silva - 06/40832
 * @param arv Nó da árvore onde será armazenado o código.
 * @param codigo Código do caractere.
 * @param profundidade Profundidade do nó na árvore.
 * @return Ponteiro para o nó do código.
 */
no_arv *buscarNoCodigo(no_arv *arv, char *codigo, int profundidade);

/** Compactar o arquivo de entrada, gravando-o na saída, usando HUFFMAN.
 * Data: 10/12/2007
 * Versão: 1.0
 * Autores:
     Arthur Thiago Barbosa Nobrega - 06/31205
     Davi Fantino da Silva - 06/40832
 * @param arqEntrada Arquivo de entrada.
 * @param arqSaida Arquivo de Saída.
 * @param arv Nó de início da árvore.
 * @param tamanho Número de caracteres deferentes existentes no arquivo.
 * @return Numero de bits do arquivo compactado.
 */
/* Função de compactação de um arquivo com o algoritmo de Huffman. */
int compactarArquivoHuffman(FILE *arqEntrada, FILE *arqSaida, no_arv *arv, int tamanho);

#endif
