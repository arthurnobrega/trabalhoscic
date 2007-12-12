/** Programa de Compactação e Descompactação utilizando Huffman e Lempel-Ziv.

Autores do programa:
Arthur Thiago Barbosa Nobrega - 06/31205
Davi Fantino da Silva - 06/40832

Versão 1.0
Data: 11/12/2007
Compilador: gcc 4.1.2 20061115 (prerelease) (Debian 4.1.1-21)

Descrição: Este programa tem por objetivo dispor ao usuário compactar e descompactar arquivos utilizando Huffman e Lempel-Ziv. O usuário também tem a opção de simplesmente mostrar a tabela de Huffman do arquivo fornecido ou o dicionário de Lempel-Ziv, além de poder comparar qual o melhor algorítmo para compactar aquele determinado arquivo.
*/

#ifndef DESC_H
#define DESC_H
#include "../Tipos.h"
#include <stdio.h>

/** Função para descomprimir arquivos compactados com Huffman ou Lempel-Ziv. 
 * arqEntrada: arquivo binário de entrada que se deseja descomprimir.
 * arqSaida: arquivo texto onde será salvo o texto original.
*/
void descomprimir(FILE *arqEntrada, FILE *arqSaida);

#endif
