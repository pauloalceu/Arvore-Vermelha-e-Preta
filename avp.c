#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "avp.h"

//========================================================================================
//======================n� que representa a �rvore vazia==================================
//========================================================================================

struct avp_no no_nil = {
     "",
     0,
     &no_nil,
     &no_nil,
     &no_nil,
     NULL
};
struct avp_no *AVP_NIL = &no_nil;

//========================================================================================
//=======================Le o arquivo e insere as palavras nos n�s========================
//========================================================================================
/*
avp_preenche � respons�vel por ler o arquivo Palavra.txt e chamar a funcao de inser��o na
�rvore para cada palavra encontrada.
*/
AVP* avp_preenche(AVP *arvore, char *argv){
    FILE *file = fopen(argv, "r" );  //ABRINDO O PRIMEIRO ARQUIVO
    char chave[50];

    if (file == NULL ){
        printf( "Nao foi possivel abrir o Primeiro arquivo!\n" );
    }else{
        // Count � a linha que t�!
        int x, count = 1;

        strcpy(chave, "");

        while ((x = fgetc(file)) != EOF){
            if (x == '\n'){
                count++;
            }
                if( ((!isalnum(x)) && (!isspace(x))) && ( !((x>=192) && (x<=253)))   ){ //192 e 253 eh o ASCII de acentuacao
                    //insere a palavra na arvore VP
                    arvore = avp_insere(arvore, chave);
                    //limpa a string
                    memset(&chave, 0, sizeof(chave));

                }else{
                    //concatena os caracteres at� que se forme uma palavra v�lida
                    if(strlen(chave) < 49 && (!isspace(x))){
                        sprintf(chave, "%s%c", chave, toupper(x));
                    }
                }
        }
        fclose(file);
    }

    return arvore;
}

//========================================================================================
//===============================Le o arquivo e insere as palavras nos n�s.===============
//========================================================================================
/*
avp_indica � respons�vel por ler o arquivo Dados e procurar palavras que estejam na �rvore. A cada
palavra encontrada no arquivo, � feita uma consulta na �rvore. A linha em que a palavra foi encontrada
tamb�m � passada como par�metro para compor o �ndice (no caso da palavra existir na AVP).
*/
AVP* avp_indice(AVP *arvore, char *argv){
    FILE *file = fopen(argv, "r" );  //ABRINDO O PRIMEIRO ARQUIVO
    char chave[50];

    if (file == NULL ){
        printf( "N�o foi poss�vel abrir o Primeiro arquivo!\n" );
    }else{
        // Count � a linha que t�!
        int x,count = 1;

        //printf( "%d\n", count);




        strcpy(chave, "");

        while ((x = fgetc(file)) != EOF){


        switch (x) {
                    case '�' :
                    case '�' :
                        x = 'C';
                }


            //aqui checa se � diferente de letra ou numero
            if(!isalnum(x)  && ( !((x>=192) && (x<=253)))){ //192 e 253 eh o ASCII de acentua��o
                //busca palavra na �rvore.
                arvore = avp_insere_indice(arvore, chave, count);
                strcpy(chave, "");
            }else{
                 //concatena os caracteres at� que se forme uma palavra v�lida
                    x = x - 32;
                    sprintf(chave, "%s%c", chave, toupper(x));
            }
            if (x == '\n'){
                    //conta as linhas
                count++;
            }
        }
        fclose(file);
    }
    return arvore;
}

//========================================================================================
//=================================cria uma nova avp======================================
//========================================================================================

AVP* avp_nova()
{
    return AVP_NIL;
}

