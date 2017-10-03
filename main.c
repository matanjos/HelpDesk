#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

typedef struct net{
    unsigned char dig1;
    unsigned char dig2;
    unsigned char dig3;
    unsigned char dig4;
}IP;

typedef struct maquina{
    unsigned int id;
    char marca[30];
    char modelo[30];
    char SO[30];
    char estado;
    IP ip;
}MAQUINA;

typedef struct node {
    MAQUINA pc;
    struct node *left;
    struct node *right;
}NODE;

typedef NODE * ARV_BIN_ENC;

ARV_BIN_ENC maketree(ARV_BIN_ENC, MAQUINA);
void listarNo(ARV_BIN_ENC);
ARV_BIN_ENC ins_ele(ARV_BIN_ENC, MAQUINA);
void InOrdem(ARV_BIN_ENC);
ARV_BIN_ENC left(ARV_BIN_ENC);
ARV_BIN_ENC right(ARV_BIN_ENC);
ARV_BIN_ENC brother(ARV_BIN_ENC);
ARV_BIN_ENC pesqID(ARV_BIN_ENC, int);


void cabecalho();
void fpause2();
MAQUINA lerinfos(MAQUINA);

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
    }
        return arvore;
}


//--------------------------------------------------------------------------------------------------------
int main(){
    int menu,aux;
    ARV_BIN_ENC info = NULL,arvaux = NULL;
    MAQUINA computador;
    do{
        cabecalho();
        printf("1 - CADASTRAR COMPUTADOR\n");
        printf("2 - LISTAR EM ORDEM CRESCENTE (PERCURSO IN-ORDEM): \n");
        printf("3 - REMOVER: \n");
        printf("5 - BALANCEAR: \n");
        printf("6 - PESQUISA POR ID: \n");
        printf("7 - PESQUISA POR ID LISTANDO VISITAS: \n");
        printf("8 - SAIR: \n");
        scanf("%d",&menu);

        switch(menu){
            case 1:
            		cabecalho();
                    info = ins_ele(info,lerinfos(computador));
                    fpause2();
                break;
            case 2:
			        InOrdem(info);
                    fpause2();
                break;
            case 3:
            
                    printf("InOrdem traversal of the given tree \n");
                    InOrdem(info);
                
                    printf("\nDelete 12\n");
                    info = remocaoPorCopia(info, 12);
                    printf("InOrdem traversal of the modified tree \n");
                    InOrdem(info);
                
                    printf("\nDelete 30\n");
                    info = remocaoPorCopia(info, 30);
                    printf("InOrdem traversal of the modified tree \n");
                    InOrdem(info);
                
                    printf("\nDelete 14\n");
                    info = remocaoPorCopia(info, 14);
                    printf("InOrdem traversal of the modified tree \n");
                    InOrdem(info);
                    fpause2();
                break;
            case 4:
                    
                break;
            case 5:
                //BALANCEAR
                break;
            case 6:
                    printf("Informe o ID a ser procurado: \n");
                    scanf("%d",&aux);
                    arvaux = pesqID(info, aux);
                    if(!arvaux){
                        printf("ID nao encontrado! \n");
                    }else{
                        listarNo(arvaux);
                    }
                    fpause2();   
                break;
            case 7:
                //PESQUISA ID LISTANDO
                break;
            case 8:
                printf("Sistema finalizado. \n");
		        fpause2();               
              break;
            default: 
                printf("Opcao invalida\n");
               fpause2();   
        }
    }while(menu != 8);

    return 0;
}

//--------------------------------------------------------------------------------------------------------

/*ARV_BIN_ENC ins_ele(ARV_BIN_ENC *arv, MAQUINA comp){ //recursiva, ubuntu
    if (!(*arv)){
        maketree(arv,comp);
        printf("entrou");
    }
    else
        if ((comp.id) < ((*arv)->pc).id)
            (*arv)->left = ins_ele(&((*arv)->left), comp);
        else
            (*arv)->right = ins_ele(&((*arv)->right), comp);
    return(*arv);



    //------------------///
     printf("paiinfo: %d\n",(info->pc).id);
                   printf("filho esq info: %d\n",((info->left)->pc).id);
                	printf("filho dir info: %d\n",((info->right)->pc).id);
                	fpause2();   
}*/

//MAQUINA buscaID(ARV_BIN_ENC, int); // id
//void buscaIDprint(ARV_BIN_ENC, int);

//void remocaoPorCopia(ARV_BIN_ENC *, int);
//void balancearArv(ARV_BIN_ENC *);

void InOrdem(ARV_BIN_ENC arv) {
    if (arv) {
        InOrdem(left(arv)); 
        listarNo(arv);
        InOrdem(right(arv)); 
    }
}

void fpause2(){                     
	setbuf(stdin,NULL);
    fflush(stdin);
	printf("Pressione alguma tecla pra continuar... \n");
	getchar();
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

ARV_BIN_ENC maketree(ARV_BIN_ENC arv, MAQUINA comp){
	arv = (ARV_BIN_ENC) malloc (sizeof (NODE));
    if (!(arv)){
        printf("Memoria nao alocada!");
        exit(1);
    }
    (arv)->pc = comp;
    (arv)->left = NULL;
    (arv)->right = NULL;
}

void listarNo(ARV_BIN_ENC arv){
    printf("\n-----------------------------------------------------------------\n");
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

    printf("\n-----------------------------------------------------------------\n");
}



ARV_BIN_ENC ins_ele(ARV_BIN_ENC arv, MAQUINA comp){ //recursiva, ubuntu
    if (!(arv)){
        return maketree(arv,comp);
    }
    if ((comp.id) < ((arv->pc).id))
        (arv)->left = ins_ele(arv->left, comp);
    else
        (arv)->right = ins_ele(arv->right, comp);
    return(arv);
}
ARV_BIN_ENC pesqID(ARV_BIN_ENC arv, int id){
     if (!(arv))
        printf("Não consta no cadastro! \n");
    else{ 
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
}

ARV_BIN_ENC left(ARV_BIN_ENC arv){
    return arv->left;
}
ARV_BIN_ENC right(ARV_BIN_ENC arv){
    return arv->right;
}


void cabecalho(){
    system("clear > nul"); //verificar ubuntu
    system("cls");
    printf("------------------------------------------------------\n");
    printf("\t\t\tHELP DESK\n");
    printf("------------------------------------------------------\n\n");
}

