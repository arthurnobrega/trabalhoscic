#ifndef LEMP_H
#define LEMP_H
#include "../Tipos.h"

/*FUNCOES DE GERACAO DA TABELA*/
void criarTabela(tab*, int , char , int );
int buscarNaArvore(reg , int , tab* , reg);


void criarArvore( reg*, int* );
int corrigirArvore(reg , int* );

#endif
