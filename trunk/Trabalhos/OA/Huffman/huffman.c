#include <stdio.h>
#include <stdlib.h>

#define NOME_ARQ "arquivo.txt"

/** Estrutura. */
struct no_arv{
    char caractere;
    int frequencia;
    struct no_arv *esq;
    struct no_arv *dir;
};

typedef struct no_arv no_arv;

no_arv *construirVetor(FILE *arq, int *tamanho);
int compararNos(const no_arv* a, const no_arv* b);
void mostrarVetor(no_arv *vetor, int tamanho);
no_arv *construirArvore(no_arv *vetor, int tamanho);
void mostrarArvore(no_arv *raiz);

int main(){
    FILE *arq;
    no_arv *vetorArvore;
    int tamanho = 0;

    vetorArvore = construirVetor(arq, &tamanho);
    mostrarVetor(vetorArvore, tamanho);
    vetorArvore = construirArvore(vetorArvore, tamanho);
    mostrarArvore(vetorArvore);

    return 0;
}

no_arv *construirVetor(FILE *arq, int *tamanho) {
    int achou = 0, i = 0;
    char ch;
    no_arv *vetor, *pont;

    /* Abre o arquivo. */
    arq = fopen(NOME_ARQ, "r");

    *tamanho = 1;
    vetor = (no_arv *) calloc(1, sizeof(no_arv));
    pont = vetor;
    ch = fgetc(arq);
    pont->caractere = ch;
    pont->frequencia = 1;
    pont->esq = NULL;
    pont->dir = NULL;
    while ((ch = fgetc(arq)) != EOF) {
	for (i = 0; i <= *tamanho - 1; i++) {
	    pont = &vetor[i];
	    if (pont->caractere == ch) {
		pont->frequencia += 1;
		achou = 1;
		break;
	    }
	}
	if (achou == 0) {
	    *tamanho += 1;
	    vetor = (no_arv *) realloc(vetor, *tamanho * sizeof(no_arv));
	    pont = &vetor[*tamanho - 1];
	    pont->caractere = ch;
	    pont->frequencia = 1;
	    pont->esq = NULL;
	    pont->dir = NULL;
	} else {
	    achou = 0;
	}

    }

    qsort(vetor, (size_t) *tamanho, sizeof(no_arv), (void*) compararNos);
    return vetor;
}

int compararNos(const no_arv* a, const no_arv* b) {
    return a->frequencia - b->frequencia;
}

void mostrarVetor(no_arv *vetor, int tamanho) {
    int i = 0;
    printf("---Tabela de Frequências---\n");
    for (i = 0; i <= tamanho - 1; i++) {
	printf("%c : %d \n",vetor[i].caractere, vetor[i].frequencia);
    }
    printf("---------------------------\n");
}

no_arv *construirArvore(no_arv *vetor, int tamanho) {
    no_arv *pont1, *pont2, *pont3, *pont4;
    int i = 0, tam_aux = tamanho - 1;

    while (tam_aux > 0) {
	i = 0;
	pont1 = &vetor[i];
	while ((pont1->frequencia) < 0) {
	    i++;
	    pont1 = &vetor[i];
	}
	pont2 = &vetor[i + 1];
	pont3 = (no_arv*) calloc (1, sizeof(no_arv));
	pont4 = (no_arv*) calloc (1, sizeof(no_arv));
	
	pont3->caractere = pont1->caractere;
	pont3->frequencia = pont1->frequencia;
	pont3->esq = pont1->esq;
	pont3->dir = pont1->dir;
	
	pont4->caractere = pont2->caractere;
	pont4->frequencia = pont2->frequencia;
	pont4->esq = pont2->esq;
	pont4->dir = pont2->dir;
	
	pont2->esq = pont3;
	pont2->dir = pont4;
	pont2->caractere = '$';
	pont2->frequencia = pont3->frequencia + pont4->frequencia;
	pont1->frequencia = -1;
	qsort(vetor, (size_t) tamanho, sizeof(no_arv), (void*) compararNos);
	tam_aux--;
    }

    return &vetor[tamanho - 1];
}

void mostrarArvore(no_arv *arv) {
    if (arv != NULL)
    {
	printf("%c : %d\n",arv->caractere, arv->frequencia);
	mostrarArvore(arv->esq);
	mostrarArvore(arv->dir);
    } else {
	printf("NULL\n");
    }
}
