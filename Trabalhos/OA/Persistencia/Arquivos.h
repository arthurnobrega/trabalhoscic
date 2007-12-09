#ifndef ARQ_H
#define ARQ_H
#include "../Tipos.h"
#include <stdio.h>

int abrirArquivo(FILE *arq, char *nomeArq, char *modo);

void gravarMaiorIndiceTabela(int );


void gravarTabelaArq(int , char ,int );
tab* criarTabela(void);
#endif
