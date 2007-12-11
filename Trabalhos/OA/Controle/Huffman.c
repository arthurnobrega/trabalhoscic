#include "Huffman.h"
#include <stdlib.h>
#include <string.h>

no_arv *ordenarLista(no_arv *pinicio, int tamanho);
void gravarTabelaCodigos(FILE *arqSaida, no_arv *arv);
int gravarCodificacao(FILE *arqEntrada, FILE *arqSaida, no_arv *arv);

unsigned char buffer = 0;
int tamanhoBuffer = 0;

/** Constroi a lista de caracteres com as respectivas frequências. */
no_arv *construirLista(FILE *arq, int *tamanho) {
    int achou = 0;
    char ch;
    no_arv *pinicio, *pfim, *paux;

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

/* Função que ordena a lista passada como parâmetro por caractere. */
no_arv *ordenarLista(no_arv *pinicio, int tamanho) {
    int i = 0, j = 0;
    no_arv *paux, *paux2;
    for (i = 0; i <= tamanho - 1; i++) {
	paux = pinicio;
	j = 0;
	while ((j <= tamanho - 2) && (paux->prox != NULL)) {
	    paux2 = paux->prox;
	    if ((paux->frequencia > paux2->frequencia) || ((paux->frequencia == paux2->frequencia) && (paux->caractere > paux2->caractere))) {
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

/** Constroi a árvore de acordo com o algoritmo de Huffman. */
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
	pnovo->caractere = pinicio->caractere;

	pinicio = pnovo;
	pinicio = ordenarLista(pinicio, tamanho);
    }
    return pinicio;
}

/** Gera os códigos para os nós de acordo com a posição dos mesmos na árvore. */
void gerarCodigos(no_arv *arv, int profundidade, char *codigo) {
    if (arv->esq == NULL)  {
	strcpy(arv->codigo, codigo);
	codigo[profundidade] = '\0';
	arv->profundidade = profundidade;
	return;
    } else {
	codigo[profundidade] = '0';
	gerarCodigos(arv->esq, profundidade + 1, codigo);
	codigo[profundidade] = '1';
	gerarCodigos(arv->dir, profundidade + 1, codigo);
    }
}

/** Busca o nó com o caractere passado como parâmetro. */
no_arv *buscarNoCaractere(no_arv *arv, char caractere) {
    no_arv *no;
    if (arv->esq == NULL) {
	if (arv->caractere == caractere) {
	    return arv;
	}
    } else {
	if ((no = buscarNoCaractere(arv->esq, caractere)) != NULL) {
	    return no;
	} else if ((no = buscarNoCaractere(arv->dir, caractere)) != NULL) {
	    return no;
	}
    }
    return NULL;
}

/** Busca o nó com o código passado como parâmetro. */
no_arv *buscarNoCodigo(no_arv *arv, char *codigo, int profundidade) {
    no_arv *paux;
    int i;

    paux = arv;
    for (i = 0; i <= profundidade - 1; i++) {
	if (codigo[i] == '0') {
	    paux = paux->esq;
	} else {
	    paux = paux->dir;
	}
    }

    if (paux->esq == NULL) {
	return paux;
    }

    return NULL;
}

/** Compacta o arquivo utilizando Huffman. */
int compactarArquivoHuffman(FILE *arqEntrada, FILE *arqSaida, no_arv *arv, int tamanho) {
    char tam;
    int nroBits = 0;

    fputs("H\n", arqSaida);
    tam = tamanho;
    fputc(tam, arqSaida);
    fputs("\n", arqSaida);
    gravarTabelaCodigos(arqSaida, arv);
    nroBits = gravarCodificacao(arqEntrada, arqSaida, arv);
    fclose(arqEntrada);
    fclose(arqSaida);
    return nroBits;
}

/* Grava no arquivo a tabela(cabeçalho) necessária para a descompactação. */
void gravarTabelaCodigos(FILE *arqSaida, no_arv *arv) {
    if (arv->esq == NULL) {
	int profundidade, i;

	fwrite(&arv->caractere, 1, 1, arqSaida);
	profundidade = arv->profundidade;
	for (i = 0; i <= profundidade - 1; i++) {
	    fwrite(&arv->codigo[i], 1, 1, arqSaida);
	}
	fputc('\n', arqSaida);
    } else {
	gravarTabelaCodigos(arqSaida, arv->esq);
	gravarTabelaCodigos(arqSaida, arv->dir);
    }
}

/* Grava os códigos dos caracteres utilizando-se de um buffer. */
int gravarCodificacao(FILE *arqEntrada, FILE *arqSaida, no_arv *arv) {
    char ch;
    no_arv *no;
    int i, nroBits = 0;

    ch = fgetc(arqEntrada);
    while (!feof(arqEntrada)) {
	no = buscarNoCaractere(arv, ch);
	for (i = 0; i <= no->profundidade - 1; i++) {
	    nroBits++;
	    buffer <<= 1;
	    if (no->codigo[i] == '1') {
		buffer |= 1;
	    }
	    tamanhoBuffer++;
	    if (tamanhoBuffer == 8) {
		fputc(buffer, arqSaida);
		buffer = 0;
		tamanhoBuffer = 0;
	    }
	}
	ch = fgetc(arqEntrada);
    }
    buffer <<= 8 - tamanhoBuffer;
    fputc(buffer, arqSaida);
    fputc(tamanhoBuffer, arqSaida);

    return nroBits;
}
