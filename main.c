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
    IP ip;
}MAQUINA;

typedef struct node {
    MAQUINA pc;
    struct node *left;
    struct node *right;
    struct node *father;
}NODE;

void cabecalho(){
    system("cls");
    printf("------------------------------------------------------\n");
    printf("\t\t\tHELP DESK\n");
    printf("------------------------------------------------------\n\n");
}


int main(){
    int menu;
    do{
        cabecalho();
        printf("1 - INICIAR ARVORE \n");
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
                //LER DA BASE
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