#ifndef TIPOS_H
#define TIPOS_H
#define TAM_MAX 256

/** Estrutura do nó da árvore/lista de Huffman. */
struct no_arv {
    unsigned char caractere;
    int frequencia;
    int profundidade;
    char codigo[TAM_MAX];
    struct no_arv *ant;
    struct no_arv *prox;
    struct no_arv *esq;
    struct no_arv *dir;
};

typedef struct no_arv no_arv;

#endif
