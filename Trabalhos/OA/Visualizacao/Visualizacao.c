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
	scanf("%s",comando);

	if (!strcmp(comando, "TAB_HUFF")) {
	    no_arv *arv;
	    int tamanho = 0;
	    scanf("%s", comando);
	    // Testar se o arquivo existe
	    arv = gerarArvoreHuffman(comando, &tamanho);
	    mostrarTabela(arv, tamanho);
	} else if (!strcmp(comando, "HUFF")) {
	    no_arv *arv;
	    int tamanho = 0;
	    scanf("%s", comando);
	    gerarArquivoHuffman(comando, arv, &tamanho);
	    printf("Arquivo compactado salvo com sucesso!\n");
	} else if (!strcmp(comando, "DIC_LZ")) {
	    
	} else if (!strcmp(comando, "LZ")) {
	    
	} else if (!strcmp(comando, "DESC")) {
	    
	} else if (!strcmp(comando, "RELAT")) {
	    
	} else {
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
    int tamanho = 0,numero = 0, mask = 0;
    if (arv != NULL) {
	if (arv->caractere != CAR_ESP) {
	    tamanho = arv->tam_cod;
	    numero = arv->codigo;
	    mask = 1 << (tamanho - 1);
	    // Mostrar código como binário com o número de casas
	    //que está armazenado no campo profundidade.
	    printf("%d ",arv->caractere );
	    putchar(numero & mask ? '1' : '0');
	    mask = (mask >> 1) & ~(1 << (tamanho - 1));
	    while (mask) {
		putchar(numero & mask ? '1' : '0');
		mask >>= 1;
	    }
	    putchar('\n');
	}
	mostrarCodigos(arv->esq);
	mostrarCodigos(arv->dir);
    }
}
