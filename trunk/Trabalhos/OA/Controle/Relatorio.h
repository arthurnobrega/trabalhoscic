/* Programa de Compactação e Descompactação utilizando Huffman e Lempel-Ziv.

Autores do programa:
Arthur Thiago Barbosa Nobrega - 06/31205
Davi Fantino da Silva - 06/40832

Versão 1.0
Data: 11/12/2007
Compilador: gcc 4.1.2 20061115 (prerelease) (Debian 4.1.1-21)

Descrição: Este programa tem por objetivo dispor ao usuário compactar e descompactar arquivos utilizando Huffman e Lempel-Ziv. O usuário também tem a opção de simplesmente mostrar a tabela de Huffman do arquivo fornecido ou o dicionário de Lempel-Ziv, além de poder comparar qual o melhor algorítmo para compactar aquele determinado arquivo.
*/

#ifndef REL_H
#define REL_H
#include "../Tipos.h"
#include <stdio.h>

/** Conta o número de Bits do Arquivo.
 * Data: 10/12/2007
 * Versão: 2.0
 * Autores:
     Arthur Thiago Barbosa Nobrega - 06/31205
     Davi Fantino da Silva - 06/40832
 */
int contarNroBitsArquivo(FILE *arq);

#endif