//========================================================================================
//====================================INSER��O EM AVP=====================================
//========================================================================================
/*
a funcao ab_insere recebe a raiz da arvore e percorre em busca da posi��o correta para
inserir a nova palavra.
*/
AVP* ab_insere(AVP **arvore, char chave[50]){
    AVP *no = AVP_NIL;

    if(*arvore == AVP_NIL){
        AVP *novo_no= (AVP*) malloc(sizeof(AVP));
        strncpy(novo_no->palavra, chave, 50);
        novo_no->cor = 1;
        novo_no->fesq = novo_no->fdir = novo_no->pai = AVP_NIL;
        novo_no->l_pag = NULL;
        //INSERE AS P�GINAS NA LISTA ENCADEADA
        *arvore = novo_no;
        return *arvore;
    }else{
       if((strcmp((*arvore)->palavra,chave)) == 0){
            exit(0);
        }
        //esquerda
        if (strcmp((*arvore)->palavra,chave) > 0){
            no = ab_insere(&(*arvore)->fesq, chave);
        }else{
            //direita
            no = ab_insere(&(*arvore)->fdir, chave);
        }
    }

    if(no != AVP_NIL && no->pai == AVP_NIL){
        no->pai = *arvore;
    }
    return no;
}

/*
a fun��o avp_insere recebe uma palavra lida do arquivo palavras.txt e insere na
arvore. Ap�s a inser��o s�o feitas as verifica��es das propriedades de uma AVP e as
opera��es necess�rias para balance�-la.

S�o verificados os seguintes casos:
pai � vermelho?
tio � vermelho: mudan�a de cores

tio � preto: mudan�a de cores e rota��es necess�rias.
*/
AVP* avp_insere(AVP *arvore, char chave[50]){
    AVP *no, *tio;
    no = ab_insere(&(arvore), chave);

    while (no != arvore && no->pai->cor == 1){
        if (no->pai == no->pai->pai->fesq) {
            //no a esquerda
            tio = no->pai->pai->fdir;
            if (tio->cor == 1){
                //Se tio for vermelho:
                //o pai e o tio ficam pretos
                //o av� fica vermel0p~qho
                //se o av� for raiz fica preto (abaixo)
                no->pai->cor = 0;
                tio->cor = 0;
                no->pai->pai->cor = 1;
                no = no->pai->pai;
            } else {
                //pai a esquerda
                //tio preto
                if (no == no->pai->fdir){
                    //filho a direita
                    //rotacao dupla
                    //rota��o a esquerda
                    arvore = rotacao_esquerda1(arvore, no);
                    no = no->fesq;
                }
                    //filho a esquerda
                    //rotacao simples a direita
                no->pai->cor = 0;
                no->pai->pai->cor = 1;
                arvore = rotacao_direita1(arvore, no->pai);

            }
        } else {
            tio = no->pai->pai->fesq;
            if (tio->cor == 1){
                no->pai->cor = 0;
                tio->cor = 0;
                no->pai->pai->cor = 1;
                no = no->pai->pai;
            }else{
                //pai a direita do avo
                if (no == no->pai->fesq) {
                    //filho a esquerda do pai
                    //rotacao dupla
                    //rota��o a direita
                    arvore = rotacao_direita1(arvore, no);
                    no = no->fdir;
                }
                //filho a direita do pai
                //rotacao simples a esquerda
                no->pai->cor = 0;			/* caso 3 */
                no->pai->pai->cor = 1;
                arvore = rotacao_esquerda1(arvore, no->pai);
            }
        }
    }
    arvore->cor = 0;
    return arvore;
}

//========================================================================================
//====================================CONSULTA EM AVP=====================================
//========================================================================================
/*
verifica se uma palavra existe na �rvore
*/
int avp_consulta(AVP *raiz, char chave[50]){
    AVP *no_del;
    no_del = avp_busca_no1(raiz, chave);

    if (no_del == AVP_NIL){
        return 0;
    }
    return 1;
}

