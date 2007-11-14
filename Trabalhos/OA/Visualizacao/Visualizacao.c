#include "Visualizacao.h"
#include <stdio.h>
#include <string.h>
#include "../Controle/Controle.h"

void mostrarTabela(no_arv *arv, int tamanho);
void mostrarCodigos(no_arv *arv);

void mostrarMenu() {
    char comando[TAM_MAX] = "";
    printf("INSTRUÇÕES AQUI\n\n");
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
	    printf("Arquivo compactado salvo com sucesso!\n");
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
    if (arv != NULL) {
	if (arv->caractere != CAR_ESP) {
	    int profundidade, i;
	    printf("%d ",arv->caractere);
	    profundidade = arv->profundidade;
	    for (i = 0; i <= profundidade - 1; i ++) {
		putc(arv->codigo[i], stdout);
	    }
	    putc('\n', stdout);
	}
	mostrarCodigos(arv->esq);
	mostrarCodigos(arv->dir);
    }
}
