#ifndef AVP_H_INCLUDED
#define AVP_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//========================================================================================
//======================================ESTRUTURA DA AVP==================================
//========================================================================================

typedef struct avp_no {
    char    palavra[50];
    int     cor;
    struct  avp_no *fesq, *fdir, *pai;
    struct  lista_pagina *l_pag;
}AVP;

//========================================================================================
//======================================LISTA PAGINAS=====================================
//========================================================================================

typedef struct lista_pagina {
  int          pagina;
  struct       lista_pagina *prox;
}PAG;

//========================================================================================
//======================================PROCEDIMENTOS=====================================
//========================================================================================

AVP* avp_preenche(AVP *arvore, char *argv);
AVP* avp_indice(AVP *arvore, char *argv);
AVP* avp_nova();
AVP* ab_insere(AVP **raiz, char chave[50]);
AVP* avp_insere(AVP *raiz, char chave[50]);
int avp_remover(AVP *raiz, char chave[50]);
AVP* avp_transplant(AVP *raiz, AVP *u, AVP *v);
AVP* avp_delete(AVP *raiz, AVP *x);
AVP* sucessor(AVP *raiz);
int avp_consulta(AVP *raiz, char chave[50]);
AVP* rotacao_esquerda1(AVP *raiz, AVP *y);
AVP* rotacao_direita1(AVP *raiz, AVP *y);
int e_avp_(AVP *arvore, int *altura_preta);
int e_avp(AVP *arvore);
int altura(AVP *arvore);
void in_ordem1(AVP *arvore);
AVP* avp_insere_indice(AVP *raiz, char chave[50], int pag);
void in_ordem_file1(AVP *arvore, FILE *saida);
AVP* avp_busca_no1(AVP *arvore, char chave[50]);
void maiuscula(char str[50]);

void cabecalho();
void menu1(AVP *arvore);
void menu5(AVP *arvore);
void menu2(AVP *arvore);
void menu3(AVP *arvore);
void menu4(AVP *arvore);
void menuSaida(AVP *arvore);

#endif // AVP_H_INCLUDED
