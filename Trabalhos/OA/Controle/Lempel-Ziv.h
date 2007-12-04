#ifndef LEMP_H
#define LEMP_H
#include "../Tipos.h"

/*FUNCOES DE GERACAO DA TABELA*/
tab* criarTabela(tab *pinicioTabela, int indice, char letraRaiz, int indiceAnterior);
int buscarNaArvore(reg pinicio, int cont, tab *pinicioTabela, reg p2);


void criarArvore(reg *pretorno, int* maiorContador);
int corrigirArvore(reg pinicio, int* maiorContador);

#endif
