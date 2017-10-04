#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int defeito;
	char outro[100];
}PROBLEMA;

typedef struct nodo_pilha{
    PROBLEMA problema;
    struct nodo_pilha * next;
}NODO_PILHA;

typedef NODO_PILHA * CHAMADO;

typedef struct nodo_fila{
    CHAMADO chamado;
    struct nodo_fila * next;
}NODO_FILA;

typedef struct{
    NODO_FILA *INICIO;
    NODO_FILA *FIM;
}DESCRITOR;

typedef DESCRITOR * FILA_DE_CHAMADOS;

void cabecalho();
int menu_programa();

void push (CHAMADO *pp, int op);
void cria_pilha(CHAMADO *);
void pop (CHAMADO *);
int eh_vazia_pilha (CHAMADO);
int top_pop_int (CHAMADO *);
//int top (CHAMADO );//


void cria_fila (FILA_DE_CHAMADOS *);
void inserir_chamado (FILA_DE_CHAMADOS, CHAMADO);
void retirar_chamado (FILA_DE_CHAMADOS);
int eh_vazia_fila (FILA_DE_CHAMADOS);

CHAMADO cons (FILA_DE_CHAMADOS);
CHAMADO cons_ret (FILA_DE_CHAMADOS);

int menu_problema(){

	int trouble;

	do{
	    cabecalho();
		printf("Digite:\n\n");
		printf("1- Se o computador nao liga.\n\n");
		printf("2- Se o computador liga,mas nao aparece algum erro no monitor.\n\n");
		printf("3- Se esta ocorrendo algum problema na instalacao de algum programa.\n\n");
		printf("4- Se algum periferico nao esta funcionando de forma adequada.\n\n");
		printf("5- Se o computador congela de forma repentina.\n\n");
		printf("6- Se alguma senha nao estiver funcionando.\n\n");
		printf("7- Se a internet nao esta funcionando.\n\n");
		printf("8- Se for outro problema.\n\n");
		printf("9- Para encerrar.\n\n");
		scanf("%d",&trouble);
   }while(trouble<1 || trouble>9);	
	return trouble;
}

int main(){ 
    FILA_DE_CHAMADOS fc;
    CHAMADO mimde;
    int option,rodar;

    cria_pilha(&mimde);
    cria_fila(&fc);  
    rodar=menu_programa();

    while(rodar){   
        do{
            option=menu_problema();
            if(option!=9)
            push(&mimde,option);
        }while(option!=9);

        inserir_chamado(fc,mimde);
        rodar=menu_programa();
    }
    while(!eh_vazia_fila(fc)){
        while(!eh_vazia_pilha(mimde)){
                if((mimde->problema).defeito)                    
                    printf("\n%d\n",top_pop_int(&mimde));
                else{   
                    printf("\n%s\n",(mimde->problema).outro);
                    pop(&mimde);
                } 
        }
        retirar_chamado(fc);
    }
    system("pause");
}

void cria_pilha(CHAMADO *pc){
	*pc=NULL;
}

void push (CHAMADO *pp, int op){
    NODO_PILHA *novo;
    novo = (NODO_PILHA *) malloc (sizeof(NODO_PILHA));
    if (!novo){
        printf ("\nERRO! Memoria insuficiente!\n");
        exit (1);
    }
    if(op==8){
        (novo->problema).defeito=0;    
        printf("Qual o problema? Descreva-o sucintamente.\n\n");
        setbuf(stdin,NULL);
        fflush(stdin);
        scanf("%99[^\n]",(novo->problema).outro);
    }else{
        (novo->problema).outro[0]='\0';                                   
        (novo->problema).defeito = op;
    }
    novo->next = *pp;
    *pp=novo;
}

int eh_vazia_pilha (CHAMADO c){
    return (!c);
}

/*int top (CHAMADO c)
{
if (eh_vazia(c))
{
printf ("\nERRO! Consulta em pilha vazia!\n");
exit (2);
}
else
return (c->);
}*/

void pop (CHAMADO *c){
    if (eh_vazia_pilha(*c)){
        printf ("\nERRO! Retirada em pilha vazia!\n");
        exit (3);
    }else{
        NODO_PILHA *aux=*c;
        *c=(*c)->next;
        free (aux);
    }
}

int top_pop_int (CHAMADO *c) {
    if (eh_vazia_pilha(*c)){
        printf ("\nERRO! Consulta e retirada em pilha vazia!\n");
        exit (4);
    }else{
        int v=(*c)->problema.defeito;
        NODO_PILHA *aux=*c;
        *c=(*c)->next;
        free (aux);
        return (v);
    }
}

void cria_fila (FILA_DE_CHAMADOS *fc){
    *fc=(DESCRITOR *)malloc(sizeof(DESCRITOR));
    if (!*fc){
        printf ("\nERRO! Memoria insuficiente!\n");
        exit (1);
    }
    (*fc)->INICIO=(*fc)->FIM=NULL;
}

int eh_vazia_fila (FILA_DE_CHAMADOS fc){
    return (fc->INICIO == NULL);
}

void inserir_chamado (FILA_DE_CHAMADOS fc, CHAMADO c) {
    NODO_FILA *novo;
    novo = (NODO_FILA *) malloc (sizeof(NODO_FILA));
    if (!novo){
        printf ("\nERRO! Memoria insuficiente!\n");
        exit (1);
    }
    novo->chamado = c;
    novo->next = NULL;
    if (eh_vazia_fila(fc))
        fc->INICIO=novo;
    else
        fc->FIM->next=novo;
    fc->FIM=novo;
}

CHAMADO cons (FILA_DE_CHAMADOS fc){
    if (eh_vazia_fila(fc)){
        printf ("\nERRO! Consulta em fila vazia!\n");
        exit (2);
    }else
        return (fc->INICIO->chamado);
}

void retirar_chamado (FILA_DE_CHAMADOS fc) {
    if (eh_vazia_fila(fc)){
        printf ("\nERRO! Retirada em fila vazia!\n");
        exit (3);
    }else{
        NODO_FILA *aux=fc->INICIO;
        fc->INICIO=fc->INICIO->next;
        if (!fc->INICIO)
        fc->FIM=NULL;
        free (aux);
    }
}

CHAMADO cons_ret (FILA_DE_CHAMADOS fc) {
    if (eh_vazia_fila(fc)){
        printf ("\nERRO! Consulta e retirada em fila vazia!\n");
        exit (4);
    }else{
        CHAMADO v=fc->INICIO->chamado;
        NODO_FILA *aux=fc->INICIO;
        fc->INICIO=fc->INICIO->next;
        if (!fc->INICIO)
        fc->FIM=NULL;
        free (aux);
        return (v);
    }
}
 
void cabecalho(){
    //system("clear > nul"); //verificar ubuntu
    system("cls");
    printf("------------------------------------------------------\n");
    printf("\t\t\tHELP DESK\n");
    printf("------------------------------------------------------\n\n");
}

int menu_programa(){
   int escolha;
   do{
      printf("\nDigite:\n");
      printf("\n1- Para fazer um novo chamado.\n");
      printf("\n0- Para encerra o programa.\n");
      scanf("%d",&escolha);
   }while(escolha<0 || escolha>1);
   return escolha;
}
