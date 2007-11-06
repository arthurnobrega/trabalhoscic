#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_ARQ "arquivo.txt"
#define TAM_MAX 32
#define CAR_ESP 127

/** Estrutura do nó da árvore. */
struct no_arv {
    char caractere;
    int frequencia;
    int codigo;
    int tam_cod;
    struct no_arv *ant;
    struct no_arv *prox;
    struct no_arv *esq;
    struct no_arv *dir;
};


typedef struct no_arv no_arv;

no_arv *construirLista(FILE *arq, int *tamanho);
void ordenarLista(no_arv *pinicio, int tamanho);
void mostrarLista(no_arv *pinicio);
void construirArvore(no_arv *pinicio);
void mostrarArvore(no_arv *arv);
void gerarCodigos(no_arv *arv, int profundidade, int codigo);


int main() {
    FILE *arq;
    no_arv *listaArvore;
    int tamanho;

    listaArvore = construirLista(arq, &tamanho);
    mostrarLista(listaArvore);
    construirArvore(listaArvore);
    mostrarArvore(listaArvore);
    gerarCodigos(listaArvore, 0, 0);

    return 0;
}

no_arv *construirLista(FILE *arq, int *tamanho) {
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
    //ordenarLista(pinicio, *tamanho);
    return pinicio;
}

void ordenarLista(no_arv *pinicio, int tamanho) {
    int i, j;
    no_arv *paux, *ptroca;
    for (i = 0; i <= tamanho - 1; i++) {
	paux = pinicio;
	if (pinicio->frequencia > paux->prox->frequencia) {
	    ptroca = paux->prox;
	    paux->prox = ptroca->prox;
	    paux->ant = ptroca;
	    ptroca->prox->ant = paux;
	    ptroca->prox = paux;
	    ptroca->ant = NULL;
	    pinicio = ptroca;
	} else {
	    paux = paux->prox;
	}
	for (j = 0; j <= tamanho - 2; j++) {
	    if (paux->frequencia > paux->prox->frequencia) {
		ptroca = paux->prox;
		paux->prox = ptroca->prox;
		paux->ant->prox = ptroca;
		ptroca->ant = paux->ant;
		ptroca->prox->ant = paux;
		paux->ant = ptroca;
		ptroca->prox = paux;
	    } else {
		paux = paux->prox;
	    }
	}
    }
}

void mostrarLista(no_arv *pinicio) {
    no_arv *paux;

    paux = pinicio;
    printf("\n\n---Lista de Frequências (PROX)---\n");
    printf("NULL = ");
    printf("|%c : %d| = ",paux->caractere, paux->frequencia);
    while (paux->prox != NULL) {
	paux = paux->prox;
	printf("|%c : %d| = ",paux->caractere, paux->frequencia);
    }
    printf("NULL\n");
    printf("----------------------------------\n");
    printf("\n---Lista de Frequências (ANT)---\n");
    printf("NULL = ");
    while (paux != NULL) {
	printf("|%c : %d| = ",paux->caractere, paux->frequencia);
	paux = paux->ant;
    }
    printf("NULL\n");
    printf("----------------------------------\n\n");
}

void construirArvore(no_arv *pinicio) {
    no_arv *paux, *pnovo;

    paux = pinicio;
    while (pinicio->prox != NULL) {
	paux = pinicio->prox;
	pnovo = (no_arv *) calloc (1, sizeof(no_arv));
	
	pnovo->esq = pinicio;
	pnovo->dir = paux;
	if (paux->prox != NULL) {
	    pnovo->prox = paux->prox;
	    paux->prox->ant = pnovo;
	}
	pnovo->ant = NULL;
	pinicio->prox = NULL;
	paux->ant = NULL;
	paux->prox = NULL;
	pnovo->frequencia = pinicio->frequencia + paux->frequencia;
	pnovo->caractere = CAR_ESP;
	printf("%c", pnovo->caractere);
	printf("%c", pinicio->caractere);
	printf("%c", paux->caractere);

	pinicio = pnovo;
    }
}

void mostrarArvore(no_arv *arv) {
    if (arv != NULL) {
	printf("\n");
	printf("|%c : %d| ",arv->caractere, arv->frequencia);
	mostrarArvore(arv->esq);
	mostrarArvore(arv->dir);
	printf("\n");
    } else {
	printf("NULL ");
    }
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
