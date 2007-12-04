#include "Controle.h"
#include <stdio.h>
#include "Huffman.h"
#include "Descompressao.h"
#include "Lempel-Ziv.h"

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
void c_compactarHuffman(char *narqEntrada, char *narqSaida, no_arv *arv, int *tamanho) {
    FILE *arqEntrada, *arqSaida;

    if ((arqEntrada = fopen(narqEntrada, "r")) != NULL) {
	if ((arqSaida = fopen(narqSaida, "wb")) != NULL) {
	    arv = c_gerarArvoreHuffman(narqEntrada, tamanho);
	    compactarArquivoHuffman(arqEntrada, arqSaida, arv, *tamanho);
	} else {
	    
	}
    } else {
	
    }
}

/** Descomprimi o arquivo compactado tanto com Huffman quanto com Lempel-Ziv. */
void c_descomprimirArquivo(char *narqEntrada, char *narqSaida) {
    FILE *arqEntrada, *arqSaida;

    if ((arqEntrada = fopen(narqEntrada, "rb")) != NULL) {
	if ((arqSaida = fopen(narqSaida, "w")) != NULL) {
	   descomprimir(arqEntrada, arqSaida);
	} else {
	    
	}
    } else {
	
    }

}

/** FUNCAO RESPONSAVEL GERAR E GRAVAR A TABELA VIA METODO LEMPEL-ZIV. */
tab *c_gerarTabelaLZ(char *nomeArq) {
    tab *pinicioTabela = NULL;
    reg *pinicio = NULL, *p1 = NULL, *pai = NULL;
    int cont, maiorIndice = 0;
    FILE *arq;

    if ((arq= fopen(nomeArq, "r")) != NULL) {
	pinicio = criarArvore(arq, &maiorIndice);
	for (cont = 1; cont <= maiorIndice; cont++) {
	    pai = NULL;
	    p1 = buscarIndice(pai, pinicio, cont);
	    if (pai != NULL) {
	    criarTabela(pinicioTabela, p1->indice, p1->letraRaiz, pai->indice);
	    } else {
		criarTabela(pinicioTabela, p1->indice, p1->letraRaiz, 0);
	    }
	}
    }
    return pinicioTabela;
}
