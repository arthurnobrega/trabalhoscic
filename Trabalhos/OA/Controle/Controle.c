#include "Controle.h"
#include <stdio.h>
#include "Huffman.h"
#include "Lempel-Ziv.h"
#include "../Persistencia/Arquivos.h"
#include "Descompressao.h"

no_arv *gerarArvoreHuffman(char nomeArq[TAM_MAX], int *tamanho) {
    no_arv *arv;
    char codigo[TAM_MAX];

    arv = construirLista(nomeArq, tamanho);
    arv = construirArvore(arv, *tamanho);
    gerarCodigos(arv, 0, codigo);

    return arv;
}

void gerarArquivoHuffman(char narqEntrada[TAM_MAX], char narqSaida[TAM_MAX], no_arv *arv, int *tamanho) {

    arv = gerarArvoreHuffman(narqEntrada, tamanho);
    compactarArquivoHuffman(narqEntrada, narqSaida, arv, *tamanho);

    return;
}

void descomprimirArquivo(char narqEntrada[TAM_MAX], char narqSaida[TAM_MAX]) {
    descomprimir(narqEntrada, narqSaida);
}


