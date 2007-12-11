#include "Visualizacao.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Controle/Controle.h"
#include "../Tipos.h"

void mostrarTabelaLempelZiv(tab *tabelaLempelZiv);
void mostrarTabelaHuffman(no_arv *arv, int tamanho);
void mostrarCodigosHuffman(no_arv *arv);
void mostrarRelatorio(int *nroBits, char *narq);

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
	    char arqEntrada[TAM_MAX];
	    scanf("%s", arqEntrada);
	    tab* tabelaLZ = NULL;

	    tabelaLZ = c_criarTabelaLempelZiv(arqEntrada);
	    mostrarTabelaLempelZiv(tabelaLZ);
	    // Limpa a memória.
	    free(tabelaLZ);
	} else if (!strcmp(comando, "LZ")) {
	    char arqEntrada[TAM_MAX], arqSaida[TAM_MAX];
	    tab* tabelaLZ = NULL;
	    
	    scanf("%s", arqEntrada);
	    scanf("%s", arqSaida);
	    tabelaLZ = c_criarTabelaLempelZiv(arqEntrada);
	    c_compactarLempelZiv(tabelaLZ, arqSaida);
	    // Limpa a memória.
	    free(tabelaLZ);
	} else if (!strcmp(comando, "DESC")) {
	    char arqEntrada[TAM_MAX], arqSaida[TAM_MAX];

	    scanf("%s", arqEntrada);
	    scanf("%s", arqSaida);
	    c_descomprimirArquivo(arqEntrada, arqSaida);
	    printf("Arquivo descompactado com sucesso!\n");
	} else if (!strcmp(comando, "RELAT")) {
	    char arqEntrada[TAM_MAX];
	    int *nroBits;

	    scanf("%s", arqEntrada);
	    nroBits = c_gerarRelatorio(arqEntrada);
	    mostrarRelatorio(nroBits, arqEntrada);
	} else if (strcmp(comando, "SAIR")){
	    printf("Comando \"%s\" não encontrado.\n", comando);
	}
    }
}

/* Mostra a tabela de Lempel Ziv na tela. */
void mostrarTabelaLempelZiv(tab *tabelaLempelZiv) {
    tab *paux = NULL;
    int conv = 0;

    paux = tabelaLempelZiv;
    printf("INDICE       ANTERIOR        LETRA\n");
    printf("   0            -              -\n");
    while (paux->prox != NULL) {
	printf("%4d",paux->indice);
	printf("%13d",paux->indiceAnterior);
	printf("%15d\n",paux->letraRaiz);
	paux = paux->prox;
    }
    conv = paux->letraRaiz;
    if (conv != 255) {
	printf("%4d",paux->indice);
	printf("%13d",paux->indiceAnterior);
	printf("%15d\n",paux->letraRaiz);
    }
}

void mostrarRelatorio(int *nroBits, char *narq) {
    double conta;

    printf("--------------------------------\n");
    printf("Nome do Arquivo:      ");
    puts(narq);
    printf("\n");
    printf("Tamanho Original:     ");
    printf("%d bits\n", nroBits[0]);
    printf("Tamanho HUFF:         ");
    printf("%d bits\n", nroBits[1]);
    printf("COMP HUFF:            ");
    conta = (double) (100 * (1 - ((double)nroBits[1]/(double)nroBits[0])));
    printf("%0.1f \%\n", conta);
    printf("Tamanho LZ:           ");
    printf("%d bits\n", nroBits[2]);
    printf("COMP LZ:              ");
    conta = (double) (100 * (1 - ((double)nroBits[2]/(double)nroBits[0])));
    printf("%0.1f \%\n", conta);
    printf("--------------------------------\n");
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
