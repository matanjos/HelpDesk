#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int maquina; //adicionei , caso problema nao seja relacionado uma maquina eh -1(fica -1 no push);
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
int menu_problema();
int menu_principal();
int chrpergunta();
void fpause2();

//---------pilha---------
CHAMADO push (CHAMADO, int);
CHAMADO cria_pilha(CHAMADO);
CHAMADO pop (CHAMADO);
int eh_vazia_pilha (CHAMADO);
PROBLEMA top (CHAMADO);
//---------fila---------
FILA_DE_CHAMADOS cria_fila (FILA_DE_CHAMADOS);
FILA_DE_CHAMADOS inserir_chamado (FILA_DE_CHAMADOS, CHAMADO);
FILA_DE_CHAMADOS retirar_chamado (FILA_DE_CHAMADOS);
int eh_vazia_fila (FILA_DE_CHAMADOS);
CHAMADO cons (FILA_DE_CHAMADOS);
CHAMADO cons_ret (FILA_DE_CHAMADOS);


//------------------------------------------------------------------------//

int main(){ 
    FILA_DE_CHAMADOS fc;
    CHAMADO mimde;
	PROBLEMA problm;
    int option,option2,rodar,aux;
    mimde = cria_pilha(mimde);
    fc = cria_fila(fc);  
    cabecalho();
    rodar=menu_principal();

    while(rodar != 9){ 
        switch(rodar){
            case 1:
                do{
                    option2=menu_programa();
                    switch(option2){
						case 0:
							break;
						case 1:

							break;
						case 2:
							do{
								option=menu_problema();
								if(option)
									mimde = push(mimde,option);
							}while(option);

							problm = top(mimde);
							printf("teste id probl %d \n",problm.defeito);
							/*do{
								printf("Deseja inserir na base ? (S ou N) \n");
							}while()
							*/
							fpause2();
							break;
						case 3:
							cabecalho();
							printf("Novo chamado. \n");
							do{
								option=menu_problema();
								if(option)
									push(mimde,option);
							}while(option);
							inserir_chamado(fc,mimde);
							printf("Chamado cadastrado com sucesso!. \n");
							fpause2(); 
							break;
						default:
							printf("Opcao invalida! \n");
					}
                }while(option2);	
            break;
            case 2:
           		break;

            case 9:
                printf("Sistema finalizado. \n");
                fpause2();               
            break;
            default:
                    printf("Opcao invalida\n");
                    fpause2();  
        
        }

        
        rodar=menu_principal();
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
    system("pause");
}

//------------------------------------------------------------------------//

int menu_programa(){
    int escolha;
    do{
        cabecalho();
        printf("Digite:\n");
        printf("1- Chamado atual.\n");
        printf("2- Cadastrar novo(s) problema(s) (chamado atual).\n");
        printf("3- Para fazer um novo chamado.\n");
        printf("\n0- Voltar.\n");
        scanf("%d", &escolha);
    }while (escolha < 0 || escolha > 3);
    return escolha;
}
int menu_principal(){
    int escolha;
    do{
        cabecalho();
        printf("Informe o modo: \n");
        printf("1- Resolucao de problemas.\n");
        printf("2- Opcoes e cadastros.\n");
        //printf("3- Opcoes e cadastros.\n");
        printf("\n0 - Finalizar programa.\n");
        scanf("%d", &escolha);
    }while (escolha < 0 || escolha > 9);
    return escolha;
}

int menu_problema(){
	int trouble;
	do{
	    cabecalho();
		printf("Digite:\n");
		printf("1- Se o computador nao liga.\n");
		printf("2- Se o computador liga,mas nao aparece algum erro no monitor.\n");
		printf("3- Se esta ocorrendo algum problema na instalacao de algum programa.\n");
		printf("4- Se algum periferico nao esta funcionando de forma adequada.\n");
		printf("5- Se o computador congela de forma repentina.\n");
		printf("6- Se alguma senha nao estiver funcionando.\n");
		printf("7- Se a internet nao esta funcionando.\n");
		printf("8- Se for outro problema.\n");
		printf("\n0- Inserir na base de dados.\n");
		scanf("%d",&trouble);
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

CHAMADO cria_pilha(CHAMADO pc){
	pc=NULL;
	return pc;
}

CHAMADO push (CHAMADO pp, int op){
    CHAMADO novo;
    int aux;
    novo = (CHAMADO) malloc (sizeof(NODO_PILHA));
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

    novo->next = pp;
    pp=novo;
	return pp;
}

int eh_vazia_pilha (CHAMADO c){
    return (!c);
}

CHAMADO pop (CHAMADO c){
    if (eh_vazia_pilha(c)){
        printf ("\nERRO! Retirada em pilha vazia!\n");
        exit (3);
    }else{
        NODO_PILHA *aux=c;
        c=(c)->next;
        free (aux);
		return c;
    }
}

PROBLEMA top (CHAMADO c){
	if (eh_vazia_pilha(c)){
        printf ("\nERRO! Consulta e retirada em pilha vazia!\n");
        exit (4);
    }else{
		return (c->problema);
	}
}
/*
int top_pop_int (CHAMADO c) {
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
*/
FILA_DE_CHAMADOS cria_fila (FILA_DE_CHAMADOS fc){
    fc=(DESCRITOR *)malloc(sizeof(DESCRITOR));
    if (!fc){
        printf ("\nERRO! Memoria insuficiente!\n");
        exit (1);
    }
    fc->INICIO=fc->FIM=NULL;
	return fc;
}

int eh_vazia_fila (FILA_DE_CHAMADOS fc){
    return (fc->INICIO == NULL);
}

FILA_DE_CHAMADOS inserir_chamado (FILA_DE_CHAMADOS fc, CHAMADO c) {
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
	return fc;
}

CHAMADO cons (FILA_DE_CHAMADOS fc){
    if (eh_vazia_fila(fc)){
        printf ("\nERRO! Consulta em fila vazia!\n");
        exit (2);
    }else
        return (fc->INICIO->chamado);
}

FILA_DE_CHAMADOS retirar_chamado (FILA_DE_CHAMADOS fc) {
    if (eh_vazia_fila(fc)){
        printf ("\nERRO! Retirada em fila vazia!\n");
        exit (3);
    }else{
        NODO_FILA *aux=fc->INICIO;
        fc->INICIO=fc->INICIO->next;
        if (!fc->INICIO)
        fc->FIM=NULL;
        free (aux);
		return fc;
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


