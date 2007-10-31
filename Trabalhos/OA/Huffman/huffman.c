#include <stdio.h>
#include <stdlib.h>

#define NOME_ARQ "arquivo.txt"

/** Estrutura. */
typedef struct {
    char caractere;
    int frequencia;
} lista_t;

lista_t *ordenarLista(lista_t *lista, int tamanho);
lista_t *construirLista(FILE *arq, int *tamanho);
void mostrarLista(lista_t *lista, int tamanho);

int main(){
    FILE *arq;
    lista_t *lista;
    int tamanho = 0;

    lista = construirLista(arq, &tamanho);
    mostrarLista(lista, tamanho);

    return 0;
}

lista_t *construirLista(FILE *arq, int *tamanho) {
    int achou = 0, i = 0;
    char ch;
    lista_t *lista, *pont;

    /* Abre o arquivo. */
    arq = fopen(NOME_ARQ, "r");

    *tamanho = 1;
    lista = (lista_t *) calloc(1, sizeof(lista_t));
    pont = lista;
    ch = fgetc(arq);
    pont->caractere = ch;
    pont->frequencia = 1;
    while ((ch = fgetc(arq)) != EOF) {
	for (i = 0; i <= *tamanho - 1; i++) {
	    pont = &lista[i];
	    if (pont->caractere == ch) {
		pont->frequencia += 1;
		achou = 1;
		break;
	    }
	}
	if (achou == 0) {
	    *tamanho += 1;
	    lista = (lista_t *) realloc(lista, *tamanho * sizeof(lista_t));
	    pont = &lista[*tamanho - 1];
	    pont->caractere = ch;
	    pont->frequencia = 1;
	} else {
	    achou = 0;
	}

    }

    lista = ordenarLista(lista, *tamanho);

    return lista;
}

lista_t *ordenarLista(lista_t *lista, int tamanho) {
    int i = 0, j = 0;
    lista_t temp, *pont1, *pont2;

    for (i = 0; i <= tamanho - 1; i++) {
	for (j = 0; j <= tamanho - 2; j++) {
	    pont1 = &lista[j];
	    pont2 = &lista[j + 1];
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
    
    return lista;
}

void mostrarLista(lista_t *lista, int tamanho) {
    int i = 0;
    for (i = 0; i <= tamanho - 1; i++) {
	printf("%c : %d \n",lista[i].caractere, lista[i].frequencia);
    }
}
