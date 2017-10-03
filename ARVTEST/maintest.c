// C program to demonstrate delete operation in binary search tree
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
// A utility function to create a new BST node
/*struct node *newNode(int item)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}*/
ARV_BIN_ENC maketree (MAQUINA comp){
	NODE * arv = (ARV_BIN_ENC) malloc (sizeof(NODE));
    if (!(arv)){
        printf("Memoria nao alocada!");
        exit(1);
    }
    (arv)->pc = comp;
    (arv)->left = NULL;
    (arv)->right = NULL;
    return (arv);
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
 
// A utility function to do InOrdem traversal of BST
void InOrdem(ARV_BIN_ENC arv) {
    if (arv) {
        InOrdem(arv->left); 
        listarNo(arv);
        InOrdem(arv->right); 
    }
}

 
/* A utility function to insert a new node with given key in BST */
/*
struct node* insert(struct node * node, int key)
{
    // If the tree is empty, return a new node 
    if (node == NULL) return newNode(key);
 
    // Otherwise, recur down the tree 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);
 
    // return the (unchanged) node pointer 
    return node;
}*/
ARV_BIN_ENC ins_ele(ARV_BIN_ENC arv, MAQUINA comp){ //recursiva, ubuntu
    if (!(arv)){
        return maketree(comp);
    }
    if ((comp.id) < ((arv->pc).id))
        (arv)->left = ins_ele(arv->left, comp);
    else
        (arv)->right = ins_ele(arv->right, comp);
    return(arv);
}
 
/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
ARV_BIN_ENC minValueNode(ARV_BIN_ENC node)
{
    ARV_BIN_ENC current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
ARV_BIN_ENC deleteNode(ARV_BIN_ENC root, int key){
    // base case
    if (root == NULL) return root;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < (root->pc).id)
        root->left = deleteNode(root->left, key);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > (root->pc).id)
        root->right = deleteNode(root->right, key);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            ARV_BIN_ENC temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            ARV_BIN_ENC temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children: Get the InOrdem successor (smallest
        // in the right subtree)
        ARV_BIN_ENC temp = minValueNode(root->right);
 
        // Copy the InOrdem successor's content to this node
        root->pc = temp->pc;
 
        // Delete the InOrdem successor
        root->right = deleteNode(root->right, (temp->pc).id);
    }
    return root;
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
void fpause2(){                     
	setbuf(stdin,NULL);
    fflush(stdin);
	printf("Pressione alguma tecla pra continuar... \n");
	getchar();
}
 
 void cabecalho(){
    system("clear > nul"); //verificar ubuntu
    system("cls");
    printf("------------------------------------------------------\n");
    printf("\t\t\tHELP DESK\n");
    printf("------------------------------------------------------\n\n");
}
// Driver Program to test above functions
int main()
{
    /* Let us create following BST
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 */
    ARV_BIN_ENC root = NULL;
    int menu;
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
                    root = ins_ele(root,lerinfos(computador));               
                    fpause2();
                break;
            case 2:
			    InOrdem(root);
                    fpause2();
                break;
            case 3:
                   
                    printf("InOrdem traversal of the given tree \n");
                    InOrdem(root);
                
                    printf("\nDelete 12\n");
                    root = deleteNode(root, 12);
                    printf("InOrdem traversal of the modified tree \n");
                    InOrdem(root);
                
                    printf("\nDelete 30\n");
                    root = deleteNode(root, 30);
                    printf("InOrdem traversal of the modified tree \n");
                    InOrdem(root);
                
                    printf("\nDelete 50\n");
                    root = deleteNode(root, 14);
                    printf("InOrdem traversal of the modified tree \n");
                    InOrdem(root);
                    fpause2();
                    
                break;
            case 4:
                    
                break;
            case 5:
                //BALANCEAR
                break;
            case 6:
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

}