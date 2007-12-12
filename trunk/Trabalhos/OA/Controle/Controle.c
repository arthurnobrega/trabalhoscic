/** Programa de Compactação e Descompactação utilizando Huffman e Lempel-Ziv.

Autores do programa:
Arthur Thiago Barbosa Nobrega - 06/31205
Davi Fantino da Silva - 06/40832

Versão 1.0
Data: 11/12/2007
Compilador: gcc 4.1.2 20061115 (prerelease) (Debian 4.1.1-21)

Descrição: Este programa tem por objetivo dispor ao usuário compactar e descompactar arquivos utilizando Huffman e Lempel-Ziv. O usuário também tem a opção de simplesmente mostrar a tabela de Huffman do arquivo fornecido ou o dicionário de Lempel-Ziv, além de poder comparar qual o melhor algorítmo para compactar aquele determinado arquivo.
*/

#include "Controle.h"
#include <stdio.h>
#include <stdlib.h>
#include "Huffman.h"
#include "Descompressao.h"
#include "Lempel-Ziv.h"

int contarNroBitsArquivo(FILE *arq);

/** Descomprimi o arquivo compactado tanto com Huffman quanto com Lempel-Ziv. */
void c_descomprimirArquivo(char *narqEntrada, char *narqSaida) {
    FILE *arqEntrada, *arqSaida;

    if ((arqEntrada = fopen(narqEntrada, "rb")) != NULL) {
	if ((arqSaida = fopen(narqSaida, "w")) != NULL) {
	    descomprimir(arqEntrada, arqSaida);
	    fclose(arqEntrada);
	    fclose(arqSaida);
	    printf("O Arquivo \"%s\" foi descompactado como \"%s\"!\n", narqEntrada, narqSaida);
	} else {
	    printf("O arquivo texto \"%s\" não pôde ser aberto!\n", narqEntrada);
	}
    } else {
	printf("O arquivo binário \"%s\" não pôde ser aberto!\n", narqSaida);
    }
}

/** Coleta o número de bits do arquivo original, compactado com Huffman e com Lempel-Ziv. */
int *c_gerarRelatorio(char* narqEntrada) {
    int tamanho = 0;
    no_arv *arv;
    tab *tabelaLZ;
    int *nroBits;
    FILE *arqEntrada;

    nroBits = calloc(3, sizeof(int));
    if ((arqEntrada = fopen(narqEntrada, "r")) != NULL) {
        nroBits[0] = contarNroBitsArquivo(arqEntrada);
	
	arv = c_gerarArvoreHuffman(narqEntrada, &tamanho);
	nroBits[1]= c_compactarHuffman(narqEntrada, "huffman", arv, &tamanho);
	
	tabelaLZ = c_criarTabelaLempelZiv(narqEntrada);
	nroBits[2] = c_compactarLempelZiv(tabelaLZ, "lempelziv");
    } else {
	printf("O arquivo texto \"%s\" não pôde ser aberto!\n", narqEntrada);
    }

    return nroBits;
}

/** Gera a árvore de Huffman. */
no_arv *c_gerarArvoreHuffman(char *nomeArq, int *tamanho) {
    no_arv *arv;
    char codigo[TAM_MAX];
    FILE *arqEntrada;

    if ((arqEntrada = fopen(nomeArq, "r")) != NULL) {
	arv = construirLista(arqEntrada, tamanho);
	arv = construirArvore(arv, *tamanho);
	gerarCodigos(arv, 0, codigo);

	return arv;
    } else {
	printf("O arquivo texto \"%s\" não pôde ser aberto!\n", nomeArq);
    }

    return NULL;
}

/** Compacta o arquivo com o algoritmo de Huffman. */
int c_compactarHuffman(char *narqEntrada, char *narqSaida, no_arv *arv, int *tamanho) {
    FILE *arqEntrada, *arqSaida;
    int nroBits = 0;

    if ((arqEntrada = fopen(narqEntrada, "r")) != NULL) {
	if ((arqSaida = fopen(narqSaida, "wb")) != NULL) {
	    arv = c_gerarArvoreHuffman(narqEntrada, tamanho);
	    nroBits = compactarArquivoHuffman(arqEntrada, arqSaida, arv, *tamanho);
	    printf("O Arquivo \"%s\" foi compactado como \"%s\" utilizando Huffman!\n", narqEntrada, narqSaida);
	} else {
	    printf("O arquivo binário \"%s\" não pôde ser aberto!\n", narqSaida);
	}
    } else {
	printf("O arquivo texto \"%s\" não pôde ser aberto!\n", narqEntrada);
    }
    return nroBits;
}

/** Chama todas as outras funções que trabalharão desde a geração até a gravação da tabela. */
tab *c_criarTabelaLempelZiv(char* narqEntrada) {
    tab *inicioTabela = NULL;
    FILE *arqEntrada = NULL;

    if ((arqEntrada = fopen(narqEntrada, "r")) != NULL) {
        inicioTabela = criarArvoreLista(arqEntrada);
    } else {
	printf("O arquivo texto \"%s\" não pôde ser aberto!\n", narqEntrada);
	return NULL;
    }

    return inicioTabela;
}

/** Compacta o arquivo com o algoritmo de Lempel-Ziv. */
int c_compactarLempelZiv(tab *pinicio, char* narqSaida) {
    FILE *arqSaida;
    int nroBits = 0;

    if ((arqSaida = fopen(narqSaida, "w")) != NULL) {
        nroBits = compactarLempelZiv(pinicio, arqSaida);
	printf("O Arquivo foi compactado como \"%s\" utilizando Lempel-Ziv!\n", narqSaida);
    } else {
	printf("O arquivo binário \"%s\" não pôde ser aberto!\n", narqSaida);
    }

    return nroBits;
}

int contarNroBitsArquivo(FILE *arq) {
    char ch;
    int nroBits = 0;
    ch = fgetc(arq);
    while (!feof(arq)) {
	nroBits += 8;
	ch = fgetc(arq);
    }

    return nroBits;
}
