#include "Controle.h"
#include <stdio.h>
#include "Huffman.h"
#include "Lempel-Ziv.h"
#include "../Persistencia/Arquivos.h"

no_arv *gerarArvoreHuffman(char nomeArq[TAM_MAX], int *tamanho) {
    no_arv *arv;

    arv = construirLista(nomeArq, tamanho);
    arv = construirArvore(arv, *tamanho);
    gerarCodigos(arv, 0, 0);

    return arv;
}

void gerarArquivoHuffman(char nomeArq[TAM_MAX], no_arv *arv, int *tamanho) {

    arv = construirLista(nomeArq, tamanho);
    arv = construirArvore(arv, *tamanho);
    gerarCodigos(arv, 0, 0);
    compactarArquivoHuffman(nomeArq, arv);

    return;
}


