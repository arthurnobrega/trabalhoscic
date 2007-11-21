#ifndef CONT_H
#define CONT_H
#include "../Tipos.h"

no_arv *c_gerarArvoreHuffman(char *nomeArq, int *tamanho);
void c_compactarHuffman(char *narqEntrada, char *narqSaida, no_arv *arv, int *tamanho);
void c_descomprimirArquivo(char *narqEntrada, char *narqSaida);

#endif