//========================================================================================
//====================================REMO��O EM AVP======================================
//========================================================================================
/*
Fun��o remove um n� da �rvore. Dada uma palavra a fun��o busca o n� atrav�s da fun��o avp_busca_no
se encontrado o n� � deletado, assim como sua lista de p�ginas. Ap�s a dele��o as propriedades da AVP
s�o checadas e, se necess�rio, s�o aplicadas as opera��es para refazer as propriedades.
Implementada segundo a abordagem do Cormen.
*/
int avp_remover(AVP *arvore, char chave[50]){
    AVP *x, *y, *no_del;
    no_del = avp_busca_no1(arvore, chave);

    if (no_del == AVP_NIL){
        return 0;
    }

    y = no_del;
    int cor_original;

    cor_original=y->cor;    //COR DO NO QUE SERA EXCLUIDO

    if (no_del->fesq == AVP_NIL){
        x=no_del->fdir;
        arvore = avp_transplant(arvore, no_del, no_del->fdir);
    }else if(no_del->fdir == AVP_NIL){
        x=no_del->fesq;
        arvore = avp_transplant(arvore,no_del, no_del->fesq);
    }else{
        y=sucessor(no_del->fdir);
        cor_original = y->cor;
        x = y->fdir;
            if (y->pai==no_del){
                x->pai=y;
            }else{
                arvore = avp_transplant(arvore, y, y->fdir);
                y->fdir=no_del->fdir;
                y->fdir->pai=y;
            }
        arvore = avp_transplant(arvore, no_del, y);
        y->fesq=no_del->fesq;
        y->fesq->pai=y;
        y->cor = no_del->cor;
    }
    if (cor_original == 0){
        arvore = avp_delete(arvore, x);
    }

    //Removendo ponteiro de p�ginas
    PAG *aux;
    while (no_del->l_pag != NULL){
        aux = no_del->l_pag->prox;
        free(no_del->l_pag);
        no_del->l_pag = aux;
    }

    free(no_del);
    return 1;
}
//========================================================================================
//==================================BUSCA=================================================
//========================================================================================

AVP* avp_busca_no1(AVP *arvore, char chave[50]){
    AVP *no = AVP_NIL;

       if(arvore != AVP_NIL){
           if((strcmp(arvore->palavra,chave)) == 0){
                return arvore;
            }
            if (strcmp(arvore->palavra,chave) > 0){
                //esquerda
                no = avp_busca_no1(arvore->fesq, chave);
            }else{
                //direita
                no = avp_busca_no1(arvore->fdir, chave);
            }
       }
       return no;
}

AVP* avp_transplant(AVP *arvore, AVP *u, AVP *v){
    if (u->pai == AVP_NIL){
        arvore=v;
    }else if (u == u->pai->fesq){
        u->pai->fesq = v;
    }else{
        u->pai->fdir = v;
    }
    v->pai=u->pai;
    return arvore;
}

AVP* avp_delete(AVP *arvore, AVP *x){
    AVP *tio;
    while((x != arvore) && (x->cor == 0)){
        if(x == x->pai->fesq){
            tio = x->pai->fdir;
            if(tio->cor == 1){
                tio->cor = 0;
                x->pai->cor = 1;
                arvore = rotacao_esquerda1(arvore, x);
                tio = x->pai->fdir;
            }
            if(tio->fesq->cor == 0 && tio->fdir->cor == 0){
                tio->cor = 1;
                x=x->pai;
            }else if(tio->fdir->cor == 0){
                tio->fesq->cor = 0;
                tio->cor = 1;
                arvore = rotacao_direita1(arvore, tio);
                tio = x->pai->fdir;
                tio->cor = x->pai->cor;
                x->pai->cor = 0;
            }
            tio->fdir->cor = 0;
            arvore = rotacao_esquerda1(arvore, x->pai);
            x = arvore;
        }else{
            tio = x->pai->fesq;
            if(tio->cor == 1){
                tio->cor = 0;
                x->pai->cor = 1;
                arvore = rotacao_direita1(arvore, x);
                tio = x->pai->fesq;
            }
            if(tio->fdir->cor == 0 && tio->fesq->cor == 0){
                tio->cor = 1;
                x=x->pai;
            }else if(tio->fesq->cor == 0){
                tio->fdir->cor = 0;
                tio->cor = 1;
                arvore = rotacao_esquerda1(arvore, tio);
                tio = x->pai->fesq;
                tio->cor = x->pai->cor;
                x->pai->cor = 0;
            }
            tio->fesq->cor = 0;
            arvore = rotacao_direita1(arvore, x->pai);
            x = arvore;
        }
    }
    return arvore;
}

