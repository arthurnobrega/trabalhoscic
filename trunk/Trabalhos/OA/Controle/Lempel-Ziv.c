#include <stdlib.h>
#include <string.h>
#include "../Tipos.h"
#include "Controle.h"
#include "../Persistencia/Arquivos.h"

/*A PARTIR DE UM ARQUIVO TEXTO, ESSA FUNCAO CRIA UMA ARVORE GENERICA,
IRMAOS(PROX) E FILHAS, CADA FILHA REPRESENTADO UM CHAR*/
reg* criarArvore(int* maiorContador, FILE* arq) {

    char caracter = 0;
    reg *pinicio = NULL;
    reg *p1 = NULL;
    int achou = 0;
    int acabouArvore = 0;
    int fimLinha = 0;
    int contadorIndice = *maiorContador;

    while((caracter = getc(arq)) != EOF){
        if(pinicio == NULL){
            pinicio = calloc(1,sizeof(reg));
            pinicio->prox = NULL;
            pinicio->filhas = NULL;
            pinicio->letraRaiz = caracter;
            contadorIndice = (contadorIndice + 1);
            pinicio->indice = contadorIndice;
            p1 = pinicio;
        }else{
            while(acabouArvore == 0){
                while ((achou == 0)&&(fimLinha == 0)){
                    if(p1->letraRaiz == caracter){
                        achou = 1;
                    }else{
                        if((p1->prox) != NULL){
                            p1 = p1->prox;
                        }else{
                            fimLinha = 1;
                        }
                    }
                }
                if (achou == 0){
                    acabouArvore = 1;
                    fimLinha = 0;
                    p1->prox = (reg*)calloc(1,sizeof(reg));
                    p1 = p1->prox;
                    p1->letraRaiz = caracter;
                    contadorIndice = contadorIndice + 1;
                    p1->indice = contadorIndice;
                    p1->prox = NULL;
                    p1->filhas = NULL;
                }else{
                    caracter = getc(arq);
                    if (p1->filhas != NULL){
                        p1 = p1->filhas;
                    }else{
                        acabouArvore = 1;
                        p1->filhas = calloc(1,sizeof(reg));
                        p1 = p1->filhas;
                        p1->letraRaiz = caracter;
                        contadorIndice = contadorIndice + 1;
                        p1->indice = contadorIndice;
                        p1->filhas = NULL;
                        p1->prox = NULL;
                    }
                    achou = 0;
                }
            }
            acabouArvore = 0;
            p1 = pinicio;
        }

    }
    *maiorContador = contadorIndice;
    return pinicio;
}


/*FAZ UMA BUSCA RECURSIVA NA ARVORE EM BUSCA DO INDICE EM QUESTAO, PERMITINDO A CONSTRUCAO DA LISTA QUE GERARA A TABELA*/
reg *buscarNaArvore(reg *pinicio, int cont, reg *p2, int *anterior) {

    reg *p1 = NULL;
    if (pinicio != NULL) {
        if (pinicio->indice == cont) {
            p1 = pinicio;
	    if(p2 == NULL){
		*anterior = 0;
	    }else{
	       *anterior = p2->indice;
	    }
	    
        }
        if (p1 == NULL) {
            if(pinicio->prox != NULL) {
               p1 = buscarNaArvore(pinicio->prox, cont, p2, anterior);
            }
        }
	if (p1 == NULL) {
            if(pinicio->filhas != NULL) {
		p1 = buscarNaArvore(pinicio->filhas, cont, pinicio, anterior);
            }
        }
    }
    return p1;
}


int compactarLempelZiv(tab* pinicioTabela, FILE *arq) {

    tab* p1 = pinicioTabela;
    int numBits = 1;
    int numeroDeBitsTotal = 0;
    putc('L',arq);
    putc('\n', arq);
    fwrite(&numeroDeBitsTotal, sizeof(int),1,arq);
    putc('\n', arq);
    fwrite(&(p1)->letraRaiz, sizeof(char),1, arq);
    numeroDeBitsTotal = numeroDeBitsTotal + 8;

    char bitsAux = 0;
    int cont = 0;
    int i = 0;
    int marcadorBits = 1;
    char buffer = 0;
    while(p1->prox != NULL){
        p1 = p1->prox;
        bitsAux = (char)p1->indiceAnterior;
        for(i = 0; i< numBits; i++){
            buffer <<= 1;
            if(bitsAux & 1){
                buffer |= 1;
            }
	    bitsAux >>= 1;
            cont = cont + 1;
            if (cont == 8){
                numeroDeBitsTotal = numeroDeBitsTotal + cont;
                cont = 0;
                fwrite(&buffer, sizeof(char), 1, arq);
                buffer = 0;
            }                
        }
        bitsAux = (char)p1->letraRaiz;
        if(bitsAux != EOF){
            for(i = 0; i < 8; i++){
                buffer <<= 1;
                if(bitsAux & 1){
                    buffer |= 1;
                }
		bitsAux >>= 1;
                cont = cont + 1;
                if (cont == 8){
                    numeroDeBitsTotal = numeroDeBitsTotal + cont;
                    cont = 0;
                    fwrite(&buffer, sizeof(char), 1, arq);
                    buffer = 0;
                }
            }
        }
        if((p1->indice + 1) > 2*marcadorBits){
            numBits = numBits + 1;
            marcadorBits = marcadorBits*2;
	}
    }
    numeroDeBitsTotal = numeroDeBitsTotal + cont;
    if(cont != 0){
        fwrite(&buffer, sizeof(char), 1, arq);
        fwrite(&cont, sizeof(char), 1, arq);
    }
    fseek(arq, 2, 0);
    fwrite(&numeroDeBitsTotal, sizeof(int), 1, arq);
    fclose(arq);

    return numeroDeBitsTotal;
}

tab *adicionarNaLista(tab *pinicio, tab *registro) {
    tab *paux = NULL;

    if (pinicio == NULL) {
	pinicio = registro;
    } else {
	paux = pinicio;
	while (paux->prox != NULL) {
	    paux = paux->prox;
	}
	paux->prox = registro;
	registro->ant = paux;
    }

    return pinicio;
}
