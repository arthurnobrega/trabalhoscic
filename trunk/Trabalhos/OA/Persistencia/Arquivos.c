#include "Arquivos.h"
#include <stdio.h>
#include "../Controle/Huffman.h"

void compactarArquivoHuffman(char *narqEntrada, char *narqSaida, no_arv *arv, int tamanho);
void gravarTabelaCodigos(FILE *arq, no_arv *arv);
void gravarCodificacao(FILE *arqEntrada, FILE *arqSaida, no_arv *arv);


unsigned char buffer = 0;
int tamanhoBuffer = 0;

void compactarArquivoHuffman(char *narqEntrada, char *narqSaida, no_arv *arv, int tamanho) {
    FILE *arqSaida, *arqEntrada;
    char tam;

    /* Abre o arquivo de Entrada. */
    arqEntrada = fopen(narqEntrada, "r");
    /* Cria o arquivo de Saída. */
    arqSaida = fopen(narqSaida, "wb");

    fputs("H\n", arqSaida);
    tam = tamanho;
    fputc(tam, arqSaida);
    fputs("\n", arqSaida);
    gravarTabelaCodigos(arqSaida, arv);
    gravarCodificacao(arqEntrada, arqSaida, arv);
    fclose(arqEntrada);
    fclose(arqSaida);
}

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

void gravarCodificacao(FILE *arqEntrada, FILE *arqSaida, no_arv *arv) {
    char ch, chprox;
    no_arv *no;
    int i;

    ch = fgetc(arqEntrada);
    chprox = fgetc(arqEntrada);
    while (chprox != EOF) {
	no = buscarNoCaractere(arv, ch);
	for (i = 0; i <= no->profundidade - 1; i++) {
	    buffer <<= 1;
	    if (no->codigo[i] == '1') {
		buffer |= 1;
	    }
	    tamanhoBuffer++;
	    if (tamanhoBuffer == 8) {
		fputc(buffer, arqSaida);
		printf("%d ", buffer);
		buffer = 0;
		tamanhoBuffer = 0;
	    }
	}
	ch = chprox;
	chprox = fgetc(arqEntrada);
    }
    fputc(CAR_MARC, arqSaida);
    fputc(tamanhoBuffer, arqSaida);
    buffer <<= 8 - tamanhoBuffer;
    fputc(buffer, arqSaida);
    printf("%d ", CAR_MARC);
    printf("%d ", tamanhoBuffer);
    printf("%d ", buffer);
}