//========================================================================================
//======================================sucessor==========================================
//========================================================================================
AVP* sucessor(AVP *arvore){
    AVP *no = arvore;
    while(no->fesq != AVP_NIL){
        no = no->fesq;
    }
    return no;
}

//========================================================================================
//==========================rota��o esquerda numa apv=====================================
//========================================================================================

AVP* rotacao_esquerda1(AVP *arvore, AVP *y){
    AVP *x;
    x = y->pai;

    x->fdir = y->fesq;		// a sub�rvore esq. de y passa a dir. de x
    if (x->fdir != AVP_NIL){
        x->fdir->pai = x;
    }

    y->pai = x->pai;		// o pai de x torna-se o pai de y
    if (y->pai != AVP_NIL){	// o filho do pai de x fica y
        if (y->pai->fesq == x){
            y->pai->fesq = y;
        }else{
            y->pai->fdir = y;
        }
    }else{				// x era a raiz da �rvore
        arvore = y;
    }

    y->fesq = x;			// x torna-se o filho esq. de y
    x->pai = y;
    return arvore;
}

//========================================================================================
//=============================== rota��o direita numa apv ===============================
//========================================================================================

AVP* rotacao_direita1(AVP *arvore, AVP *y)
{
    AVP *x;
    x = y->pai;

    x->fesq = y->fdir;		// a sub�rvore esq. de y passa a dir. de x
    if (x->fesq != AVP_NIL){
        x->fesq->pai = x;
    }

    y->pai = x->pai;		// o pai de x torna-se o pai de y
    if (y->pai != AVP_NIL){	// o filho do pai de x fica y
        if (y->pai->fdir == x){
            y->pai->fdir = y;
        }else{
            y->pai->fesq =y;
        }
    }else{				// x era a raiz da �rvore
        arvore = y;
    }

  y->fdir = x;			// x torna-se o filho esq. de y
  x->pai = y;

  return arvore;
}

//========================================================================================
//========================determina se uma �rvore � uma avp===============================
//========================================================================================

int e_avp_(AVP *arvore, int *altura_preta){
  int ape, apd;		/* alturas pretas das sub�rvores esq. e dir. */

  /* uma �rvore vazia � uma avp com altura-preta 0 */
  if (arvore == AVP_NIL) {
    *altura_preta = 0;
    return 1;
  }

  /* se alguma das sub�rvores n�o � uma avp, a �rvore n�o � uma avp */
  if (!e_avp_(arvore->fesq, &ape) || !e_avp_(arvore->fdir, &apd))
    return 0;

  /* se o n� � vermelho, ambos os filhos t�m de ser pretos (ou NIL) e
     as duas sub�rvores t�m de ter a mesma altura-preta */
  if (arvore->cor == 1) {
    if (arvore->fesq->cor == 1 || arvore->fdir->cor == 1 || ape != apd)
      return 0;
    else {
      *altura_preta = ape + 1;
      return 1;
    }
  }

  /* o n� � preto, se um filho for preto, a altura-preta do n� vai ser
     a do filho + 1, se for vermelho vai ser a do filho, e o mesmo
     valor tem de ser obtido para ambos os filhos */
  if (&(arvore)->fesq->cor == 0)
    ++ape;
  if (&(arvore)->fdir->cor == 0)
    ++apd;
  *altura_preta = ape;
  return ape == apd;
}

int e_avp(AVP *arvore){
  int ap;		/* altura preta da �rvore */
  return e_avp_(arvore, &ap);
}

