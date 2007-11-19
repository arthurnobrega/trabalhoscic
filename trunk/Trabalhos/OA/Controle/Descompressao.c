#include "Descompressao.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Persistencia/Arquivos.h"
#include "Huffman.h"

void descomprimir(char narqEntrada[TAM_MAX], char narqSaida[TAM_MAX]);
no_arv *lerTabelaHuffman(FILE *arqEntrada);
void reconstruirArvoreHuffman(no_arv *arv, char caractere, char codigo[TAM_MAX], int profundidade);
void escreverArquivoTexto(FILE *arqEntrada, FILE *arqSaida, no_arv *arv);

void descomprimir(char narqEntrada[TAM_MAX], char narqSaida[TAM_MAX]) {
    FILE *arqSaida, *arqEntrada;
    char ch;
    no_arv *arv;

    /* Abre o arquivo de Entrada. */
    arqEntrada = fopen(narqEntrada, "rb");
    /* Cria o arquivo de Saída. */
    arqSaida = fopen(narqSaida, "w");

    ch = fgetc(arqEntrada);
    if (ch == 'H') {
	ch = fgetc(arqEntrada);
	arv = lerTabelaHuffman(arqEntrada);
	escreverArquivoTexto(arqEntrada, arqSaida, arv);
    } else if (ch == 'L') {
	
    }
    fclose(arqEntrada);
    fclose(arqSaida);
}

no_arv *lerTabelaHuffman(FILE *arqEntrada) {
    char ch, caractere, codigo[TAM_MAX], nroLinhas;
    int i, tamanho;
    no_arv *arv;

    arv = calloc(1, sizeof(no_arv));
    nroLinhas = fgetc(arqEntrada);
    caractere = fgetc(arqEntrada);
    for (i = 0; i <= nroLinhas - 1; i++) {
	caractere = fgetc(arqEntrada);
	tamanho = 0;
	while((ch = fgetc(arqEntrada)) != '\n') {
	    tamanho++;
	    codigo[tamanho - 1] = ch;
	}
	reconstruirArvoreHuffman(arv, caractere, codigo, tamanho);
    }

    return arv;
}

void reconstruirArvoreHuffman(no_arv *arv, char caractere, char codigo[TAM_MAX], int profundidade) {
    no_arv *paux, *pnovo;
    int i;

    paux = arv;
    for (i = 0; i <= profundidade - 1; i++) {
	if (codigo[i] == '0') {
	    if (paux->esq == NULL) {
	       pnovo = calloc(1, sizeof(no_arv));
	       pnovo->esq = NULL;
	       pnovo->dir = NULL;
	       paux->esq = pnovo;
	    }
	    paux = paux->esq;
	} else {
	    if (paux->dir == NULL) {
		pnovo = calloc(1, sizeof(no_arv));
		pnovo->esq = NULL;
		pnovo->dir = NULL;
		paux->dir = pnovo;
	    }
	    paux = paux->dir;
	}
    }
    strcpy(paux->codigo,codigo);
    paux->profundidade = profundidade;
    paux->caractere = caractere;
}

void escreverArquivoTexto(FILE *arqEntrada, FILE *arqSaida, no_arv *arv) {
    char ch, vetorCod[TAM_MAX];
    unsigned char caux;
    int tamanho = 0, i, nroBits;
    no_arv *no;

    nroBits = 8;
    while ((ch = fgetc(arqEntrada)) != EOF) {
	if (ch == CAR_MARC) {
	    nroBits = fgetc(arqEntrada);
	    ch = fgetc(arqEntrada);
	}
	caux = 128;
	for (i = 0; i <= nroBits - 1; i++) {
	    if (caux & ch) {
		vetorCod[tamanho] = '1';
	    } else {
		vetorCod[tamanho] = '0';
	    }
	    tamanho++;
	    caux >>= 1;
	    no = buscarNoCodigo(arv, vetorCod, tamanho);
	    if (no != NULL) {
		tamanho = 0;
		fwrite(&no->caractere, 1, 1, arqSaida);
		no = NULL;
	    }
	}
    }
}
