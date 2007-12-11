#ifndef LEMP_H
#define LEMP_H
#include <stdio.h>
#include "../Tipos.h"

/*FUNCOES DE GERACAO DA TABELA*/
reg* criarArvore(int* maiorContador, FILE* arq);
int corrigirBytes(reg p, int* maiorContador, reg* p2, int *bytes);
reg *buscarNaArvore(reg *pinicio, int cont, reg *p2, int *anterior);
int compactarLempelZiv(tab* pinicioTabela, FILE *arq);
tab *adicionarNaLista(tab *pinicio, tab *registro);

#endif
