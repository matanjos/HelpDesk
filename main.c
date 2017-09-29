#include<stdio.h>
#include<stdlib.h>

typedef struct net{
    unsigned char dig1;
    unsigned char dig2;
    unsigned char dig3;
    unsigned char dig4;
}IP;

typedef struct maquina{
    unsigned int id;
    char marca[20];
    char modelo[20];
    char SO[30];
    char estado;
    IP ip;
}MAQUINA;

typedef struct node {
    MAQUINA pc;
    struct node *left;
    struct node *right;
    struct node *father;
}NODE;
typedef NODE * ARV_BIN_ENC;

void lerinfos(MAQUINA *pc){
    printf("CADASTRO DE MAQUINA: \n\n");

    printf("Informe o Numero de Serie (ID): ");
    scanf("%d",&pc->id);
    fflush(stdin);
    printf("Informe a Marca: ");
    scanf("%s",pc->marca);
    
    fflush(stdin);
    printf("Informe o modelo: ");
    scanf("%s",pc->modelo);
    
    fflush(stdin);
    printf("Informe o Sistema Operacional: ");
    scanf("%s",pc->SO);
    
    fflush(stdin);
    printf("Informe o estado atual da maquina: \nM - Manutencao. \n B - Bom estado/em uso. \n D - Deposito. \n");
    scanf("%c",&(pc)->estado);
    
    fflush(stdin);
    printf("Informe o IP da maquina: (0 a 255, com espacos)Ex: 192 168 0 20 \n");
    scanf("%d %d %d %d", &(pc->ip).dig1, &(pc->ip).dig2, &(pc->ip).dig3, &(pc->ip).dig4);

}

void maketree(ARV_BIN_ENC * arv, MAQUINA comp){
	*arv = (ARV_BIN_ENC) malloc (sizeof (NODE));
    if (!(*arv)){
        printf("Memoria nao alocada!");
        exit(1);
    }
    (*arv)->pc = comp;
    (*arv)->left = NULL;
    (*arv)->right = NULL;
    (*arv)->father = NULL;
}

void listarNo(ARV_BIN_ENC *arv){
    printf("id: %d\n",((*arv)->pc).id);
    printf("marca: %s\n",((*arv)->pc).marca);
    printf("modelo: %s\n",((*arv)->pc).modelo);
    printf("so: %s\n",((*arv)->pc).SO);
    printf("estado: %c\n",((*arv)->pc).estado);
    printf("IP: %d.%d.%d.%d \n", ((*arv)->pc).ip.dig1, ((*arv)->pc).ip.dig2, ((*arv)->pc).ip.dig3, ((*arv)->pc).ip.dig4);
    system("pause");
}

void ins_ele(ARV_BIN_ENC *arv, MAQUINA comp){
    if (!(*arv)){
        maketree(arv,comp);
        printf("entrou");
    }
    else
        if ((comp.id) < ((*arv)->pc).id)
            ins_ele(&((*arv)->left), comp);
        else
            ins_ele(&((*arv)->right), comp);
}
//MAQUINA buscaID(ARV_BIN_ENC, int); // id
//void buscaIDprint(ARV_BIN_ENC, int);

//void remocaoPorCopia(ARV_BIN_ENC *, int);
//void balancearArv(ARV_BIN_ENC *);



void cabecalho(){
    system("cls");
    printf("------------------------------------------------------\n");
    printf("\t\t\tHELP DESK\n");
    printf("------------------------------------------------------\n\n");
}


int main(){
    int menu;
    ARV_BIN_ENC info;
    MAQUINA computador;
    do{
        cabecalho();
        printf("1 - RECEBER VALORES E INICIAR ARVORE \n");
        printf("2 - INSERIR: \n");
        printf("3 - REMOVER: \n");
        printf("4 - LISTAR: \n");
        printf("5 - BALANCEAR: \n");
        printf("6 - PESQUISA POR ID: \n");
        printf("7 - PESQUISA POR ID LISTANDO VISITAS: \n");
        printf("8 - SAIR: \n");
        scanf("%d",&menu);

        switch(menu){
            case 1:
            		cabecalho();
					lerinfos(&computador);
                    ins_ele(&info,computador);
                    //listarNo(&info);
                break;
            case 2:
                //INSERIR
                break;
            case 3:
                //REMOVER
                break;
            case 4:
                //LISTAR
                break;
            case 5:
                //BALANCEAR
                break;
            case 6:
                //PESQUISA ID
                break;
            case 7:
                //PESQUISA ID LISTANDO
                break;
            case 8:
                printf("Sistema finalizado. \n");
                system("pause");
                break;
            default: 
                printf("Opcao invalida\n");
                system("pause");
        }
    }while(menu != 8);
}
