#ifndef TIPOS_H
#define TIPOS_H
#define TAM_MAX 256
#define CAR_MARC -1

typedef struct no_arv no_arv;
typedef struct registro *reg;
typedef struct tabela *tab;


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


struct registro{
    char letraRaiz;
    reg *filhas;
    reg *prox;
    int indice;
};

struct tabela{
    tab *prox;
    int indice;
    char letraRaiz;
    int indiceAnterior;
};
#endif
