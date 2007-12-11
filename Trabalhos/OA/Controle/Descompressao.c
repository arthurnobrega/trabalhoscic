#include "Descompressao.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Huffman.h"

no_arv *lerTabelaHuffman(FILE *arqEntrada);
void reconstruirArvoreHuffman(no_arv *arv, char caractere, char *codigo, int profundidade);
void escreverArquivoTexto(FILE *arqEntrada, FILE *arqSaida, no_arv *arv);
tab* remontarTabelaLempelZiv(FILE *arq);

/** Função para descomprimir arquivos compactados com Huffman ou Lempel-Ziv. */
void descomprimir(FILE *arqEntrada, FILE *arqSaida) {
    char ch;
    no_arv *arv;

    ch = fgetc(arqEntrada);
    if (ch == 'H') {
	ch = fgetc(arqEntrada);
	arv = lerTabelaHuffman(arqEntrada);
	escreverArquivoTexto(arqEntrada, arqSaida, arv);
    } else if (ch == 'L') {
	ch = fgetc(arqEntrada);
	remontarTabelaLempelZiv(arqEntrada);
    }
    fclose(arqEntrada);
    fclose(arqSaida);
}

/* Esta função lê a tabela(cabeçalho) do arquivo compactado com o algoritmo de Huffman e já vai reconstruindo a árvore a cada caractere e código encontrado. */
no_arv *lerTabelaHuffman(FILE *arqEntrada) {
    char ch, caractere, codigo[TAM_MAX], nroLinhas;
    int i, tamanho;
    no_arv *arv;

    arv = calloc(1, sizeof(no_arv));
    nroLinhas = fgetc(arqEntrada);
    caractere = fgetc(arqEntrada);
    for (i = 0; i <= nroLinhas - 1; i++) {
	caractere = fgetc(arqEntrada);
	tamanho = 0;
	while((ch = fgetc(arqEntrada)) != '\n') {
	    tamanho++;
	    codigo[tamanho - 1] = ch;
	}
	reconstruirArvoreHuffman(arv, caractere, codigo, tamanho);
    }

    return arv;
}

/* Função que reconstroi a árvore de Huffman apenas com os nós que realmente contêm caracteres, os outros não são preenchidos. */
void reconstruirArvoreHuffman(no_arv *arv, char caractere, char *codigo, int profundidade) {
    no_arv *paux, *pnovo;
    int i;

    paux = arv;
    for (i = 0; i <= profundidade - 1; i++) {
	if (codigo[i] == '0') {
	    if (paux->esq == NULL) {
	       pnovo = calloc(1, sizeof(no_arv));
	       pnovo->esq = NULL;
	       pnovo->dir = NULL;
	       paux->esq = pnovo;
	    }
	    paux = paux->esq;
	} else {
	    if (paux->dir == NULL) {
		pnovo = calloc(1, sizeof(no_arv));
		pnovo->esq = NULL;
		pnovo->dir = NULL;
		paux->dir = pnovo;
	    }
	    paux = paux->dir;
	}
    }
    strcpy(paux->codigo,codigo);
    paux->profundidade = profundidade;
    paux->caractere = caractere;
}

/* Função que escreve o arquivo texto com o texto originalmente compactado. */
void escreverArquivoTexto(FILE *arqEntrada, FILE *arqSaida, no_arv *arv) {
    char ch[3], vetorCod[TAM_MAX];
    unsigned char caux;
    int tamanho = 0, i, nroBits, sair = 1;
    no_arv *no;

    nroBits = 8;
    ch[0] = fgetc(arqEntrada);
    ch[1] = fgetc(arqEntrada);
    ch[2] = fgetc(arqEntrada);
    while (sair) {
	if (feof(arqEntrada)) {
	    nroBits = ch[1] + 1;
	    sair = 0;
	}
	caux = 128;
	for (i = 0; i <= nroBits - 1; i++) {
	    if (caux & ch[0]) {
		vetorCod[tamanho] = '1';
	    } else {
		vetorCod[tamanho] = '0';
	    }
	    tamanho++;
	    caux >>= 1;
	    no = buscarNoCodigo(arv, vetorCod, tamanho);
	    if (no != NULL) {
		tamanho = 0;
		fwrite(&no->caractere, 1, 1, arqSaida);
		no = NULL;
	    }
	}
	ch[0] = ch[1];
	ch[1] = ch[2];
	ch[2] = fgetc(arqEntrada);
    }
}

