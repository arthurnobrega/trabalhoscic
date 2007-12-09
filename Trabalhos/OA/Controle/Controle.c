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

/*CHAMA TODAS AS OUTRAS FUNCOES QUE TRABALHARAO DESDE A GERACAO, 
ATE A GRAVACAO DA TABELA.*/
int gravarTabela(char* arqEntrada){
    int maiorIndice = 0;
    int bytes = 0;
    reg* pinicio = criarArvore(&maiorIndice, &bytes, arqEntrada);
    reg* p2 = NULL;
    int cont;

    /*ARQUIVOS.H*/
    gravarMaiorIndiceTabela(maiorIndice);
    for (cont = 1; cont <= maiorIndice; cont++){

        /*LEMPEL-ZIV.H*/
        buscarNaArvore(*pinicio ,cont, p2);
    }
    free(pinicio);
    free(p2);
    return bytes;
}

/*INTERFACE DE BUSCA DA TABELA GERADA E GRAVADA NO ARQUIVO*/
tab* resgatarTabela(void){

    /*ARQUIVO.H*/
    tab* pinicio = criarTabela();
    return pinicio;
}
