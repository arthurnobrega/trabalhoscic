#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registro *reg;

struct registro{
    char letraRaiz;
    reg *filhas;
    reg *prox;
    int indice;
};

//cria uma lista encadeada com a sequencia de caracter do codigo LZ
void criarLista(FILE *arq, reg *pretorno){
    char caracter;

    reg pinicio = *pretorno;
    reg p1 = NULL;
    int achou = 0;
    int acabouArvore = 0;
    int fimLinha = 0;
    int contadorIndice = 0;

    
    while((caracter = getc(arq)) != EOF){
        printf("\n                                   %c\n", caracter);
        if(pinicio == NULL){
            pinicio = malloc(sizeof(reg));
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
                    contadorIndice = contadorIndice + 1;
                    p1->indice = contadorIndice;
                    p1->prox = NULL;
                    p1->filhas = NULL;

                    
                }else{
                    printf("andando para as filhas");
                    caracter = getc(arq);
                    if (p1->filhas != NULL){
                        p1 = *p1->filhas;                        
                    }else{
                        printf("%c\n", caracter);
                        acabouArvore = 1;
                        p1->filhas = malloc(sizeof(reg));
                        p1 = *p1->filhas;
                        p1->letraRaiz = caracter;
                        contadorIndice = contadorIndice + 1;
                        p1->indice = contadorIndice;
                        p1->filhas = NULL;
                        p1->prox = NULL;
                        //caracter = getc(arq);
                        printf("%c\n", caracter);
                    }
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

    FILE *arq = fopen("teste.txt","r");
    reg pinicio = NULL;

    criarLista(arq, &pinicio);
    reg p1 = pinicio;

    while(p1->prox != NULL){
        printf("%c\n",p1->letraRaiz);
        printf("%d", p1->indice);
        p1 = *p1->prox;
    }
        printf("%c\n",p1->letraRaiz);
        printf("%d", p1->indice);

printf("\n\n");
reg p2 = pinicio;
p1 = *p2->filhas;
while (p2->prox != NULL){
printf("\n\n");
    while(p1->prox != NULL){
        printf("%c\n",p1->letraRaiz);
        printf("%d", p1->indice);
        p1 = *p1->prox;
    }
        printf("%c\n",p1->letraRaiz);
        printf("%d", p1->indice);
    p2 = *p2->prox;
    while(p2->filhas == NULL){
        p2 = *p2->prox;
    }
        p1 = *p2->filhas;    


}
while(p1->prox != NULL){
        printf("%c\n",p1->letraRaiz);
        p1 = *p1->prox;
    }
        printf("%c\n",p1->letraRaiz);

    int a = 1;
    scanf("%d",a);
    
return 0;
}
