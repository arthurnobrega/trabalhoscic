#include "Huffman.h"
#include <stdio.h>
#include <stdlib.h>


no_arv *construirLista(char *nomeArq, int *tamanho) {
    FILE *arq;
    int achou = 0;
    char ch;
    no_arv *pinicio, *pfim, *paux;

    /* Abre o arquivo. */
    arq = fopen(nomeArq, "r");

    /* Cria o primeiro elemento da lista. */
    pinicio = (no_arv *) calloc(1, sizeof(no_arv));
    pfim = pinicio;
    paux = pinicio;
    ch = fgetc(arq);
    paux->caractere = ch;
    paux->frequencia = 1;
    paux->ant = NULL;
    paux->prox = NULL;
    paux->esq = NULL;
    paux->dir = NULL;
    *tamanho = 1;
    /* Adiciona os outros elementos à lista. */
    while ((ch = fgetc(arq)) != EOF) {
	paux = pinicio;
	while (paux != NULL) {
	    /* Se o caractere já existir na lista, soma 1 na frequência. */
	    if (paux->caractere == ch) {
		paux->frequencia += 1;
		achou = 1;
		break;
	    }
	    pfim = paux;
	    paux = paux->prox;
	}
	/* Se é o caractere não existir na lista, o adiciona. */
	if (achou == 0) {
	    paux = (no_arv *) calloc(1, sizeof(no_arv));
	    paux->caractere = ch;
	    paux->frequencia = 1;
	    paux->ant = pfim;
	    paux->prox = NULL;
	    pfim->prox = paux;
	    paux->esq = NULL;
	    paux->dir = NULL;
	    *tamanho += 1;
	} else {
	    achou = 0;
	}
    }
    pinicio = ordenarLista(pinicio, *tamanho);
    return pinicio;
}

no_arv *ordenarLista(no_arv *pinicio, int tamanho) {
    int i = 0, j = 0;
    no_arv *paux, *paux2;
    for (i = 0; i <= tamanho - 1; i++) {
	paux = pinicio;
	j = 0;
	while ((j <= tamanho - 2) && (paux->prox != NULL)) {
	    paux2 = paux->prox;
	    if (paux->frequencia > paux2->frequencia) {
		if (j == 0) {
		    pinicio = paux2;
		} else {
		    paux->ant->prox = paux2;
		}
		if (paux2->prox != NULL) {
		    paux2->prox->ant = paux;
		}
		paux->prox = paux2->prox;
		paux2->ant = paux->ant;
		paux->ant = paux2;
		paux2->prox = paux;
	    } else {
		paux = paux->prox;
	    }
	    j++;
	}
    }
    return pinicio;
}

no_arv *construirArvore(no_arv *pinicio, int tamanho) {
    no_arv *paux, *pnovo;

    paux = pinicio;
    while (pinicio->prox != NULL) {
	paux = pinicio->prox;
	pnovo = (no_arv *) calloc (1, sizeof(no_arv));
	
	pnovo->esq = pinicio;
	pnovo->dir = paux;
	pnovo->prox = paux->prox;
	if (paux->prox != NULL) {
	    paux->prox->ant = pnovo;
	}
	pnovo->ant = NULL;
	pinicio->prox = NULL;
	paux->ant = NULL;
	paux->prox = NULL;
	pnovo->frequencia = pinicio->frequencia + paux->frequencia;
	pnovo->caractere = CAR_ESP;

	pinicio = pnovo;
	pinicio = ordenarLista(pinicio, tamanho);
    }
    return pinicio;
}

void gerarCodigos(no_arv *arv, int profundidade, int codigo) {
    if (arv->caractere != CAR_ESP) {
	arv->codigo = codigo;
	arv->tam_cod = profundidade;
	return;
    } else {
	codigo <<= 1;
	profundidade++;
	gerarCodigos(arv->esq, profundidade, codigo);
	codigo |= 1;
	gerarCodigos(arv->dir, profundidade, codigo);
    }
}