tab* remontarTabelaLempelZiv(FILE *arq) {
    tab* pinicioTabela = calloc(1,sizeof(tab));
    tab* p1;
    int numeroDeBitsTotal = 0;
    int i;
    int bitsIndice = 0;
    unsigned char bitsLetra = 0;
    char bitsAux = 0;
    int bitsInversao1 = 0;
    char bitsInversao = 0;
    char ultimosBits = 0;
    int numeroDeBitsNoFinal = 0;
    int contadorBits = 1;
    int indice = 1; 
    int marcadorBits = 1; 
    int cont = 0; 
    int comparador = 1;
    int termino = 0;

    fread(&numeroDeBitsTotal, sizeof(int), 1, arq);
    printf("numero total: %d\n", numeroDeBitsTotal);
    getc(arq);

    pinicioTabela->ant = NULL;
    pinicioTabela->prox = NULL;
    pinicioTabela->indiceAnterior = 0;
    pinicioTabela->indice = indice;

    fread(&pinicioTabela->letraRaiz, sizeof(char), 1, arq);
    printf("pinicio: %c\n",pinicioTabela->letraRaiz );
    numeroDeBitsTotal = numeroDeBitsTotal - 8;
    p1 = pinicioTabela;

    fread(&bitsAux, sizeof(char), 1, arq);
    numeroDeBitsTotal = numeroDeBitsTotal - 8;

    comparador <<= 7;

    while (numeroDeBitsTotal > 0) {
	bitsIndice = 0;
	bitsLetra = 0;
        for (i = 0; i < contadorBits; i++) {
	    bitsIndice <<= 1;
            if ((comparador & bitsAux) != 0) {
                bitsIndice |= 1; 
            }
            comparador = comparador / 2;
            cont = cont + 1;
            if(cont == 8){
                fread(&bitsAux, sizeof(char), 1, arq);
                numeroDeBitsTotal = numeroDeBitsTotal - 8;
                cont = 0;
                comparador = 128;
            }
        }

        bitsInversao1 = 0;
	for(i = 0; i < contadorBits; i++){
	    bitsInversao1 <<= 1;
	   if ((bitsIndice & 1) != 0) {
	       bitsInversao1 |= 1;
	   }
	   bitsIndice >>= 1;
	}
	bitsIndice = bitsInversao1;

        if (termino == 0){
            for(i = 0; i < 8; i++){
                bitsLetra <<= 1;
                if ((comparador & bitsAux) != 0) {
                    bitsLetra |= 1; 
                }
                comparador = comparador / 2;
                cont = cont + 1;
                if(cont == 8){
                    fread(&bitsAux, sizeof(char), 1, arq);
                    numeroDeBitsTotal = numeroDeBitsTotal - 8;
                    cont = 0;
                    comparador = 128;
                }
            }

            bitsInversao = 0;
            for(i = 0; i < 8; i++){
                bitsInversao <<= 1;
                if ((bitsLetra & 1) != 0) {
                    bitsInversao |= 1;
                }
                bitsLetra >>= 1;
            }
            bitsLetra = bitsInversao;
        }
        indice = indice + 1;
        p1->prox = (tab*)calloc(1, sizeof(tab));
        p1->prox->ant = p1;
        p1 = p1->prox;
        p1->prox = NULL;
        p1->indice = indice;
        p1->indiceAnterior = bitsIndice;
        p1->letraRaiz = bitsLetra;
	
        if (numeroDeBitsTotal < 8){
            termino = 1;
        }

        if((indice + 1) > 2*marcadorBits){
            contadorBits = contadorBits + 1;
            marcadorBits = marcadorBits*2;
        }
    }

    fclose(arq);
    p1 = pinicioTabela;
    while (p1 != NULL) {
	printf("%d ", p1->indice);
	printf("%d ", p1->indiceAnterior);
	printf("%c\n", p1->letraRaiz);
	p1 = p1->prox;
    }
    return pinicioTabela;
}
