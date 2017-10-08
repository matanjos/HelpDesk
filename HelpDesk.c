#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<math.h>

//-----------geral-----------//
typedef struct{
    int maquina; 
    int defeito;
    char outro[100];
}PROBLEMA;

typedef struct net{
    unsigned char dig1;
    unsigned char dig2;
    unsigned char dig3;
    unsigned char dig4;
}IP;

typedef struct maquin{
    unsigned int id;
    char marca[30];
    char modelo[30];
    char SO[30];
    char estado;
    IP ip;
}MAQUINA;

//-----------pilha-----------//

typedef struct nodo_pilha{
    PROBLEMA problema;
    int contador;
    struct nodo_pilha * next;
}NODO_PILHA;

typedef NODO_PILHA * CHAMADO;

void push (CHAMADO *, int);
void cria_pilha(CHAMADO *);
void pop (CHAMADO *);
int eh_vazia_pilha (CHAMADO);
PROBLEMA top (CHAMADO);

//-----------fila-----------//
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

void cria_fila (FILA_DE_CHAMADOS *);
void inserir_chamado (FILA_DE_CHAMADOS);
void retirar_chamado (FILA_DE_CHAMADOS);
int eh_vazia_fila (FILA_DE_CHAMADOS);

CHAMADO cons (FILA_DE_CHAMADOS);

//-----------arvore-----------//

typedef struct node {
    MAQUINA pc;
    struct node *left;
    struct node *right;
}NODE_ARV;

typedef NODE_ARV * ARV_BIN_ENC;


ARV_BIN_ENC maketree(ARV_BIN_ENC, MAQUINA);
ARV_BIN_ENC ins_ele(ARV_BIN_ENC, MAQUINA);
ARV_BIN_ENC left(ARV_BIN_ENC);
ARV_BIN_ENC right(ARV_BIN_ENC);
ARV_BIN_ENC pesqID(ARV_BIN_ENC, int);
ARV_BIN_ENC remocaoPorCopia(ARV_BIN_ENC,int);
ARV_BIN_ENC alterarCad(ARV_BIN_ENC);
ARV_BIN_ENC rotacao_direita(ARV_BIN_ENC);
ARV_BIN_ENC rotacao_esquerda(ARV_BIN_ENC);
ARV_BIN_ENC EspinhaDorsal(ARV_BIN_ENC);
ARV_BIN_ENC balancearDorsal(ARV_BIN_ENC);
ARV_BIN_ENC ALGORITMODSW(ARV_BIN_ENC);


void listarNo(ARV_BIN_ENC);
void InOrdem(ARV_BIN_ENC);
int conta_nodoright(ARV_BIN_ENC);   
int conta_nodoleft(ARV_BIN_ENC);   

//---------------------geral------------------
MAQUINA lerinfos(MAQUINA);

void cabecalho();
int menu_programa();
int menu_problema();
int menu_chamado();
int menu_principal();
int menu_arvbin();
int menu_alterarCad();
int chrpergunta();
void problemaDec(int);
void fpause2();
double Log2 (double);

//----------------------------------MAIN---------------------------------//

