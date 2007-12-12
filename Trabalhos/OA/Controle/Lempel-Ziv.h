/** Programa de Compactação e Descompactação utilizando Huffman e Lempel-Ziv.

Autores do programa:
Arthur Thiago Barbosa Nobrega - 06/31205
Davi Fantino da Silva - 06/40832

Versão 1.0
Data: 11/12/2007
Compilador: gcc 4.1.2 20061115 (prerelease) (Debian 4.1.1-21)

Descrição: Este programa tem por objetivo dispor ao usuário compactar e descompactar arquivos utilizando Huffman e Lempel-Ziv. O usuário também tem a opção de simplesmente mostrar a tabela de Huffman do arquivo fornecido ou o dicionário de Lempel-Ziv, além de poder comparar qual o melhor algorítmo para compactar aquele determinado arquivo.
*/

#ifndef LEMP_H
#define LEMP_H
#include <stdio.h>
#include "../Tipos.h"

/** Função para criar a árvore de Lempel-Ziv.
 * Data: 10/12/2007
 * Versão: 1.0
 * Autores:
     Arthur Thiago Barbosa Nobrega - 06/31205
     Davi Fantino da Silva - 06/40832
 * @param arq Arquivo que contém o texto.
 * @return Ponteiro para o início da lista.
 */
tab* criarArvoreLista(FILE* arq);

/** Função para buscar recursivamente um índice na árvore.
 * Data: 10/12/2007
 * Versão: 1.0
 * Autores:
     Arthur Thiago Barbosa Nobrega - 06/31205
     Davi Fantino da Silva - 06/40832
 * @param pinicio Ponteiro de início da árvore.
 * @param cont Índice a ser procurado.
 * @param p2 Ponteiro de marcação do pai.
 * @param anterior Índice do pai.
 * @return Ponteiro para o registro que contém o índice procurtab *pfim,ado.
 */
reg *buscarNaArvore(reg *pinicio, int cont, reg *p2, int *anterior);

/** Função que compacta o arquivo baseado na lista gerada pela árvore.
 * Data: 10/12/2007
 * Versão: 1.0
 * Autores:
     Arthur Thiago Barbosa Nobrega - 06/31205
     Davi Fantino da Silva - 06/40832
 * @param pinicioTabela Ponteiro de início da lista.
 * @param arq Arquivo binário de saída.
 * @return Número de bits que o arquivo compactado possui.
 */
int compactarLempelZiv(tab* pinicioTabela, FILE *arq);

/** Função para adicionar um registro na lista de sequências de Lempel-Ziv.
 * Data: 10/12/2007
 * Versão: 1.0
 * Autores:
     Arthur Thiago Barbosa Nobrega - 06/31205
     Davi Fantino da Silva - 06/40832
 * @param pinicio Ponteiro de início da lista.
 * @param registro Registro a ser adicionado no final da lista.
 * @return Ponteiro para o fim da lista.
 */
tab *adicionarNaLista(tab *pfim, tab *registro);

#endif
