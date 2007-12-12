/** Programa de Compactação e Descompactação utilizando Huffman e Lempel-Ziv.

Autores do programa:
Arthur Thiago Barbosa Nobrega - 06/31205
Davi Fantino da Silva - 06/40832

Versão 1.0
Data: 11/12/2007
Compilador: gcc 4.1.2 20061115 (prerelease) (Debian 4.1.1-21)

Descrição: Este programa tem por objetivo dispor ao usuário compactar e descompactar arquivos utilizando Huffman e Lempel-Ziv. O usuário também tem a opção de simplesmente mostrar a tabela de Huffman do arquivo fornecido ou o dicionário de Lempel-Ziv, além de poder comparar qual o melhor algorítmo para compactar aquele determinado arquivo.
*/

#ifndef VIS_H
#define VIS_H
#include "../Tipos.h"

/** Função para mostrar o menu com os comandos na tela para o usuário poder digitar os comandos.
 * Data: 10/12/2007
 * Versão: 1.0
 * Autores:
     Arthur Thiago Barbosa Nobrega - 06/31205
     Davi Fantino da Silva - 06/40832
*/
void mostrarMenu();

#endif
