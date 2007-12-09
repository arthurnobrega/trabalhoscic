#ifndef LEMP_H
#define LEMP_H
#include <stdio.h>
#include "../Tipos.h"

/*FUNCOES DE GERACAO DA TABELA*/
int buscarNaArvore(reg, int, reg*);
reg* criarArvore(int*, int*, char[TAM_MAX]);
int corrigirBytes(reg , int* , reg*, int*);
void compactarLempelZiv(tab*);

#endif
