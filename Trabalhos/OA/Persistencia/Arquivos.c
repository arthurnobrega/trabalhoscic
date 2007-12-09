#include "Arquivos.h"
#include "../Tipos.h"

int abrirArquivo(FILE *arq, char *nomeArq, char *modo) {

    arq = fopen(nomeArq, modo);
    if (arq == NULL) {
	   return 0;
    }
    return 1;
}

/*GRAVA O MAIOR INDICE ENCONTRA NA ARVORE NO ARQUIVO*/
void gravarMaiorIndiceTabela(int maiorIndice){
    FILE *arq = fopen("tabela","a");
    fwrite(&maiorIndice, sizeof(int), 2, arq);
    fclose(arq);
}

/*RECEBE OS DADOS RELATIVOS AOS CAMPOS DA TABELA E OS GRAVA NO ARQUIVO.*/
void gravarTabelaArq(int indice, char letra,int indiceAnterior){
    FILE *arq = fopen("tabela","a");
    fwrite(&indice, sizeof(int), 1, arq);
    fwrite(&letra, sizeof(char), 1, arq);
    fwrite(&indiceAnterior, sizeof(int), 1, arq);
    fclose(arq);
}

/*ATRAVÉS DO ARQUIVO, GERA UMA LISTA SIMPLESMENTE ENCADEADA NA QUAL ESTARÃO OS 
ELEMENTOS DA TABELA.*/
tab* criarTabela(void){

    FILE *arq = fopen("tabela","r");
    int maiorIndice = 0;
    int i;
    tab *pinicio = malloc(sizeof(tab));
    tab* p1 = NULL;
    tab* p2 = NULL;

    pinicio->prox = NULL;
    pinicio->indice = 0;
    pinicio->indiceAnterior = -1;
    pinicio->letraRaiz = '-';
    p1 = pinicio;
    fread(&maiorIndice, sizeof(int), 1, arq);
    for(i = 0; i < maiorIndice; i++){
        p2 = malloc(sizeof(tab));
        p1->prox = p2;
        p1 = p2;
        p1->prox = NULL;
        fread(&p1->indice, sizeof(int), 1, arq);
        fread(&p1->letraRaiz, sizeof(char), 1, arq);
        fread(&p1->indiceAnterior, sizeof(int), 1, arq);
    }
    fclose(arq);
    remove("tabela");
    if(maiorIndice != 0){
        return pinicio;
    }else{
        return NULL;
    }
    
}
