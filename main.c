#include<stdio.h>
#include<stdlib.h>

typedef struct net{
    int dig1;
    int dig2;
    int dig3;
    int dig4;
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
/*
void lerinfos(){

}
*/

//void maketree(ARV_BIN_ENC * arv, MAQUINA comp){
	
//}

//MAQUINA buscaID(ARV_BIN_ENC, int); // id
//void buscaIDprint(ARV_BIN_ENC, int);
//void ins_ele(ARV_BIN_ENC *, MAQUINA);
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
        printf("1 - receber valores e INICIAR ARVORE \n");
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
            		
					printf("CADASTRO DE MAQUINA: \n\n");
					
					fflush(stdin);
					printf("Informe a Marca: ");
					scanf("%s",computador.marca);
					
					fflush(stdin);
					printf("Informe o modelo: ");
					scanf("%s",computador.modelo);
					
					fflush(stdin);
					printf("Informe o Sistema Operacional: ");
					scanf("%s",computador.SO);
					
					fflush(stdin);
					printf("Informe o estado atual da maquina: \nM - Manutencao. \n B - Bom estado/em uso. \n D - Deposito. \n");
					scanf("%s",computador.estado);
					
					fflush(stdin);
					printf("Informe o IP da maquina: (sem )Ex: 192 168 0 20");
					scanf("%d", &computador.ip.dig1);
	
				/*	printf("marca: %s\n",computador.marca);
					printf("modelo: %s\n",computador.modelo);
					printf("so: %s\n",computador.SO);
					printf("estado: %c\n",computador.estado);
					printf("IP: %c.%c.%c.%c \n",computador.ip.dig1,computador.ip.dig2,computador.ip.dig3,computador.ip.dig4);
                //maketree(&info,computador);*/
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
