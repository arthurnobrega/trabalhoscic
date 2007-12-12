/** Programa de Compactação e Descompactação utilizando Huffman e Lempel-Ziv.

Autores do programa:
Arthur Thiago Barbosa Nobrega - 06/31205
Davi Fantino da Silva - 06/40832

Versão 1.0
Data: 11/12/2007
Compilador: gcc 4.1.2 20061115 (prerelease) (Debian 4.1.1-21)

Descrição: Este programa tem por objetivo dispor ao usuário compactar e descompactar arquivos utilizando Huffman e Lempel-Ziv. O usuário também tem a opção de simplesmente mostrar a tabela de Huffman do arquivo fornecido ou o dicionário de Lempel-Ziv, além de poder comparar qual o melhor algorítmo para compactar aquele determinado arquivo.
*/

#ifndef TIPOS_H
#define TIPOS_H
#define TAM_MAX 256

typedef struct no_arv no_arv;
typedef struct registro reg;
typedef struct tabela tab;

/** Estrutura do nó da árvore/lista de Huffman.
 * Data: 10/12/2007
 * Versão: 3.0
 * Autores:
     Arthur Thiago Barbosa Nobrega - 06/31205
     Davi Fantino da Silva - 06/40832
 */
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

/** Estrutura do nó da árvore de Lempel-Ziv.
 * Data: 10/12/2007
 * Versão: 4.0
 * Autores:
     Arthur Thiago Barbosa Nobrega - 06/31205
     Davi Fantino da Silva - 06/40832
 */
struct registro {
    unsigned char letraRaiz;
    reg *filhas;
    reg *prox;
    int indice;
};

/** Estrutura do nó da lista de Lempel-Ziv.
 * Data: 10/12/2007
 * Versão: 2.0
 * Autores:
     Arthur Thiago Barbosa Nobrega - 06/31205
     Davi Fantino da Silva - 06/40832
 */
struct tabela {
    tab *prox;
    tab *ant;
    int indice;
    unsigned char letraRaiz;
    int indiceAnterior;
};
#endif
