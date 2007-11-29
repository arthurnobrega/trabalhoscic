#include "Lempel-Ziv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registro *reg;

struct registro{
    char letraRaiz;
    reg *filhas;
    reg *prox;
};

//cria uma lista encadeada com a sequencia de caracter do codigo LZ
void criarLista(FILE *arq, reg *pretorno){
    char caracter;

    reg pinicio = *pretorno;
    reg p1 = NULL;
    reg p2 = NULL;
    int achou = 0;
    int acabouArvore = 0;
    int fimLinha = 0;

    
    while((caracter = getc(arq)) != EOF){
        printf("\n                                   %c\n", caracter);
        if(pinicio == NULL){
            pinicio = malloc(sizeof(reg));
            pinicio->prox = NULL;
            pinicio->filhas = NULL;
            pinicio->letraRaiz = caracter;
            p1 = pinicio;
        }else{
            while(acabouArvore == 0){
                while ((achou == 0)&&(fimLinha == 0)){
                    if(p1->letraRaiz == caracter){
                        achou = 1;
                    }else{
                        if((p1->prox) != NULL){
                            p1 = *p1->prox;
                        }else{
                            fimLinha = 1;
                        }
                    }
                }
                if (achou == 0){
                    acabouArvore = 1;
                    fimLinha = 0;
                    p1->prox = malloc(sizeof(reg));
                    p1 = *p1->prox;
                    p1->letraRaiz = caracter;
                    p1->prox = NULL;
                    p1->filhas = NULL;

                    
                }else{
                    printf("andando para as filhas");
                    p1 = *p1->filhas;
                    caracter = getc(arq);
                    achou = 0;
                }
            }
            acabouArvore = 0;
            p1 = pinicio;
        }
        printf("sai da arvore\n");
    }
    printf("chega aqui?");
    *pretorno = pinicio;
}

int contarTamanhoDaLista(reg pinicio){
    int cont = 0;
    reg p1 = pinicio;
    while (p1 != NULL){
        cont = cont + 1;
        p1 = *p1->prox;
    }
    free(p1);
    return cont;
}

int main(){
    printf("aqui");
    FILE *arq = fopen("teste.txt","r");
    reg pinicio = NULL;
    printf("aqui");
    criarLista(arq, &pinicio);
    reg p1 = pinicio;
        printf("aqui");
    while(p1 != NULL){
        printf("antes do\n");
        printf("%c\n",p1->letraRaiz);
        printf("depois do\n");
        p1 = *p1->prox;
        printf("por fim\n\n");
    }
    printf("depois não");
    int a = 1;
    scanf("%d",a);
    
return 0;
}
