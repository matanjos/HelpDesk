#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int maquina; 
    int defeito;
    char outro[100];
}PROBLEMA;

typedef struct nodo_pilha{
    PROBLEMA problema;
    int contador;
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
    int qtd;
}DESCRITOR;

typedef DESCRITOR * FILA_DE_CHAMADOS;

void cabecalho();
int menu_programa();
int menu_problema();
int menu_principal();
int chrpergunta();
void fpause2();

//---------pilha---------
void push (CHAMADO *, int);
void cria_pilha(CHAMADO *);
CHAMADO zerarPilha(CHAMADO );
int pop (CHAMADO *);
int eh_vazia_pilha (CHAMADO);
PROBLEMA top (CHAMADO);

void muda(CHAMADO c){
    c->problema.defeito = 72;
}
void muda2(CHAMADO *c){
    (*c)->problema.defeito = 95;
}
//---------fila---------
void cria_fila (FILA_DE_CHAMADOS *);
void inserir_chamado (FILA_DE_CHAMADOS);
void retirar_chamado (FILA_DE_CHAMADOS);
int eh_vazia_fila (FILA_DE_CHAMADOS);

CHAMADO cons (FILA_DE_CHAMADOS);
CHAMADO cons_ret (FILA_DE_CHAMADOS);


//------------------------------------------------------------------------//

int main(){ 
    FILA_DE_CHAMADOS fc;
    PROBLEMA problm;
    int option,option2,rodar,aux;
    cria_fila(&fc);  
    cabecalho();
    rodar=menu_principal();
    while(rodar){ 
        switch(rodar){
            case 1:   //resolucao de problemas
                do{
                    option2=menu_programa();
                    switch(option2){
                        case 0: //voltar
                            break;
                        case 1: //chamado atual (mostrar as infos , problema atual,qtd de problemas no chamado e perguntar se quer resolver)
                            if(fc->INICIO){
                                printf("defeito direto : %d\n", (fc->INICIO)->chamado->problema.defeito);
                                if((fc->INICIO)->next)
                                    printf("defeito direto do proximo chamado : %d\n", ((fc->INICIO)->next)->chamado->problema.defeito);
                                problm = top((fc->INICIO)->chamado); 
                                if(problm.maquina != -1)
                                    printf("Computador anexado: ID %d\n",problm.maquina); 
                                else
                                    printf("Nenhuma maquina anexada.\n"); 
                                if(problm.defeito != -1)                    
                                    printf("\nDefeito :%d\n",problm.defeito);
                                else  
                                    printf("\nDefeito: %s\n",problm.outro);
                                    printf("Problema ja foi resolvido ?. (S ou N) \n\n");
                                
                                    aux = chrpergunta();
                                    if((aux) && aux != -1){
                                        pop(&((fc->INICIO)->chamado));
                                        printf("Sucesso!\n"); 
                                        if(eh_vazia_pilha((fc->INICIO)->chamado)){
                                            retirar_chamado(fc);
                                        }
                                    }
                            }else{
                                printf("Sem chamados cadastrados! \n");
                            }
                                
                            
                                /* while(!eh_vazia_fila(fc)){
                                    while(!eh_vazia_pilha(mimde)){
                                            if((mimde->problema).maquina != -1)
                                                printf("maquina %d\n",(mimde->problema).maquina); 
                                            else
                                                printf("Nenhuma maquina anexada.\n"); 
                                            if((mimde->problema).defeito != -1)                    
                                                printf("\n%d\n",top_pop_int(mimde));
                                            else{   
                                                printf("\n%s\n",(mimde->problema).outro);
                                                pop(mimde);
                                            } 
                                            
                                    }
                                    retirar_chamado(fc);
                                }*/
                            fpause2();
                            break;
                        case 2: //Cadastrar novo(s) problema(s) (chamado atual).
                            if(fc->INICIO){
                                do{
                                    option=menu_problema();
                                    if(option){
                                        push(&(fc->FIM->chamado),option);
                                        printf("Problema cadastrado com sucesso!. \n");
                                        fpause2();
                                    }
                                }while(option);
                                
                            }else{
                                printf("Nenhum chamado pendente/cadastrado!. \n");
                            }
                            fpause2();
                            break;
                        case 3:  //novo chamado.\n
                            cabecalho();
                            printf("Novo chamado. \n");
                            aux = 0;
                            do{
                                option=menu_problema();
                                if(option){
                                    if(!aux){
                                        inserir_chamado(fc); //prepara o nodo pra receber os chamados
                                    }   
                                    push(&(fc->FIM->chamado),option);
                                    printf("Problema cadastrado com sucesso!. \n");
                                    fpause2();
                                    aux = 1;
                                }
                            }while(option);
                            if(aux){
                                printf("Chamado cadastrado com sucesso!. \n");
                                fpause2(); 
                            }
                            break;
                        case 4: 
                            printf("teste:\n");
                            if(!eh_vazia_fila(fc)){
                                printf(" Contador de problemas atual :%d  \n",(fc->INICIO)->chamado->contador);
                                printf(" Contador de problemas next:%d \n",((fc->INICIO)->next)->chamado->contador);
                            
                                /*muda((fc->INICIO)->chamado);
                                printf("muda\nproblm chamado atual :%d  \n",(fc->INICIO)->chamado->problema.defeito);
                                printf("problm chamado next:%d \n",((fc->INICIO)->next)->chamado->problema.defeito);
                                
                                muda2(&((fc->INICIO)->chamado));
                                printf("muda*\nproblm chamado atual :%d  \n",(fc->INICIO)->chamado->problema.defeito);
                                printf("problm chamado next:%d \n",((fc->INICIO)->next)->chamado->problema.defeito);
                            */}
                            else
                            	printf("no ten nada manito:\n");


                            
                            fpause2();
                            break;
                        default:
                            printf("Opcao invalida! \n");
                    }
                }while(option2);	
            break;
            case 2:  //opcoes e base de dados
                fpause2();
                break;

            case 0:
                printf("Sistema finalizado. \n");
                fpause2();               
            break;
            default:
                    printf("Opcao invalida\n");
                    fpause2();  
        }
        rodar=menu_principal();
    }

   
    fpause2();
}

