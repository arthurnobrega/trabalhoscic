#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Tipos.h"
#include "Controle.h"
#include "../Persistencia/Arquivos.h"


/*A PARTIR DE UM ARQUIVO TEXTO, ESSA FUNCAO CRIA UMA ARVORE GENERICA,
IRMAOS(PROX) E FILHAS, CADA FILHA REPRESENTADO UM CHAR*/
reg* criarArvore(int* maiorContador, int* bytes,char* arqEntrada){
    
    FILE* arq = fopen(arqEntrada, "r");
    char caracter;
    reg *pinicio = NULL;
    reg *p1 = NULL;
    reg *p2 = NULL;
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
}









/*FUNCAO DE COMPACTACAO UTILIZANDO O ALGORITMO LEMPELZIV. RECEBE COMO PARAMETROS UMA
LISTA CONTENDO OS INDICES E OS SEUS RESPECTIVOS VALORES, BEM COMO O INDICE ANTERIOR.*/
void compactarLempelZiv(tab* pinicioTabela){

    FILE *arq = fopen("escrita","w"); //ARQUIVO DE SAIDA
    tab* p1 = pinicioTabela->prox; 
    int numBits = 1; /*MARCADOR QUE DIZ O NUMERO DE BITS QUE DEVEM SER LIDOS NO MOMENTO:
POR EXEMPLO: O NUMBITS SERA 1 QUANDO OS VALORES QUE SE PODE ASSUMIR ESTIVEREM ENTRE 0-1*/
    int numeroDeBitsTotal = 0; // CONTA O NUMERO DE BITS QUE O ARQUIVO COMPACTADO TERA.
    putc('L',arq);
    putc('\n', arq);
    fwrite(&numeroDeBitsTotal, sizeof(int),1,arq);
    putc('\n', arq);
    fwrite(&(p1)->letraRaiz, sizeof(char),1, arq);
    numeroDeBitsTotal = numeroDeBitsTotal + 8;
    char bits = 0; /*CARACTER QUE SEMPRE EH INICIALIZADO COM ZERO. TEM SEUS BITS ALTERADOS
BASEANDO-SE NO NUMERO E NA LETRA. SENDO ASSIM ELE EH A SAIDA, SENDO DESCARREGADO SEMPRE
QUE SEUS 8 BITS TIVEREM SIDO PREENCHIDOS*/
    char bitsAux; /*ARMAZENA O INDICE ANTERIOR*/
    char bitsAux2; /*ARMAZENA A LETRA RAIZ.*/
    int i = 0;
    int j = 0;

    int bitsIndice = 1; /*BOOLEANA QUE MARCA O TERMINO DA GRAVACAO DO INDICE QUE 
FOI PEGO NA MEMORIA PARA O bits QUE IRA SER DESCARREGADO PARA O DISCO*/
    int bitsLetra = 1; /*MESMO QUE O bitsIndice MAS COM A LETRA*/
    int marcadorBits = 1; /*VARIAVEL DE APOIO AO numBits*/


/*LE A LISTA, TABELA, INTEIRA*/
    while(p1->prox != NULL){

/*INCREMENTA O ANDAR NA LISTA*/
        if ((bitsIndice == 1) && (bitsLetra == 1)){
            p1 = p1->prox;
            bitsAux = p1->indiceAnterior;
            bitsAux2 = p1->letraRaiz;
            bitsIndice = 0;
            bitsLetra = 0;
        }

/*FAZ A INSERCAO DE CADA BIT DO INDICE, NO bits (VARIAVEL DE SAIDA)*/
        while (bitsIndice == 0){
            for(i = 0; (i < numBits) && (j < 8); i++){
                if(((bitsAux>>i)&1) == 0){
                    bits = (bits<<1)|1;
                }else{
                    bits = (bits<<1);                 
                }
                j = j + 1;
            }

/*EU CONSTATEI QUE PODERIAMOS TER 3 SITUACOES: 
OU O bits ENCHE ANTES DE SE TER 
TERMINADO DE LER OS BITS DO bitsAux TODO. NESSE CASO O BITS DEVERIA SER DESCARREGADO
NO DISCO E REINICIALIZADO.
OU O bitsAux TERIA TODOS SEUS BITS GRAVADOS NO bits E, PORTANTO, SERIA O MOMENTO DE COMEÇAR
A GRAVAR O bitsAux2(QUE HOSPEDA A LETRA).
OU OS DOIS ACABARAM JUNTOS - OCASIONARIA NAS DUAS ACOES ACIMA.
*/
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

/*FAZ O MESMO QUE O LOOP ACIMA, SO QUE PARA A LETRA AGORA.*/

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
            }else{
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

/*A PARTE DE LOOPS ESTA TODA CERTA. O ARQUIVO DE SAIDA ESTA SAINDO COM 31 BYTES, 
SENDO QUE DEVERIA SAIR COM 30: 177 bits /8 = 22bytes +1 bits. --> 1byte do 'L', 2 bytes
por '\n', e 4 bytes pelo numero de bytes do arquivo compactado (um integer). 

AI VAI OUTRA DUVIDA TAMBEM - QUANDO VOCE USA LEMPEL ZIV VOCE PODE ACONTECER DOS BITS NAO 
SEREM MULTIPLOS DE 8, FAZENDO SOBRAR BITS. SENDO ASSIM, VOCE ACABA GRAVANDO UM BIT INTEIRO NO
FINAL CERTO? FOI O QUE FIZ PELO MENOS.

VE SE TU ENTENDE E ME FALA ANTES DE MUDAR =)*/

/*O CONTADOR DE BITS QUE DEVEM SER GRAVADOS ESTA CORRETO. AQUI ELE FAZ O TESTE DO INDICE
SENDO LIDO DA LISTA (TABELA) E VERIFICA SE O NUMERO MAXIMO DE BITS QUE DEVEM SER LIDOS ESTA
CORRETO. ESSA FUNCAO ESTA FUNCIONANDO.*/
        if((p1->indice + 1) > 2*marcadorBits){
            numBits = numBits + 1;
            marcadorBits = marcadorBits*2;
        }
    }
    
    fseek(arq, 2, 0);
    fwrite(&numeroDeBitsTotal, sizeof(int), 1, arq);
    fclose(arq);
}
