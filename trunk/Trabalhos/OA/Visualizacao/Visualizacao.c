#include "Visualizacao.h"
#include <stdio.h>
#include <string.h>
#include "../Controle/Controle.h"

void mostrarTabela(no_arv *arv, int tamanho);
void mostrarCodigos(no_arv *arv);

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
	    arv = gerarArvoreHuffman(comando, &tamanho);
	    mostrarTabela(arv, tamanho);
	} else if (!strcmp(comando, "HUFF")) {
	    char arqEntrada[TAM_MAX], arqSaida[TAM_MAX];
	    no_arv *arv;
	    int tamanho = 0;

	    scanf("%s", arqEntrada);
	    scanf("%s", arqSaida);
	    gerarArquivoHuffman(arqEntrada, arqSaida, arv, &tamanho);
	    printf("Arquivo compactado e salvo com sucesso!\n");
	} else if (!strcmp(comando, "DIC_LZ")) {
	    
	} else if (!strcmp(comando, "LZ")) {
	    
	} else if (!strcmp(comando, "DESC")) {
	    
	} else if (!strcmp(comando, "RELAT")) {
	    
	} else if (strcmp(comando, "SAIR")){
	    printf("Comando \"%s\" não encontrado.\n", comando);
	}
    }
}

void mostrarTabela(no_arv *arv, int tamanho) {
    printf("--------Tabela de Códigos---------\n");
    printf("%d\n", tamanho);
    mostrarCodigos(arv);
    printf("----------------------------------\n");
}

void mostrarCodigos(no_arv *arv) {
    if (arv->esq == NULL) {
	int profundidade, i;
	printf("%d ",arv->caractere);
	profundidade = arv->profundidade;
	for (i = 0; i <= profundidade - 1; i++) {
	    putc(arv->codigo[i], stdout);
	}
	putc('\n', stdout);
    } else {
	mostrarCodigos(arv->esq);
	mostrarCodigos(arv->dir);
    }
}
