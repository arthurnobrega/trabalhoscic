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
