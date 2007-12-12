/** Programa de Compactação e Descompactação utilizando Huffman e Lempel-Ziv.

Autores do programa:
Arthur Thiago Barbosa Nobrega - 06/31205
Davi Fantino da Silva - 06/40832

Versão 1.0
Data: 11/12/2007
Compilador: gcc 4.1.2 20061115 (prerelease) (Debian 4.1.1-21)

Descrição: Este programa tem por objetivo dispor ao usuário compactar e descompactar arquivos utilizando Huffman e Lempel-Ziv. O usuário também tem a opção de simplesmente mostrar a tabela de Huffman do arquivo fornecido ou o dicionário de Lempel-Ziv, além de poder comparar qual o melhor algorítmo para compactar aquele determinado arquivo.
*/

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
    printf("Digite o comando seguido dos argumentos:\n\n");

    while (strcmp(comando, "SAIR")) {
	printf("> ");
	scanf("%s",comando);

	if (!strcmp(comando, "TAB_HUFF")) {
	    no_arv *arv;
	    int tamanho = 0;

	    scanf("%s", comando);
	    arv = c_gerarArvoreHuffman(comando, &tamanho);
	    mostrarTabelaHuffman(arv, tamanho);
	    // Limpa a memória.
	    free(arv);
	} else if (!strcmp(comando, "HUFF")) {
	    char arqEntrada[TAM_MAX], arqSaida[TAM_MAX];
	    no_arv *arv;
	    int tamanho = 0;

	    scanf("%s", arqEntrada);
	    scanf("%s", arqSaida);
	    c_compactarHuffman(arqEntrada, arqSaida, arv, &tamanho);
	} else if (!strcmp(comando, "DIC_LZ")) {
	    char arqEntrada[TAM_MAX];
	    scanf("%s", arqEntrada);
	    tab* tabelaLZ = NULL;

	    tabelaLZ = c_criarTabelaLempelZiv(arqEntrada);
	    if (tabelaLZ != NULL) {
	       mostrarTabelaLempelZiv(tabelaLZ);
	    }
	    // Limpa a memória.
	    free(tabelaLZ);
	} else if (!strcmp(comando, "LZ")) {
	    char arqEntrada[TAM_MAX], arqSaida[TAM_MAX];
	    tab* tabelaLZ = NULL;

	    scanf("%s", arqEntrada);
	    scanf("%s", arqSaida);
	    tabelaLZ = c_criarTabelaLempelZiv(arqEntrada);
	    if (tabelaLZ != NULL) {
	       c_compactarLempelZiv(tabelaLZ, arqSaida);
	    }
	    // Limpa a memória.
	    free(tabelaLZ);
	} else if (!strcmp(comando, "DESC")) {
	    char arqEntrada[TAM_MAX], arqSaida[TAM_MAX];

	    scanf("%s", arqEntrada);
	    scanf("%s", arqSaida);
	    c_descomprimirArquivo(arqEntrada, arqSaida);
	} else if (!strcmp(comando, "RELAT")) {
	    char arqEntrada[TAM_MAX];
	    int *nroBits;

	    scanf("%s", arqEntrada);
	    nroBits = c_gerarRelatorio(arqEntrada);
	    mostrarRelatorio(nroBits, arqEntrada);
	    // Limpa a memória.
	    free(nroBits);
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
    printf("\n--------Dicionário de Lempel-Ziv--------\n");
    printf("   Índice       Anterior        Letra\n");
    printf("      0            -              -\n");
    while (paux->prox != NULL) {
	printf("%7d",paux->indice);
	printf("%13d",paux->indiceAnterior);
	printf("%15d\n",paux->letraRaiz);
	paux = paux->prox;
    }
    conv = paux->letraRaiz;
    if (conv != EOF) {
	printf("%7d",paux->indice);
	printf("%13d",paux->indiceAnterior);
	printf("%15d\n",paux->letraRaiz);
    }
    printf("----------------------------------------\n\n");
}

/* Mostra o relatório na tela. */
void mostrarRelatorio(int *nroBits, char *narq) {
    float contaHuff, contaLZ;

    printf("\n------------Relatório-------------\n");
    printf("Nome do Arquivo:        ");
    puts(narq);
    printf("\n");
    printf("Tamanho Original:       ");
    printf("%d bits\n", nroBits[0]);
    printf("Compactando com:\n");
    printf("- Huffman\n");
    printf("   Tamanho:             ");
    printf("%d bits\n", nroBits[1]);
    printf("   Taxa de Compressao:  ");
    contaHuff = (double) (100 * (1 - ((double)nroBits[1]/(double)nroBits[0])));
    printf("%0.1f \%\n", contaHuff);
    printf("- Lempel-Ziv\n");
    printf("   Tamanho:             ");
    printf("%d bits\n", nroBits[2]);
    printf("   Taxa de Compressao:  ");
    contaLZ = (double) (100 * (1 - ((double)nroBits[2]/(double)nroBits[0])));
    printf("%0.1f \%\n\n", contaLZ);
    printf("Melhor Algorítmo:       ");
    (contaHuff > contaLZ) ? printf("Huffman\n") : printf("Lempel-Ziv\n");
    printf("----------------------------------\n\n");
}

/* Mostra a tabela de Huffman na tela. */
void mostrarTabelaHuffman(no_arv *arv, int tamanho) {
    printf("\n--------Tabela de Códigos de Huffman---------\n");
    printf("%5d\n", tamanho);
    mostrarCodigosHuffman(arv);
    printf("--------------------------------------------\n\n");
}

/* Mostra os caracteres e seus respectivos códigos da tabela de Huffman. */
void mostrarCodigosHuffman(no_arv *arv) {
    if (arv->esq == NULL) {
	int profundidade, i;
	printf("%5d ",arv->caractere);
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
