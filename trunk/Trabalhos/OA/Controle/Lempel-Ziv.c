#include "Lempel-Ziv.h"
#include <stdlib.h>
#include <string.h>
#include "Controle.h"

reg* adicionarFilha(reg *p1, char caracter, int *contadorIndice);

/*A PARTIR DE UM ARQUIVO TEXTO, ESSA FUNCAO CRIA UMA ARVORE GENERICA,
IRMAOS(PROX) E FILHAS, CADA FILHA REPRESENTADO UM CHAR*/
reg *criarArvore(FILE *arq, int *contadorIndice) {
    char caracter;
    reg *pinicio = NULL, *p1 = NULL;
    int achou = 0, acabouArvore = 0, fimLinha = 0;

    while(!feof(arq)) {
	caracter = getc(arq);
        if(pinicio == NULL) {
            pinicio = malloc(sizeof(reg));
            pinicio->prox = NULL;
            pinicio->filhas = NULL;
            pinicio->letraRaiz = caracter;
            *contadorIndice +=1;
            pinicio->indice = *contadorIndice;
        } else {
	    acabouArvore = 0;
	    p1 = pinicio;
            while(acabouArvore == 0) {
                while ((achou == 0)&&(fimLinha == 0)) {
                    if(p1->letraRaiz == caracter) {
                        achou = 1;
                    } else {
                        if((p1->prox) != NULL) {
                            p1 = p1->prox;
                        } else {
                            fimLinha = 1;
                        }
                    }
                }
                if (achou == 0) {
                    acabouArvore = 1;
                    fimLinha = 0;
                    p1->prox = malloc(sizeof(reg));
                    p1 = p1->prox;
                    p1->letraRaiz = caracter;
                    *contadorIndice += 1;
                    p1->indice = *contadorIndice;
                    p1->prox = NULL;
                    p1->filhas = NULL;
                } else {
                    caracter = getc(arq);
		    p1 = adicionarFilha(p1, caracter, contadorIndice);
		    while (p1 != NULL) {
			caracter = getc(arq);
                        p1 = adicionarFilha(p1, caracter, contadorIndice);
		    }
		    acabouArvore = 1;
                    achou = 0;
                }
            }
        }
    }
    /*corrigirArvore(pinicio, &contadorIndice);*/
    return pinicio;
}

reg* adicionarFilha(reg *p1, char caracter, int *contadorIndice) {
    int achou = 0;

    if (p1->filhas != NULL) {
	p1 = p1->filhas;
	while ((p1->prox != NULL) && (achou == 0)) {
	    p1 = p1->prox;
	    if (p1->letraRaiz == caracter) {
		achou = 1;
	    }
	}
	if (achou == 0) {
	    p1->prox = malloc(sizeof(reg));
	    p1 = p1->prox;
	    p1->letraRaiz = caracter;
	    *contadorIndice += 1;
	    p1->indice = *contadorIndice;
	    p1->filhas = NULL;
	    p1->prox = NULL;
	} else {
            return p1;
	}
    } else {
	p1->filhas = malloc(sizeof(reg));
	p1 = p1->filhas;
	p1->letraRaiz = caracter;
	*contadorIndice += 1;
	p1->indice = *contadorIndice;
	p1->filhas = NULL;
	p1->prox = NULL;
    }
    return NULL;
}


/*ESSA FUNCAO GARANTE QUE O ULTIMO ELEMENTO DO INDICE NAO E O EOF,
E DESALOCA A MEMORIA USADA POR ELE
int corrigirArvore(reg *pinicio, int *maiorContador) {
    
    int achou = 0;
    if (pinicio != NULL) {
        if(pinicio->indice == *maiorContador) {
            if(pinicio->letraRaiz == EOF) {
                free(pinicio);
                *maiorContador = *maiorContador - 1;
            }
            achou = 1;
        }
        if(achou == 0) {
            if(pinicio->prox != NULL) {
               achou = corrigirArvore(*pinicio->prox, maiorContador);
            }
        }
        if(achou == 0) {
            if(pinicio->filhas != NULL) {
               achou = corrigirArvore(*pinicio->filhas, maiorContador);
            }
        }
    }
    return achou;
}*/

/*FAZ UMA BUSCA RECURSIVA NA ARVORE EM BUSCA DO INDICE EM QUESTAO, PERMITINDO A CONSTRUCAO DA LISTA QUE GERARA A TABELA
int buscarNaArvore(reg *pinicio, int cont, tab *pinicioTabela, reg *p2) {
    int achou = 0;
    if (pinicio != NULL) {

        if(pinicio->indice == cont) {
            if(p2 != NULL) {
                pinicioTabela = criarTabela(pinicioTabela, pinicio->indice, pinicio->letraRaiz, p2->indice);
            }else {

                pinicioTabela = criarTabela(pinicioTabela, pinicio->indice, pinicio->letraRaiz, 0);
            }
            achou = 1;
        }
        if(achou == 0) {
            if(pinicio->prox != NULL) {
               achou = buscarNaArvore(*pinicio->prox, cont, pinicioTabela, p2);
            }
        }
        if (achou == 0) {
            if(pinicio->filhas != NULL) {
                achou = buscarNaArvore(*pinicio->filhas, cont, pinicioTabela, pinicio);
            }
        }
    }
    return achou;
}*/

reg *buscarIndice(reg *pai, reg *no, int indice) {
    reg *p1 = NULL, *pret = NULL;

    p1 = no;
    if (p1 != NULL) {
	if (p1->indice == indice) {
	    return p1;
	} else if (p1->filhas != NULL) {
	    pret = buscarIndice(p1, p1->filhas, indice);
	} else if (pret == NULL) {
	    pret = buscarIndice(pai, p1->prox, indice);
	}
	return pret;
    }
    return NULL;
}

/*GRAVA UMA LISTA ENCADEADA A PARTIR DA ARVORE PARA POSSIBILITAR A GRAVACAO EM DISCO DA TABELA.*/
void criarTabela(tab *pinicioTabela, int indice, char letraRaiz, int indiceAnterior) {

    tab *pinicio = pinicioTabela;
    if (pinicio == NULL) {
        pinicio = malloc(sizeof(tab));
        pinicio->prox = NULL;
        pinicio->indiceAnterior = indiceAnterior;
        pinicio->indice = indice;
        pinicio->letraRaiz = letraRaiz;
    } else {
        tab *pCaminha = pinicio, *p1 = NULL;

        while (pCaminha->prox != NULL) {
            pCaminha = pCaminha->prox;
        }
        p1 = malloc(sizeof(tab));
        p1->prox = NULL;
        pCaminha->prox = p1;
        p1->indiceAnterior = indiceAnterior;
        p1->indice = indice;
        p1->letraRaiz = letraRaiz;
    }
}

void compactarLempelZiv(tab *pinicioTabela) {
    FILE *arq = fopen("escrita","w");
    tab *p1 = pinicioTabela;
    int bits = 0;

    while(p1->prox != NULL) {
        fwrite(&(p1)->indiceAnterior, (bits*2),1, arq);
        fwrite(&(p1)->letraRaiz, sizeof(char),1, arq);
        
    }
    fclose(arq);
}


