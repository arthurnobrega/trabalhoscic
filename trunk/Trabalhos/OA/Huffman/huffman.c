#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_ARQ "arquivo.txt"
#define TAM_MAX 32
#define CAR_ESP '$'

/** Estrutura do nó da árvore. */
struct no_arv {
    char caractere;
    int frequencia;
    struct no_arv *ant;
    struct no_arv *prox;
    struct no_arv *esq;
    struct no_arv *dir;
};


typedef struct no_arv no_arv;

no_arv *construirLista(FILE *arq);
void mostrarLista(no_arv *pinicio);
no_arv *construirArvore(no_arv *pinicio);
void mostrarArvore(no_arv *arv);


int main() {
    FILE *arq;
    no_arv *listaArvore;

    listaArvore = construirLista(arq);
    mostrarLista(listaArvore);
    listaArvore = construirArvore(listaArvore);
    mostrarArvore(listaArvore);

    return 0;
}

no_arv *construirLista(FILE *arq) {
    int achou = 0;
    char ch;
    no_arv *pinicio, *pfim, *paux;

    /* Abre o arquivo. */
    arq = fopen(NOME_ARQ, "r");

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
	} else {
	    achou = 0;
	}

    }

    /* Ordena a lista. */

    return pinicio;
}

void mostrarLista(no_arv *pinicio) {
    no_arv *paux = pinicio;
    printf("---Tabela de Frequências---\n");
    while (paux != NULL) {
	printf("%c : %d\n",paux->caractere, paux->frequencia);
    }
    printf("---------------------------\n");
}

no_arv *construirArvore(no_arv *pinicio) {
    no_arv *paux, *paux2, *pnovo;

    while (paux != NULL) {
	paux = pinicio;
	paux2 = paux->prox;
	pnovo = (no_arv *) calloc (1, sizeof(no_arv));
	
	pnovo->esq = paux;
	paux->prox = NULL;
	pnovo->dir = paux2;
	paux2->ant = NULL;
	paux2->prox->ant = NULL;
	paux2->prox = NULL;
	pnovo->caractere = CAR_ESP;
	pnovo->frequencia = paux->frequencia + paux2->frequencia;
	
	/* Ordena a lista. */
    }

    return pinicio;
}

void mostrarArvore(no_arv *arv) {
    if (arv != NULL)
    {
	printf("%c : %d\n",arv->caractere, arv->frequencia);
	mostrarArvore(arv->esq);
	mostrarArvore(arv->dir);
    } else {
	printf("NULL\n");
    }
}
/*
el_cod *gerarListaCodigos(no_arv *arv, int tamanho) {
    el_cod *cod;
    int indice;
    char codigo[TAM_MAX];

    cod = calloc(tamanho, sizeof(el_cod));
    preencherCodigos(cod, arv, &indice, codigo);
    return cod;
}

void preencherCodigos(el_cod *cod, no_arv *arv, int *indice, char codigo[TAM_MAX]) {
    if ((arv != NULL &&) {
	 if (arv->caractere != CAR_ESP)) {
	    cod[*indice].codigo = codigo;
	    *indice += 1;
	    return;
	 } else {
	    preencherCodigos(cod, arv->esq, indice, strcat(codigo, "0"));
	    preencherCodigos(cod, arv->dir, indice, strcat(codigo, "1"));
	}
    }
}*/

