#include "Controle.h"
#include <stdio.h>
#include "Huffman.h"
#include "Lempel-Ziv.h"
#include "../Persistencia/Arquivos.h"

no_arv *gerarArvoreHuffman(char nomeArq[TAM_MAX], int *tamanho) {
    no_arv *arv;
    char codigo[TAM_MAX] ;

    codigo[0] = CAR_ESP;

    arv = construirLista(nomeArq, tamanho);
    arv = construirArvore(arv, *tamanho);
    gerarCodigos(arv, 0, codigo);

    return arv;
}

void gerarArquivoHuffman(char arqEntrada[TAM_MAX], char arqSaida[TAM_MAX], no_arv *arv, int *tamanho) {
    char codigo[TAM_MAX];

    codigo[0] = CAR_ESP;

    arv = construirLista(arqEntrada, tamanho);
    arv = construirArvore(arv, *tamanho);
    gerarCodigos(arv, 0, codigo);
    compactarArquivoHuffman(arqSaida, arv);

    return;
}


