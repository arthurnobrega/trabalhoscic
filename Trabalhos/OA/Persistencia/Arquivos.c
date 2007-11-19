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

    fwrite("H\n", 2, 2 , arqSaida);
    tam = tamanho;
    fwrite(&tam, 1, 1, arqSaida);
    fwrite("\n", 1, 1, arqSaida);
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
	fwrite("\n", 1, 1, arqSaida);
    } else {
	gravarTabelaCodigos(arqSaida, arv->esq);
	gravarTabelaCodigos(arqSaida, arv->dir);
    }
}

void gravarCodificacao(FILE *arqEntrada, FILE *arqSaida, no_arv *arv) {
    char ch;
    no_arv *no;
    int profundidade, i;

    while ((ch = fgetc(arqEntrada)) != EOF) {
	no = buscarNoCaractere(arv, ch);
	profundidade = no->profundidade;
	for (i = 0; i <= profundidade - 1; i++) {
	    buffer <<= 1;
	    if (no->codigo[i] == '1') {
		buffer |= 1;
	    }
	    tamanhoBuffer++;
	    if (tamanhoBuffer == 8) {
		fwrite(&buffer, 1, 1, arqSaida);
		buffer = 0;
		tamanhoBuffer = 0;
	    }
	}
    }
}
