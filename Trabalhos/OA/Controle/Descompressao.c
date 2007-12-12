/** Programa de Compactação e Descompactação utilizando Huffman e Lempel-Ziv.

Autores do programa:
Arthur Thiago Barbosa Nobrega - 06/31205
Davi Fantino da Silva - 06/40832

Versão 1.0
Data: 11/12/2007
Compilador: gcc 4.1.2 20061115 (prerelease) (Debian 4.1.1-21)

Descrição: Este programa tem por objetivo dispor ao usuário compactar e descompactar arquivos utilizando Huffman e Lempel-Ziv. O usuário também tem a opção de simplesmente mostrar a tabela de Huffman do arquivo fornecido ou o dicionário de Lempel-Ziv, além de poder comparar qual o melhor algorítmo para compactar aquele determinado arquivo.
*/

#include "Descompressao.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Huffman.h"

no_arv *lerTabelaHuffman(FILE *arqEntrada);
void reconstruirArvoreHuffman(no_arv *arv, char caractere, char *codigo, int profundidade);
void escreverArquivoTexto(FILE *arqEntrada, FILE *arqSaida, no_arv *arv);
tab* remontarTabelaLempelZiv(FILE *arq);
void escreverArquivoLZ(tab *pinicioTabela, FILE *arq);

/** Função para descomprimir arquivos compactados com Huffman ou Lempel-Ziv. */
void descomprimir(FILE *arqEntrada, FILE *arqSaida) {
    char ch;
    no_arv *arv;
    tab *pinicio;

    ch = fgetc(arqEntrada);
    if (ch == 'H') {
	ch = fgetc(arqEntrada);
	arv = lerTabelaHuffman(arqEntrada);
	escreverArquivoTexto(arqEntrada, arqSaida, arv);
    } else if (ch == 'L') {
	ch = fgetc(arqEntrada);
	pinicio = remontarTabelaLempelZiv(arqEntrada);
	escreverArquivoLZ(pinicio, arqSaida);
    }
}

/** Esta função lê a tabela(cabeçalho) do arquivo compactado com o algoritmo de Huffman e já vai recons
truindo a árvore a cada caractere e código encontrado. */
/** Constroi a lista de caracteres com as respectivas frequências. 
 * arq: arquivo texto de entrada, onde está o texto original.
 * tamanho: ponteiro para um inteiro onde será armazenado o número de caracteres no texto.
*/
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
   
/** Constroi a lista de caracteres com as respectivas frequências. 
     * arq: arquivo texto de entrada, onde está o texto original.
     * tamanho: ponteiro para um inteiro onde será armazenado o número de caracteres no texto.
 */
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

/** Função que escreve o arquivo texto com o texto originalmente compactado. */
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
	
/** Constroi a lista de caracteres com as respectivas frequências. 
	     * arq: arquivo texto de entrada, onde está o texto original.
	     * tamanho: ponteiro para um inteiro onde será armazenado o número de caracteres no texto.
 */
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
/** Constroi a lista de caracteres com as respectivas frequências. 
	 * arq: arquivo texto de entrada, onde está o texto original.
	 * tamanho: ponteiro para um inteiro onde será armazenado o número de caracteres no texto.
 */

	ch[0] = ch[1];
	ch[1] = ch[2];
	ch[2] = fgetc(arqEntrada);
    }
}

/** Constroi a lista de caracteres com as respectivas frequências. 
 * arq: arquivo texto de entrada, onde está o texto original.
 * tamanho: ponteiro para um inteiro onde será armazenado o número de caracteres no texto.
 */

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
    int termino = 0, termino2 = 0;

    fread(&numeroDeBitsTotal, sizeof(int), 1, arq);
    getc(arq);

    pinicioTabela->ant = NULL;
    pinicioTabela->prox = NULL;
    pinicioTabela->indiceAnterior = 0;
    pinicioTabela->indice = indice;

    fread(&pinicioTabela->letraRaiz, sizeof(char), 1, arq);
    numeroDeBitsTotal = numeroDeBitsTotal - 8;
    p1 = pinicioTabela;

    fread(&bitsAux, sizeof(char), 1, arq);
    numeroDeBitsTotal = numeroDeBitsTotal - 8;

    comparador <<= 7;

    while ((numeroDeBitsTotal > 0) && (!feof(arq))) {
	bitsIndice = 0;
	bitsLetra = 0;
	if(termino2 == 0){
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
	}
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
	
	if(termino == 0){
	    if (numeroDeBitsTotal < 8){
		fread(&ultimosBits, sizeof(char), 1, arq); 
		numeroDeBitsNoFinal = (int) ultimosBits;
		numeroDeBitsTotal = (numeroDeBitsTotal + 8) - cont;
		if (numeroDeBitsNoFinal == cont){
		    termino2 = 1;
		    termino = 1;
		}else{
		    termino = 1;
		}
	    }
	} else {
	    if(numeroDeBitsNoFinal != 0){
 	       p1->letraRaiz = EOF;
	    }
	   break;
	}
        if((indice + 1) > 2*marcadorBits){
            contadorBits = contadorBits + 1;
            marcadorBits = marcadorBits*2;
        }
    }
    return pinicioTabela;
}

void escreverArquivoLZ(tab *pinicioTabela, FILE *arq) {
    tab *p1 = NULL, *p2 = NULL;
    int indiceAnterior = 0;
    int terminou = 0, cont = 0, i = 0;
    char *str = NULL;
    p1 = pinicioTabela;
    p2 = p1;
    while (p1 != NULL) {
	cont++;
	str = (char *) realloc(str, cont * sizeof(char));
	str[cont - 1] = p1->letraRaiz;
	indiceAnterior = p1->indiceAnterior;
	if (indiceAnterior != 0) {
	    while ((p2->ant != NULL) && (terminou == 0)) {
		p2 = p2->ant;
		if (p2->indice == indiceAnterior) {
		    cont++;
		    str = (char *) realloc(str, cont * sizeof(char));
		    str[cont - 1] = p2->letraRaiz;
		    indiceAnterior = p2->indiceAnterior;
		    if (indiceAnterior == 0) {
			terminou = 1;
		    }
		}
	    }
	    terminou = 0;
	}
	for (i = cont - 1; i >= 0; i--) {
		fputc(str[i], arq);
	}
	cont = 0;
	str = (char *) realloc (str, cont * 0 );
	p1 = p1->prox;
	p2 = p1;
    }
    
}
