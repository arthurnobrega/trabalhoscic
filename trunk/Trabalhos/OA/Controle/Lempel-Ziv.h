#ifndef LEMP_H
#define LEMP_H
#include <stdio.h>
#include "../Tipos.h"

/*FUNCOES DE GERACAO DA TABELA*/
reg* criarArvore(int* maiorContador, int* bytes,char* arqEntrada);
int corrigirBytes(reg p, int* maiorContador, reg* p2, int *bytes);
int buscarNaArvore(reg p, int cont, reg* p2);
void compactarLempelZiv(tab* pinicioTabela, FILE *arq);

#endif