int main(){ 
    FILA_DE_CHAMADOS fc;
    PROBLEMA problm;
    ARV_BIN_ENC info = NULL,arvaux = NULL;
    MAQUINA computador;
    int menu,option,option2,option3,rodar,aux,contpc = 0,contpcTOTAL = 0;
    cria_fila(&fc);  
    cabecalho();
    do{
        rodar=menu_principal();
        switch(rodar){
            case 0:   
                printf("Sistema Finalizado.\n");
                fpause2();          
                break;

            case 1:   //resolucao de problemas
                do{
                    option2=menu_programa();    // 1 - chamado atual, 2 - Fazer novo chamado, 3 - informacoes gerais
                    switch(option2){
                        case 0: //voltar
                            break;

                        case 1: //chamado atual (mostrar as infos , problema atual,qtd de problemas no chamado e perguntar se quer resolver)
                             if(fc->INICIO){
                                do{
                                    cabecalho();
                                    problm = top(cons(fc));
                                    printf("RESOLUCAO DE PROBLEMAS:\n"); 
                                    
                                    if(problm.defeito != -1){
                                        printf("\nProblema: ");
                                        problemaDec(problm.defeito);
                                    }                 
                                    else  
                                        printf("\nProblema: %s\n",problm.outro);

                                    if(problm.maquina != -1){
                                        arvaux = pesqID(info, problm.maquina);
                                        if(!arvaux){
                                            printf("Computador anexado: ID %d\n",problm.maquina); 
                                            printf("Computador ainda nao cadastrado na base de dados! \n");
                                        }else
                                            listarNo(arvaux);
                                    }else
                                        printf("Nenhuma maquina anexada.\n"); 
                                    
                                    printf("\nResolver problema?. (S ou N)\n");
                                    aux = chrpergunta();
                                    if((aux) && aux != -1){
                                        pop(&(fc->INICIO->chamado)); 
                                        cabecalho();
                                        printf("Sucesso!\n"); 
                                        if(eh_vazia_pilha(cons(fc))){
                                            retirar_chamado(fc);
                                            printf("Problemas resolvidos - Chamado finalizado. \n");
                                            if(!eh_vazia_fila(fc)){
                                                printf("Ir para o proximo chamado? (S ou N) \n");
                                                aux = chrpergunta();
                                            }else{
                                                printf("Todos os chamados foram finalizados!\n");
                                                aux = 0;
                                            }
                                        }
                                    }
                                }while(aux);
                            }else{
                                printf("Sem chamados cadastrados! \n");
                            }
                            fpause2();
                            break;

                        case 2: //Cadastrar novo chamado.
                            cabecalho();
                            printf("Novo chamado. \n");
                            aux = 0;
                            do{
                                option=menu_problema();
                                if(option){
                                    if(!aux)
                                        inserir_chamado(fc); //prepara o nodo pra receber os chamados
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

                        case 3:   //info gerais
                            cabecalho();
                            printf("INFORMACOES GERAIS:\n\n");
                            if(!eh_vazia_fila(fc)){
                                printf("Numero de problemas do chamado atual :%d\n",(cons(fc)->contador));
                                printf("Numero de chamados abertos:%d \n",(fc->qtd));
                            }else
                            	printf("Nenhum chamado cadastrado.\n");
                            if(contpcTOTAL)
                                printf("Numero de computadores cadastrados: %d\n",contpcTOTAL);
                            else
                            	printf("Nenhum computador cadastrado.\n");

                            fpause2();
                            break;

                        default:
                            printf("Opcao invalida! \n");
                    }
                }while(option2);	
            break;

            case 2:  //opcoes e base de dados (arvore)
                do{
                    cabecalho();
                    menu = menu_arvbin();
                    switch(menu){
                        case 0: //VOLTAR
                            break;

                        case 1: //CADASTRAR PC
                                cabecalho();
                                computador =lerinfos(computador); 
                                arvaux = pesqID(info,computador.id);
                                if(arvaux){
                                    printf("ERRO! ID ja encontrado na Base de dados!\n");
                                }else{
                                    info = ins_ele(info,computador);
                                    contpc++;
                                    contpcTOTAL++;
                                    printf("Computador cadastrado com sucesso!\n");
                                    if(contpc == 8){
                                        info = ALGORITMODSW(info);
                                        printf("Base otimizada automaticamente.\n");
                                        contpc = 0;
                                    }
                                }
                                fpause2();
                            break;

                        case 2: //LISTAR MAQUINAS EM ORDEM ID
                                InOrdem(info);
                                fpause2();
                            break;

                        case 3: //REMOVERPC
                                printf("Informe o ID a ser removido: \n");
                                scanf("%d",&aux);
                                arvaux = pesqID(info,aux);
                                if(arvaux){
                                    info = remocaoPorCopia(info, aux);
                                    printf("Removido com sucesso!\n");
                                    contpcTOTAL--;
                                }else{
                                    printf("ID nao encontrado na base de dados!\n");
                                }
                                fpause2();
                            break;

                        case 4: //ALTERAR CADASTRO
							printf("ALTERAR CADASTRO:\n\n");
							printf("Informe o ID: \n");
                                scanf("%d",&aux);
                                arvaux = pesqID(info, aux);
                                if(!arvaux)
                                    printf("ID nao encontrado! \n");
                                else
                                    arvaux = alterarCad(arvaux);
                                fpause2();  
                            break;

                        case 5: //PESQUISAR ID
                                printf("Informe o ID a ser procurado: \n");
                                scanf("%d",&aux);
                                arvaux = pesqID(info, aux);
                                if(!arvaux)
                                    printf("ID nao encontrado! \n");
                                else
                                    listarNo(arvaux);
                                fpause2();   
                            break;

                        case 6: //OTIMIZAR BASE(ALGORITMO DSW)
                                if(info){
                                    info = ALGORITMODSW(info);
                                    printf("Base otimizada com sucesso!\n");
                                }else
                                    printf("Base de dados vazia!\n");
                                fpause2();
                            break;

                        case 7: //FUNCAO PRA TESTES(CONTAR ATE O FILHO MAIS A ESQUERDA/DIREITA DA RAIZ)
                                arvaux = info;
                                printf("Nodos ate filho mais a esq: %d, mais a direita : %d\n",conta_nodoleft(arvaux)-1, conta_nodoright(arvaux)-1);
                                fpause2();
                            break;

                        default: 
                                printf("Opcao invalida\n");
                                fpause2();   
                    }
                }while(menu);
                break;

            default:
                    printf("Opcao invalida\n");
                    fpause2();  
        }
    }while(rodar);
    return (0);
}

//-------------------- Pilha ------------------------//

void cria_pilha(CHAMADO *pc){
    *pc=NULL;
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
        printf("Qual o problema? Descreva-o sucintamente.\n");
        
        setbuf(stdin,NULL);
        fflush(stdin);
        scanf("%99[^\n]",(novo->problema).outro);
    }else{
        (novo->problema).outro[0]='\0';                                   
        (novo->problema).defeito = op;
    }
    printf("Anexar um computador ao problema?. (S ou N) \n");
    do{
        aux = chrpergunta();
        if(aux == 1){
            printf("Informe o ID do computador : \n");
            scanf("%d",&((novo->problema).maquina));   
        }else if(!aux){
            (novo->problema).maquina = -1;
        }else{
            printf("Opcao invalida! \n");  
        }   
    }while(aux == -1);
    if(!*pp)	
        novo->contador = 1;
    else
        novo->contador = (*pp)->contador + 1;
    novo->next = *pp;
    *pp=novo;
}

int eh_vazia_pilha (CHAMADO c){
    return (!c);
}

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

PROBLEMA top (CHAMADO c){
    if (eh_vazia_pilha(c)){
        printf ("\nERRO! Consulta e retirada em pilha vazia!\n");
    }else{
        return (c->problema);
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

void inserir_chamado (FILA_DE_CHAMADOS fc){
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

void retirar_chamado (FILA_DE_CHAMADOS fc){
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

//--------------------------------Arvore--------------------------------//

ARV_BIN_ENC maketree(ARV_BIN_ENC arv, MAQUINA comp){
	arv = (ARV_BIN_ENC) malloc (sizeof (NODE_ARV));
    if (!(arv)){
        printf("Memoria nao alocada!");
        exit(1);
    }
    (arv)->pc = comp;
    (arv)->left = NULL;
    (arv)->right = NULL;
    return arv;
}

ARV_BIN_ENC ins_ele(ARV_BIN_ENC arv, MAQUINA comp){ 
    if (!(arv)){
        return maketree(arv,comp);
    }
    if ((comp.id) < ((arv->pc).id))
        (arv)->left = ins_ele(arv->left, comp);
    else
        (arv)->right = ins_ele(arv->right, comp);
    return(arv);
}

ARV_BIN_ENC remocaoPorCopia(ARV_BIN_ENC arvore,int id) {
    if(!arvore)
        return arvore;
    if (id < (arvore->pc).id)
        arvore->left = remocaoPorCopia(arvore->left, id);
    else if (id > (arvore->pc).id)
        arvore->right = remocaoPorCopia(arvore->right, id);
    else{
        ARV_BIN_ENC tmp= arvore, father;
        if ((arvore)->right == NULL){
            arvore = (arvore)->left;
            free (tmp);
            return arvore;
        }else if ((arvore)->left == NULL){
            arvore = (arvore)->right;
            free (tmp);
            return arvore;
        }
            tmp = (arvore)->left;
            father = arvore;
            while (tmp->right!=NULL) {
                father = tmp;
                tmp = tmp->right;
            }
            (arvore)->pc = tmp->pc;
            if (father==arvore)
                father->left = tmp->left;
            else
                father->right = tmp->left;
            free (tmp);
    }
        return arvore;
}

ARV_BIN_ENC alterarCad(ARV_BIN_ENC arvore) {
	int aux;
    if(!arvore)
        return arvore;
    do{
		cabecalho();
		printf("MAQUINA: \n");
		listarNo(arvore);
		aux = menu_alterarCad();
		
		switch(aux){
			case 0://voltar
				break;

			case 1: //marca
				printf("Marca atual: %s\n",((arvore)->pc).marca);
				
				setbuf(stdin,NULL);
				fflush(stdin);
				printf("Informe a Marca: ");
				scanf("%29[^\n]",(arvore)->pc.marca);
				fpause2();
				break;

			case 2://modelo
				printf("Modelo atual: %s\n",((arvore)->pc).modelo);

				setbuf(stdin,NULL);
				fflush(stdin);
				printf("Informe o modelo: ");
				scanf("%29[^\n]",((arvore)->pc).modelo);
				fpause2();
				break;

			case 3://SO
				printf("Sistema Operacional atual: %s\n",((arvore)->pc).SO);
				setbuf(stdin,NULL);
				fflush(stdin);
				printf("Informe o Sistema Operacional: ");
				scanf("%29[^\n]",((arvore)->pc).SO);
				fpause2();
				break;

			case 4://ESTADO 
				printf("Estado atual da Maquina: ");
				if(((arvore->pc).estado == 'M') || ((arvore->pc).estado == 'm'))
					printf("M - Manutencao.\n");
				else if(((arvore->pc).estado == 'B') || ((arvore->pc).estado == 'b'))
					printf("B - Bom estado / Em uso.\n");
				else
					printf("D - Deposito.\n");
				
				setbuf(stdin,NULL);
				fflush(stdin);
				printf("Informe o novo estado da maquina: \nM - Manutencao. \n B - Bom estado/em uso. \n D - Deposito. \n");
				scanf("%c",&(arvore->pc).estado);
				
				fpause2();
				break;

			case 5://IP
				printf("IP: %d.%d.%d.%d \n", ((arvore)->pc).ip.dig1, ((arvore)->pc).ip.dig2, ((arvore)->pc).ip.dig3, ((arvore)->pc).ip.dig4);

				setbuf(stdin,NULL);
				fflush(stdin);
				printf("Informe o Novo IP da maquina: (0 a 255, com espacos)Ex: 192 168 0 20 \n");
				scanf("%d %d %d %d", &((arvore)->pc).ip.dig1, &((arvore)->pc).ip.dig2, &((arvore)->pc).ip.dig3, &((arvore)->pc).ip.dig4);
				fpause2();
				break;
		}
	}while(aux);
        return arvore;
}



ARV_BIN_ENC rotacao_direita(ARV_BIN_ENC arvore){
    ARV_BIN_ENC aux1, aux2;
    aux1 = (arvore)->left;        
    aux2 = aux1->right;
    (arvore)->left = aux2;
    aux1->right = (arvore);
    arvore = aux1;
    return(arvore);
}

ARV_BIN_ENC rotacao_esquerda(ARV_BIN_ENC arvore){
    ARV_BIN_ENC aux1, aux2;
    aux1 = (arvore)->right;        
    aux2 = aux1->left;
    (arvore)->right = aux2;
    aux1->left = (arvore);
    arvore = aux1;
    return(arvore);
}

ARV_BIN_ENC EspinhaDorsal(ARV_BIN_ENC arvore){
    ARV_BIN_ENC tmp,father, ant;
    int aux = 1;
    father = tmp = ant = arvore;
    while(tmp){
        if(tmp->left){
            tmp = rotacao_direita(tmp);
            
            if(aux)
                father = tmp;  
            else
                ant->right = tmp;
        }else{
            aux = 0;
            ant = tmp;
            tmp = tmp->right;
        }
    }
    
    return father;
}

ARV_BIN_ENC balancearDorsal(ARV_BIN_ENC arvore){
    int n = conta_nodoright(arvore), m, i;
    ARV_BIN_ENC aux = arvore,aux2;
    m = (pow(2,floor(Log2(n+1))))-1;
    for(i=0 ; i<(n-m) ; i++){
        if(!i){
            aux = rotacao_esquerda(arvore);
            arvore = aux;
            aux2= arvore;
        }else{
            aux = rotacao_esquerda(aux->right);
            aux2->right = aux;
            aux2 = aux2->right;
        }
    }
    while(m>1){
        m = m/2;
        aux = rotacao_esquerda(arvore);
        arvore = aux2 = aux;
        for(i=0;i< m-1;i++){
            aux = rotacao_esquerda(aux->right);
            aux2->right = aux;
            aux2 = aux2->right;
        }
    }
    
    return aux;
}

ARV_BIN_ENC ALGORITMODSW(ARV_BIN_ENC arvore){
    if(arvore)
        return balancearDorsal(EspinhaDorsal(arvore)); 
    return NULL;
}

ARV_BIN_ENC pesqID(ARV_BIN_ENC arv, int id){
    while(arv){
        if (id < ((arv->pc).id)){
            arv = arv->left;    
        }else{
            if(id == ((arv->pc).id)){   
                return arv;
                break;
            }
            arv = arv->right;
        }
    }
        return NULL;
}

ARV_BIN_ENC left(ARV_BIN_ENC arv){
    return arv->left;
}
ARV_BIN_ENC right(ARV_BIN_ENC arv){
    return arv->right;
}
void InOrdem(ARV_BIN_ENC arv) {
    if (arv) {
        InOrdem(left(arv)); 
        listarNo(arv);
        InOrdem(right(arv)); 
    }
}

void listarNo(ARV_BIN_ENC arv){
    printf("\n-----------------------------------------------------------------------\n");
    printf("Numero de Serie (ID): %d\n\n",((arv)->pc).id);
    printf("Marca: %s\n",((arv)->pc).marca);
    printf("Modelo: %s\n",((arv)->pc).modelo);
    printf("Sistema Operacional: %s\n",((arv)->pc).SO);
    printf("Estado da Maquina: ");
    if(((arv->pc).estado == 'M') || ((arv->pc).estado == 'm'))
        printf("M - Manutencao.\n");
    else if(((arv->pc).estado == 'B') || ((arv->pc).estado == 'b'))
        printf("B - Bom estado / Em uso.\n");
    else
         printf("D - Deposito.\n");
    printf("IP: %d.%d.%d.%d \n", ((arv)->pc).ip.dig1, ((arv)->pc).ip.dig2, ((arv)->pc).ip.dig3, ((arv)->pc).ip.dig4);

    printf("\n-----------------------------------------------------------------------\n");
}


//--------------------------------Funcoes auxiliares--------------------------------//

int menu_programa(){
    int escolha;
    do{
        cabecalho();
        printf("Digite:\n");
        printf("1- Chamado atual.\n");
        printf("2- Cadastrar um novo chamado.\n");
        printf("3- Informacoes Gerais.\n");
        printf("\n0- Voltar.\n");

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

int menu_alterarCad(){
    int escolha;
    do{
        printf("Oque deseja alterar ?:\n");
        printf("1- Marca.\n");
        printf("2- Modelo.\n");
        printf("3- Sistema Operacional.\n");
        printf("4- Estado da Maquina.\n");
        printf("5- IP.\n");
        printf("\n0- Voltar.\n");

        setbuf(stdin,NULL);
        fflush(stdin);

        scanf("%d", &escolha);
        if(escolha < 0 || escolha > 5){
            printf("Opcao invalida\n");
            fpause2();
        }
            
    }while (escolha < 0 || escolha > 5);
    return escolha;
}

int menu_chamado(){
    int escolha;
    do{
        cabecalho();
        printf("1- Resolucao de problemas.\n");
        printf("2- Maquina anexada.\n");
        printf("\n0- Voltar.\n");

        setbuf(stdin,NULL);
        fflush(stdin);

        scanf("%d", &escolha);

        if(escolha < 0 || escolha > 2){
            printf("Opcao invalida\n");
            fpause2();
        }
            
    }while (escolha < 0 || escolha > 2);
    return escolha;
}

int menu_principal(){
    int escolha;
    do{
        cabecalho();
        printf("Informe o modo: \n");
        printf("1- Resolucao de problemas.\n");
        printf("2- Opcoes e base de dados.\n");
        printf("\n0 - Finalizar programa.\n");
        
        setbuf(stdin,NULL);
        fflush(stdin); 

        scanf("%d", &escolha);
        if(escolha < 0 || escolha > 2){
            printf("Opcao invalida\n");
            fpause2();
        }
    }while (escolha < 0 || escolha > 3);
    return escolha;
}

int menu_arvbin(){
    int escolha;
    do{
        cabecalho();
        printf("1 - Cadastrar computador.\n");
        printf("2 - Listar maquinas por ordem crescente de ID. \n");
        printf("3 - Remover computador. \n");
        printf("4 - Alterar Cadastro. \n");
        printf("5 - Pesquisar por ID. \n");
        printf("6 - Otimizar Base de dados. (ALGORITMO DSW) \n");
        printf("7 - Numero de nodos ate o filho mais a esquerda/direita. (COMPARACAO DSW)\n");
        printf("\n0 - Voltar \n");
        
        setbuf(stdin,NULL);
        fflush(stdin); 

        scanf("%d", &escolha);
        if(escolha < 0 || escolha > 7){
            printf("Opcao invalida\n");
            fpause2();
        }
    }while (escolha < 0 || escolha > 7);
    return escolha;
}

void problemaDec(int cod){
    switch(cod){
        case 1:
            printf("O computador nao liga.\n");
            break;
        case 2:
            printf("O computador liga,mas aparece algum erro no monitor.\n");
            break;
        case 3:
            printf("Esta ocorrendo algum problema na instalacao de algum programa.\n");
            break;
        case 4:
            printf("Algum periferico nao esta funcionando de forma adequada.\n");
            break;
        case 5:
            printf("O computador congela de forma repentina.\n");
            break;
        case 6:
            printf("Alguma senha nao esta funcionando.\n");
            break;
        case 7:
            printf("A internet nao esta funcionando.\n");
            break;
    }
}

int menu_problema(){
    int trouble;
    do{
        cabecalho();
        printf("CADASTRO DE PROBLEMAS:\n\n");
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

MAQUINA lerinfos(MAQUINA pc){
    printf("CADASTRO DE MAQUINA: \n\n");

    printf("Informe o Numero de Serie (ID): ");
    scanf("%d",&pc.id);

    setbuf(stdin,NULL);
    fflush(stdin);
    printf("Informe a Marca: ");
    scanf("%29[^\n]",pc.marca);
    
    setbuf(stdin,NULL);
    fflush(stdin);
    printf("Informe o modelo: ");
    scanf("%29[^\n]",pc.modelo);
    
    setbuf(stdin,NULL);
    fflush(stdin);
    printf("Informe o Sistema Operacional: ");
    scanf("%29[^\n]",pc.SO);
    
    setbuf(stdin,NULL);
    fflush(stdin);
    printf("Informe o estado atual da maquina: \nM - Manutencao. \n B - Bom estado/em uso. \n D - Deposito. \n");
    scanf("%c",&(pc).estado);
    
    setbuf(stdin,NULL);
    fflush(stdin);
    printf("Informe o IP da maquina: (0 a 255, com espacos)Ex: 192 168 0 20 \n");
    scanf("%d %d %d %d", &(pc.ip).dig1, &(pc.ip).dig2, &(pc.ip).dig3, &(pc.ip).dig4);

    return pc;
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

double Log2(double v){  
    // logaritmo na base 2
    return (log(v)/log(2));  
}
int conta_nodoright(ARV_BIN_ENC arvaux){
    int aux ;
    for(aux = 0;arvaux; ++aux, arvaux=arvaux->right);
    return (aux);  
}
int conta_nodoleft(ARV_BIN_ENC arvaux){
    int aux ;
    for(aux = 0;arvaux; ++aux, arvaux=arvaux->left);
    return (aux);
}

void fpause2(){                     
    setbuf(stdin,NULL);
    fflush(stdin);
    printf("Pressione alguma tecla pra continuar... \n");
    getchar();
}
void cabecalho(){
    system("clear || cls");
    printf("-----------------------------------------------------------------------\n");
    printf("\t\t\t\tHELP DESK\n");
    printf("-----------------------------------------------------------------------\n\n");
}
