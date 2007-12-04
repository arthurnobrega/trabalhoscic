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

/*FUNCAO RESPONSAVEL GERAR E GRAVAR A TABELA VIA METODO LEMPEL-ZIV.*/
void gravarTabela(tab *pinicioTabela){
    reg pinicio = NULL;
    reg p2 = NULL;
    int cont;
    int maiorIndice = 0;
    criarArvore(&pinicio, &maiorIndice);
    for (cont = 0; cont < maiorIndice; cont++){
        buscarNaArvore( pinicio ,cont, pinicioTabela, p2);
    }
}