//-------------------- Pilha ------------------------//

void cria_pilha(CHAMADO *pc){
    *pc=NULL;
    //return pc;
}

void push (CHAMADO *pp, int op){
    NODO_PILHA * novo;
    int aux;
    novo = (NODO_PILHA*)malloc (sizeof(NODO_PILHA));
    if (!novo){
        printf ("\nERRO! Memoria insuficiente!\n");
        exit (1);
    }
    if(op==8){
        (novo->problema).defeito=-1;    
        printf("Qual o problema? Descreva-o sucintamente.\n\n");
        
        setbuf(stdin,NULL);
        fflush(stdin);
        scanf("%99[^\n]",(novo->problema).outro);
    }else{
        (novo->problema).outro[0]='\0';                                   
        (novo->problema).defeito = op;
    }
    printf("Anexar um computador ao problema?. (S ou N) \n\n");
    do{
        aux = chrpergunta();
        if((aux) && aux != -1){
            printf("Informe o ID do computador : \n");
            scanf("%d",&((novo->problema).maquina));   
        }else if(!aux){
            (novo->problema).maquina = -1;
        }else{
            printf("Opcao invalida! \n");   //colocar while
            (novo->problema).maquina = -1;
        }   
    }while(aux == -1);
    if(!*pp)	
        novo->contador = 1;
    else
        novo->contador = (*pp)->contador + 1;
    novo->next = *pp;
    *pp=novo;
    printf("novo->contador: %d\n",novo->contador);
}

int eh_vazia_pilha (CHAMADO c){
    return (!c);
}

int pop (CHAMADO *c){
    if (eh_vazia_pilha(*c)){
        printf ("\nERRO! Retirada em pilha vazia!\n");
        exit (3);
    }else{
        NODO_PILHA *aux=*c;
        *c=(*c)->next;
        free (aux);
        //return c;
    }
}

CHAMADO zerarPilha(CHAMADO c){
    while(!eh_vazia_pilha(c))
            pop(&c);
    c = NULL;
    return c;
}

