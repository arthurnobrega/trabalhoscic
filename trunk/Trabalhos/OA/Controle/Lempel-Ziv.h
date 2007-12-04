#ifndef LEMP_H
#define LEMP_H
#include <stdio.h>
#include "../Tipos.h"

reg *criarArvore(FILE *arq, int *contadorIndice);
/*int corrigirArvore(reg pinicio, int* maiorContador);*/
reg *buscarIndice(reg *pai, reg *reg, int indice);

/*FUNCOES DE GERACAO DA TABELA*/
void criarTabela(tab *pinicioTabela, int indice, char letraRaiz, int indiceAnterior);
int buscarNaArvore(reg *pinicio, int cont, tab *pinicioTabela, reg *p2);

#endif
