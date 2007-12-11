#include "Controle.h"
#include <stdio.h>
#include <stdlib.h>
#include "Huffman.h"
#include "Descompressao.h"
#include "Lempel-Ziv.h"
#include "Relatorio.h"

/** Descomprimi o arquivo compactado tanto com Huffman quanto com Lempel-Ziv. */
void c_descomprimirArquivo(char *narqEntrada, char *narqSaida) {
    FILE *arqEntrada, *arqSaida;

    if ((arqEntrada = fopen(narqEntrada, "rb")) != NULL) {
	if ((arqSaida = fopen(narqSaida, "w")) != NULL) {
	    descomprimir(arqEntrada, arqSaida);
	    fclose(arqEntrada);
	    fclose(arqSaida);
	} else {
	    
	}
    } else {
	
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
    }

    arv = c_gerarArvoreHuffman(narqEntrada, &tamanho);
    nroBits[1]= c_compactarHuffman(narqEntrada, "huffman", arv, &tamanho);

    tabelaLZ = c_criarTabelaLempelZiv(narqEntrada);
    nroBits[2] = c_compactarLempelZiv(tabelaLZ, "lempelziv");

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
	} else {
	    
	}
    } else {
	
    }
    return nroBits;
}

/*CHAMA TODAS AS OUTRAS FUNCOES QUE TRABALHARAO DESDE A GERACAO, 
ATE A GRAVACAO DA TABELA.*/
tab *c_criarTabelaLempelZiv(char* narqEntrada) {
    int maiorIndice = 0, cont = 0, anterior = 0;
    reg *pinicio = NULL, *p2 = NULL, *paux = NULL;
    tab *inicioTabela = NULL, *elementoTab = NULL;
    FILE *arqEntrada = NULL;

    if ((arqEntrada = fopen(narqEntrada, "r")) != NULL) {
        pinicio = criarArvore(&maiorIndice, arqEntrada);
	for (cont = 1; cont <= maiorIndice; cont++) {
	    /*LEMPEL-ZIV.H*/
	    paux = buscarNaArvore(pinicio, cont, p2,&anterior);
	    elementoTab = calloc(1, sizeof(tab));
	    elementoTab->indice = cont;
	    elementoTab->letraRaiz = paux->letraRaiz;
	    elementoTab->indiceAnterior = anterior;
	    inicioTabela = adicionarNaLista(inicioTabela, elementoTab);
	}
	
    } else {
	
    }
    return inicioTabela;
}

int c_compactarLempelZiv(tab *pinicio, char* narqSaida) {
    FILE *arqSaida;
    int nroBits;

    if ((arqSaida = fopen(narqSaida, "w")) != NULL) {
        nroBits = compactarLempelZiv(pinicio, arqSaida);
    }

    return nroBits;
}
