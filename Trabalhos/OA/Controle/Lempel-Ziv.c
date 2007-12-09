#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Tipos.h"
#include "Controle.h"
#include "../Persistencia/Arquivos.h"

int corrigirBytes(reg p, int* maiorContador, reg* p2, int *bytes);

/*A PARTIR DE UM ARQUIVO TEXTO, ESSA FUNCAO CRIA UMA ARVORE GENERICA,
IRMAOS(PROX) E FILHAS, CADA FILHA REPRESENTADO UM CHAR*/
reg* criarArvore(int* maiorContador, int* bytes,char* arqEntrada){
    
    FILE* arq = fopen(arqEntrada, "r");
    char caracter;
    reg *pinicio = NULL;
    reg *p1 = NULL;
    int achou = 0;
    int acabouArvore = 0;
    int fimLinha = 0;
    int contadorIndice = *maiorContador;
    int contadorBytes = *bytes;

    while((caracter = getc(arq)) != EOF){
        contadorBytes = contadorBytes + 1;
        if(pinicio == NULL){
            pinicio = (reg*) calloc(1,sizeof(reg));
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
                    //p1 = p2;
                    
                }else{
                    caracter = getc(arq);
                    contadorBytes = contadorBytes + 1;
                    if (p1->filhas != NULL){
                        p1 = p1->filhas;                        
                    }else{
                        acabouArvore = 1;
                        p1->filhas = (reg*)calloc(1,sizeof(reg));
                        p1 = p1->filhas;
                        p1->letraRaiz = caracter;
                        contadorIndice = contadorIndice + 1;
                        p1->indice = contadorIndice;
                        p1->filhas = NULL;
                        p1->prox = NULL;
                        //p1 = p2;
                    }
                    achou = 0;
                }
            }
            acabouArvore = 0;
            p1 = pinicio;
        }

    }
    corrigirBytes(*p1, &contadorIndice, NULL, &contadorBytes);
    *bytes = contadorBytes;
    *maiorContador = contadorIndice;
    return pinicio;
    
}



/*ESSA FUNCAO GARANTE QUE O ULTIMO ELEMENTO DO INDICE NAO E O EOF,
E DESALOCA A MEMORIA USADA POR ELE*/
int corrigirBytes(reg p, int* maiorContador, reg* p2, int *bytes){
    
    reg* pinicio = &p;
    int achou = 0;
    if (pinicio != NULL){
        if(pinicio->indice == *maiorContador){
            if(pinicio->letraRaiz == EOF){
                *bytes = *bytes - 1;
            }
            achou = 1;
        }
        if(achou == 0){
            if(pinicio->prox != NULL){
               achou = corrigirBytes(*pinicio->prox, maiorContador, pinicio, bytes);
            }
        }
        if(achou == 0){
            if(pinicio->filhas != NULL){
               achou = corrigirBytes(*pinicio->filhas, maiorContador, pinicio, bytes);
            }
        }
    return achou;
    }
    return 0;
}

/*FAZ UMA BUSCA RECURSIVA NA ARVORE EM BUSCA DO INDICE EM QUESTAO, PERMITINDO A CONSTRUCAO DA 
LISTA QUE GERARA A TABELA*/
int buscarNaArvore(reg p, int cont, reg* p2){

    reg* pinicio = &p;
    int achou = 0;
    if (pinicio != NULL){

        if(pinicio->indice == cont){
            if(p2 != NULL){
                gravarTabelaArq(pinicio->indice , pinicio->letraRaiz,p2->indice);
            }else{
                gravarTabelaArq(pinicio->indice , pinicio->letraRaiz,0);
            }
            achou = 1;
        }
        if(achou == 0){
            if(pinicio->prox != NULL){
               achou = buscarNaArvore(*pinicio->prox, cont, p2);
            }
        }
        if (achou == 0){
            if(pinicio->filhas != NULL){
                achou = buscarNaArvore(*pinicio->filhas, cont, pinicio);
            }
        }
    return achou;
    }
    return 0;
}


void compactarLempelZiv(tab* pinicioTabela){

    FILE *arq = fopen("escrita","w");
    tab* p1 = pinicioTabela->prox;
    int numBits = 1;
    int numeroDeBitsTotal = 0;
    putc('L',arq);
    putc('\n', arq);
    fwrite(&numeroDeBitsTotal, sizeof(int),1,arq);
    putc('\n', arq);
    fwrite(&(p1)->letraRaiz, sizeof(char),1, arq);
    numeroDeBitsTotal = numeroDeBitsTotal + 8;
    char bits = 0;
    char bitsAux;
    char bitsAux2;
    int i = 0;
    int j = 0;

    int bitsIndice = 1;
    int bitsLetra = 1;
    int marcadorBits = 1;



    while(p1->prox != NULL){
        if ((bitsIndice == 1) && (bitsLetra == 1)){
            p1 = p1->prox;
            bitsAux = p1->indiceAnterior;
            bitsAux2 = p1->letraRaiz;
            bitsIndice = 0;
            bitsLetra = 0;
        }
        while (bitsIndice == 0){
            for(i = 0; (i < numBits) && (j < 8); i++){
                if(((bitsAux>>i)&1) == 0){
                    bits = (bits<<1)|1;
                }else{
                    bits = (bits<<1);                 
                }
                j = j + 1;
            }
            if(i < numBits){

                bits = ~bits;
                fwrite(&bits, sizeof(char), 1, arq);
                numeroDeBitsTotal = numeroDeBitsTotal + 8;
                bits = 0;
                j = 0;
            }else{
                if(j < 8){
                    bitsIndice = 1;
                }else{
                    bits = ~bits;
                    fwrite(&bits, sizeof(char), 1, arq);
                    numeroDeBitsTotal = numeroDeBitsTotal + 8;
                    bits = 0;
                    j =  0;
                    bitsIndice = 1;
                }
            } 
        }

        i = 0;
        while (bitsLetra == 0){
            for(i ; (i < 8) && (j < 8); i++){
                    if(((bitsAux2>>i)&1) == 0){
                        bits = (bits<<1)|1;
                    }else{
                        bits = (bits<<1);
                }
                    j = j + 1;
            }

            if(i < 8){
                bits = ~bits;
                fwrite(&bits, sizeof(char), 1, arq);
                numeroDeBitsTotal = numeroDeBitsTotal + 8;
                bits = 0;
                j =  0;
            } else {
                if(j < 8){
                    bitsLetra = 1;
                }else{
                    bits = ~bits;
                    fwrite(&bits, sizeof(char), 1, arq);
                    numeroDeBitsTotal = numeroDeBitsTotal + 8;
                    bits = 0;
                    j =  0;
                    bitsLetra = 1;
                }
            }
        }

        if((p1->indice + 1) > 2*marcadorBits){
            numBits = numBits + 1;
            marcadorBits = marcadorBits*2;
        }
    }
    
    fseek(arq, 2, 0);
    fwrite(&numeroDeBitsTotal, sizeof(int), 1, arq);
    fclose(arq);
}
