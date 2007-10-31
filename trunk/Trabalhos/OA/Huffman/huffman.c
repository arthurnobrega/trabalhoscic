#include <stdio.h>
#include <stdlib.h>

#define NOME_ARQ "arquivo.txt"

/** Estrutura. */
typedef struct {
    char caractere;
    int frequencia;
    struct no_arv *esq;
    struct no_arv *dir;
} no_arv;

no_arv *ordenarLista(no_arv *no, int tamanho);
no_arv *construirVetor(FILE *arq, int *tamanho);
void mostrarLista(no_arv *no, int tamanho);

int main(){
    FILE *arq;
    no_arv *vetor;
    int tamanho = 0;

    no = construirLista(arq, &tamanho);
    mostrarLista(vetor, tamanho);

    return 0;
}

no_arv *construirVetor(FILE *arq, int *tamanho) {
    int achou = 0, i = 0;
    char ch;
    no_arv *no, *pont;

    /* Abre o arquivo. */
    arq = fopen(NOME_ARQ, "r");

    *tamanho = 1;
    no = (no_arv *) calloc(1, sizeof(no_arv));
    pont = no;
    ch = fgetc(arq);
    pont->caractere = ch;
    pont->frequencia = 1;
    pont->esq = NULL;
    pont->dir = NULL;
    while ((ch = fgetc(arq)) != EOF) {
	for (i = 0; i <= *tamanho - 1; i++) {
	    pont = &no[i];
	    if (pont->caractere == ch) {
		pont->frequencia += 1;
		achou = 1;
		break;
	    }
	}
	if (achou == 0) {
	    *tamanho += 1;
	    no = (no_arv *) realloc(no, *tamanho * sizeof(no_arv));
	    pont = &no[*tamanho - 1];
	    pont->caractere = ch;
	    pont->frequencia = 1;
	    pont->esq = NULL;
	    pont->dir = NULL;
	} else {
	    achou = 0;
	}

    }

    return qsort(no, *tamanho, sizeof(no_arv), compararNos);
}

int compararNos(const no_arv* a, const no_arv* b) {
    return a->frequencia - b->frequencia;
}

no_arv *ordenarLista(no_arv *no, int tamanho) {
    int i = 0, j = 0;
    no_arv temp, *pont1, *pont2;

    for (i = 0; i <= tamanho - 1; i++) {
	for (j = 0; j <= tamanho - 2; j++) {
	    pont1 = &no[j];
	    pont2 = &no[j + 1];
	    if (pont1->frequencia > pont2->frequencia) {
		temp.caractere = pont1->caractere;
		temp.frequencia = pont1->frequencia;
		pont1->caractere = pont2->caractere;
		pont1->frequencia = pont2->frequencia;
		pont2->caractere = temp.caractere;
		pont2->frequencia = temp.frequencia;
	    }
	}
    }

    return no;
}

void mostrarVetor(no_arv *vetor, int tamanho) {
    int i = 0;
    printf("---Tabela de Frequências---\n");
    for (i = 0; i <= tamanho - 1; i++) {
	printf("%c : %d \n",vetor[i].caractere, vetor[i].frequencia);
    }
    printf("---------------------------\n");
}

void construirArvore(no_arv *vetor, int tamanho) {
    no_arv *pont;
    int i = 0;

    while () {
	pont = vetor[i];
	while () {
	    
	}
	i++;
    }

}
