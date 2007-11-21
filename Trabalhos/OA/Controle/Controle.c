#include "Controle.h"
#include <stdio.h>
#include "Huffman.h"
#include "../Persistencia/Arquivos.h"
#include "Descompressao.h"

no_arv *c_gerarArvoreHuffman(char *nomeArq, int *tamanho) {
    no_arv *arv;
    char codigo[TAM_MAX];
    FILE *arqEntrada;

    if (abrirArquivo(arqEntrada, nomeArq, "r")) {
	arv = construirLista(arqEntrada, tamanho);
	arv = construirArvore(arv, *tamanho);
	gerarCodigos(arv, 0, codigo);

	return arv;
    } else {
	
    }

    return NULL;
}

void c_compactarHuffman(char *narqEntrada, char *narqSaida, no_arv *arv, int *tamanho) {
    FILE *arqEntrada, *arqSaida;

    if (abrirArquivo(arqEntrada, narqEntrada, "r")) {
	if (abrirArquivo(arqSaida, narqSaida, "wb")) {
	    arv = c_gerarArvoreHuffman(narqEntrada, tamanho);
	    compactarArquivoHuffman(arqEntrada, arqSaida, arv, *tamanho);
	} else {
	    
	}
    } else {
	
    }
}

void c_descomprimirArquivo(char *narqEntrada, char *narqSaida) {
    FILE *arqEntrada, *arqSaida;

    if (abrirArquivo(arqEntrada, narqEntrada, "rb")) {
	if (abrirArquivo(arqSaida, narqSaida, "w")) {
	   descomprimir(arqEntrada, arqSaida);
	} else {
	    
	}
    } else {
	
    }

}