//========================================================================================
//=================================C�lculo de Altura de uma VP============================
//========================================================================================

int altura(AVP *arvore) {
   if (arvore == AVP_NIL)
      return -1; // altura de �rvore vazia � -1
   else {
      int he = altura(arvore->fesq);
      int hd = altura(arvore->fdir);
      if (he < hd) return hd + 1;
      else return he + 1;
   }
}

//========================================================================================
//============================Varrendo in-Ordem a �rvore==================================
//========================================================================================
void in_ordem1(AVP *arvore) {
    PAG *noatual;
    if (arvore != AVP_NIL) {
       in_ordem1(arvore->fesq);
       printf( "%s ---(%s)--", arvore->palavra, arvore->pai->palavra);
       noatual = arvore->l_pag;
       if(noatual != NULL){
            while(noatual != NULL){
                printf( "%d,", noatual->pagina);
                noatual = noatual->prox;    /* Ao final do while, noatual aponta para o ultimo no */
            }
       }
       printf("\n");
       in_ordem1(arvore->fdir);
    }
}
//========================================================================================
//==================================IN ORDEM COM ARQUIVO==================================
//========================================================================================
void in_ordem_file1(AVP *arvore, FILE *saida) {
    PAG *noatual;
    if (arvore != AVP_NIL) {
       in_ordem_file1(arvore->fesq, saida);
       fprintf(saida, "%s -----", arvore->palavra);
       noatual = arvore->l_pag;
       if(noatual != NULL){
            while(noatual != NULL){
                fprintf(saida, "%d,", noatual->pagina);
                noatual = noatual->prox;    /* Ao final do while, noatual aponta para o ultimo no */
            }
       }
       fprintf(saida, "\n");
       in_ordem_file1(arvore->fdir, saida);
    }
}
//========================================================================================
//===================================BUSCA CON INSER��O===================================
//========================================================================================

AVP* avp_insere_indice(AVP *arvore, char chave[50], int pag){
    AVP *no;

    no = avp_busca_no1(arvore, chave);

    //INSERE PAGINA NA LISTA DE INTEIROS DE CADA NO
    PAG *noatual, *novono;

    if (no->l_pag == NULL){ //Primeiro a ser inserido
        novono = malloc(sizeof(int));
        novono->pagina = pag;
        novono->prox = NULL;
        no->l_pag = novono;
    }else{
    /* Se ja existem elementos na lista, deve percorre-la ate' o seu final e inserir o novo elemento */
        noatual = no->l_pag;
        while(noatual->prox != NULL){
            noatual = noatual->prox;    /* Ao final do while, noatual aponta para o ultimo no */
        }
        novono =  malloc(sizeof(int));/* Aloca memoria para o novo no */
        novono->pagina = pag;
        novono->prox = NULL;
        noatual->prox = novono;     /* Faz o ultimo no apontar para o novo no */
    }
    return arvore;
}

void maiuscula(char str[50])
{
    int i = 0;
    int len = 0;

    len = strlen(str);

    for(i = 0; i< len; i++)
    {
       str[i] = toupper(str[i]);
        switch (str[i]) {
                    case '�' :
                        str[i] = 'C';
                        continue;
                    case '�' :
                    case '�' :
                    case '�' :
                    case '�' :
                    case '�' :
                        str[i] = 'A';
                        continue;
                    case '�' :
                    case '�' :
                    case '�' :
                    case '�' :
                        str[i] = 'E';
                        continue;
                    case '�' :
                    case '�' :
                    case '�' :
                    case '�' :
                        str[i] = 'I';
                        continue;
                    case '�' :
                    case '�' :
                    case '�' :
                    case '�' :
                    case '�' :
                        str[i] = 'O';
                        continue;
                    case '�' :
                    case '�' :
                    case '�' :
                    case '�' :
                        str[i] = 'U';
                        continue;
                }
    }
    //terminate string
    str[i]= '\0';
}
//========================================================================================
//========================================================================================
//========================================================================================
