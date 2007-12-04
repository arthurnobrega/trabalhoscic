#include "Visualizacao.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Controle/Controle.h"
#include "../Tipos.h"

void mostrarTabelaHuffman(no_arv *arv, int tamanho);
void mostrarCodigosHuffman(no_arv *arv);
void mostrarTabelaLempelZiv(tab *pinicio);

/** Mostra o menu ao usuário. */
void mostrarMenu() {
    char comando[TAM_MAX] = "";
    printf("\n-> Lista de Comandos:\n");
    printf("    - TAB_HUFF arg\n");
    printf("    - HUFF arg1 arg2\n");
    printf("    - DIC_LZ arg\n");
    printf("    - LZ arg1 arg2\n");
    printf("    - DESC arg1 arg2\n");
    printf("    - RELAT arg \n");
    printf("    - SAIR\n\n");
    printf("Para obter ajuda sobre os comandos digite COMANDO --help\n\n");

    while (strcmp(comando, "SAIR")) {
	printf("> ");
	//lê toda a linha: scanf("%[^\n]",comando);
	scanf("%s",comando);

	if (!strcmp(comando, "TAB_HUFF")) {
	    no_arv *arv;
	    int tamanho = 0;

	    scanf("%s", comando);
	    // Testar se o arquivo existe
	    arv = c_gerarArvoreHuffman(comando, &tamanho);
	    mostrarTabelaHuffman(arv, tamanho);
	} else if (!strcmp(comando, "HUFF")) {
	    char arqEntrada[TAM_MAX], arqSaida[TAM_MAX];
	    no_arv *arv;
	    int tamanho = 0;

	    scanf("%s", arqEntrada);
	    scanf("%s", arqSaida);
	    c_compactarHuffman(arqEntrada, arqSaida, arv, &tamanho);
	    printf("Arquivo compactado e salvo com sucesso!\n");
	} else if (!strcmp(comando, "DIC_LZ")) {
            tab *pinicio = NULL;
	    char arqEntrada[TAM_MAX];

	    scanf("%s", arqEntrada);
	    pinicio = c_gerarTabelaLZ(arqEntrada);
	    mostrarTabelaLempelZiv(pinicio);
            free(pinicio);
	} else if (!strcmp(comando, "LZ")) {
	    
	} else if (!strcmp(comando, "DESC")) {
	    char arqEntrada[TAM_MAX], arqSaida[TAM_MAX];

	    scanf("%s", arqEntrada);
	    scanf("%s", arqSaida);
	    c_descomprimirArquivo(arqEntrada, arqSaida);
	    printf("Arquivo descompactado com sucesso!\n");
	} else if (!strcmp(comando, "RELAT")) {
	    
	} else if (strcmp(comando, "SAIR")){
	    printf("Comando \"%s\" não encontrado.\n", comando);
	}
    }
}

/* Mostra a tabela de Huffman na tela. */
void mostrarTabelaHuffman(no_arv *arv, int tamanho) {
    printf("--------Tabela de Códigos---------\n");
    printf("%d\n", tamanho);
    mostrarCodigosHuffman(arv);
    printf("----------------------------------\n");
}

/* Mostra os caracteres e seus respectivos códigos da tabela de Huffman. */
void mostrarCodigosHuffman(no_arv *arv) {
    if (arv->esq == NULL) {
	int profundidade, i;
	printf("%d ",arv->caractere);
	profundidade = arv->profundidade;
	for (i = 0; i <= profundidade - 1; i++) {
	    putc(arv->codigo[i], stdout);
	}
	putc('\n', stdout);
    } else {
	mostrarCodigosHuffman(arv->esq);
	mostrarCodigosHuffman(arv->dir);
    }
}

void mostrarTabelaLempelZiv(tab *pinicio) {
    tab *p1 = pinicio;

    printf("---INDICES ANTERIOR CODIGO(TABELA ASCII)---");
    while(p1->prox != NULL) {
	printf("%-8d\n",p1->indice);
	printf("%-9d\n",p1->indiceAnterior);
	printf("%-20d\n",(int)p1->letraRaiz);
    }
    printf("----------------------------------\n");
}