PROBLEMA top (CHAMADO c){
    if (eh_vazia_pilha(c)){
        printf ("\nERRO! Consulta e retirada em pilha vazia!\n");
        fpause2();
    }else{
        return (c->problema);
    }
}

PROBLEMA top_pop (CHAMADO *c) {
    if (eh_vazia_pilha(*c)){
        printf ("\nERRO! Consulta e retirada em pilha vazia!\n");
        exit (4);
    }else{
        PROBLEMA problm=(*c)->problema;
        NODO_PILHA *aux=*c;
        *c=(*c)->next;
        free (aux);
        return (problm);
    }
}

//-------------------- fila ------------------------//
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

void inserir_chamado (FILA_DE_CHAMADOS fc) {
    NODO_FILA *novo;
    novo = (NODO_FILA *) malloc (sizeof(NODO_FILA));
    if (!novo){
        printf ("\nERRO! Memoria insuficiente!\n");
        exit (1);
    }
    novo->chamado = NULL;
    novo->next = NULL;
    if (eh_vazia_fila(fc)){
        fc->INICIO=novo;
        fc->qtd = 1;
    }else{
        fc->FIM->next=novo;
        fc->qtd++;
    }
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
 
 
//--------------------------------Funcoes auxiliares--------------------------------//

int menu_programa(){
    int escolha;
    do{
        cabecalho();
        printf("Digite:\n");
        printf("1- Chamado atual.\n");
        printf("2- Cadastrar novo(s) problema(s) (chamado atual).\n");
        printf("3- Para fazer um novo chamado.\n");
        printf("4- teste contadores.\n");
        printf("\n0- Voltar.\n");
        scanf("%d", &escolha);
        if(escolha < 0 || escolha > 4){
            printf("Opcao invalida\n");
            fpause2();
        }
            
    }while (escolha < 0 || escolha > 4);
    return escolha;
}
int menu_principal(){
    int escolha;
    do{
        cabecalho();
        printf("Informe o modo: \n");
        printf("1- Resolucao de problemas.\n");
        printf("2- Opcoes e base de dados.\n");
        //printf("3- Opcoes e cadastros.\n");
        printf("\n0 - Finalizar programa.\n");
        
        setbuf(stdin,NULL);
        fflush(stdin); 

        scanf("%d", &escolha);
        if(escolha < 0 || escolha > 3){
            printf("Opcao invalida\n");
            fpause2();
        }
    }while (escolha < 0 || escolha > 3);
    return escolha;
}




int menu_problema(){
    int trouble;
    do{
        cabecalho();
        printf("\n\nCADASTRO DE PROBLEMAS:\n\n");
        printf("Digite o numero que melhor descreve o problema: \n");
        printf("1- Se o computador nao liga.\n");
        printf("2- Se o computador liga,mas nao aparece algum erro no monitor.\n");
        printf("3- Se esta ocorrendo algum problema na instalacao de algum programa.\n");
        printf("4- Se algum periferico nao esta funcionando de forma adequada.\n");
        printf("5- Se o computador congela de forma repentina.\n");
        printf("6- Se alguma senha nao estiver funcionando.\n");
        printf("7- Se a internet nao esta funcionando.\n");
        printf("8- Se for outro problema.\n");
        printf("\n0- Voltar / Inserir chamado na base de dados.\n");
    
        setbuf(stdin,NULL);
        fflush(stdin); 
        scanf("%d",&trouble);
        if(trouble<0 || trouble>8){
            printf("Opcao invalida\n");
            fpause2();
        }
            
   }while(trouble<0 || trouble>8);	
    return trouble;
}

int chrpergunta(){
    char aux;
    setbuf(stdin,NULL);
    fflush(stdin);
    scanf("%c",&aux);

    if((aux == 's') || (aux == 'S')){
        return 1;
    }else if((aux == 'n') || (aux == 'N')){
        return 0;
    }else{
        return -1;
    }   
}

void fpause2(){                     
    setbuf(stdin,NULL);
    fflush(stdin);
    printf("Pressione alguma tecla pra continuar... \n");
    getchar();
}
void cabecalho(){
    system("clear || cls");
    printf("------------------------------------------------------\n");
    printf("\t\t\tHELP DESK\n");
    printf("------------------------------------------------------\n\n");
}
