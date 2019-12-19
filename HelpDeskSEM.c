#include<stdio.h>
#include<stdlib.h>

#define NMAXCHAMADOS 100
#define NMAXPROBLEMAS 100
#define NMAXPCS 300

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

typedef struct{
    int maquina; 
    int defeito;
    char outro[100];
}PROBLEMA;

typedef struct pilha{
    PROBLEMA problm;
    int contador;
}PROBLEMAS;

typedef struct chamad{
    PROBLEMAS problema[NMAXPROBLEMAS];
    int ativo;
}CHAMADOS;

MAQUINA lerinfos(MAQUINA);

void cabecalho();
int menu_programa();
int menu_problema();
int menu_principal();
int menu_base();
int menu_alterarCad();
int chrpergunta();
void problemaDec(int);
void fpause2();

void iniciar_chamado(CHAMADOS *);
void iniciar_pc(MAQUINA *);
int livreChamado(CHAMADOS *);
int livreProblema(PROBLEMAS * );
int livrePC(MAQUINA *);
int primProblm(PROBLEMAS * );
int pesqID(MAQUINA *, int );
void inserir_chamado (CHAMADOS *,int);
void ins_problm (PROBLEMAS *, int ,int);
void ins_ele(MAQUINA *, MAQUINA);
void listarPC(MAQUINA *);
void listarTodosPcs(MAQUINA *,int);
void selectionSort (MAQUINA *,int);
void trocarPosicaoValores(MAQUINA *, MAQUINA *);
void remocaoPC(MAQUINA *);
void remocaoChamado(CHAMADOS *);
void remocaoProblm(PROBLEMAS *);
void alterarCad(MAQUINA *);
/*-------------------------------------MAIN-------------------------------------*/
int main(){ 
    MAQUINA pc[NMAXPCS],pcAux;
    CHAMADOS c[NMAXCHAMADOS];
    PROBLEMAS proAux;
    int menu,option,option2,option3,rodar,aux,ind,ind2,contpc = 0,contpcTOTAL = 0,contProblm =0,contChamado = 0;
    iniciar_chamado(&c[0]);
    iniciar_pc(&pc[0]);
    cabecalho();
    do{
        rodar=menu_principal();
        switch(rodar){
            case 0:   
                printf("Sistema Finalizado.\n");
                fpause2();          
                break;

            case 1:   /*Resolucao de problemas*/
                do{
                    option2=menu_programa();    /* 1 - Chamado atual, 2 - Fazer novo chamado, 3 - informacoes gerais*/
                    switch(option2){
                        case 0: /*Voltar*/
                            break;

                        case 1: /*Chamado atual (mostrar as infos , problema atual,qtd de problemas no chamado e perguntar se quer resolver)*/
                            if(c[0].ativo){
                                do{
                                    cabecalho();
                                    printf("RESOLUCAO DE PROBLEMAS:\n"); 
                                    ind = primProblm(&(c[0].problema[0]));
                                    proAux = c[0].problema[ind];
                                    if(proAux.problm.defeito != -1){
                                        printf("\nProblema: ");
                                        problemaDec(proAux.problm.defeito);
                                    }                 
                                    else  
                                        printf("\nProblema: %s\n",proAux.problm.outro);

                                    if(proAux.problm.maquina != -1){
                                        ind2 = pesqID(&pc[0], proAux.problm.maquina);
                                        if(ind2 == -1){
                                            printf("Computador anexado: ID %d\n",proAux.problm.maquina); 
                                            printf("Computador ainda nao cadastrado na base de dados! \n");
                                        }else
                                            listarPC(&pc[ind2]);
                                    }else
                                        printf("Nenhuma maquina anexada.\n"); 
                                    
                                    printf("\nResolver problema?. (S ou N)\n");
                                    aux = chrpergunta();
                                    if((aux) && aux != -1){
                                        remocaoProblm(&c[0].problema[ind]);
                                        cabecalho();
                                        printf("Sucesso!\n"); 
                                        if(c[0].problema[0].contador == -1){
                                            remocaoChamado(&c[0]);
                                            contChamado--;
                                            printf("Problemas resolvidos - Chamado finalizado. \n");
                                            if(c[0].ativo){
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

                        case 2: /*Cadastrar novo chamado.*/
                            cabecalho();
                            printf("Novo chamado. \n");
                            aux = 0;
                            contProblm = 0;
                            do{
                                option=menu_problema();
                                if(option){
                                    if(!aux){
                                        ind = livreChamado(&c[0]);
                                        inserir_chamado(&c[0],ind); /*prepara o nodo pra receber os chamados*/
                                        c[ind].ativo = 1;
                                        contChamado++;
                                    }
                                    contProblm++;
                                    ind2 = livreProblema(&(c[ind].problema[0]));
                                    ins_problm(&(c[ind].problema[ind2]),option,contProblm);
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

                        case 3:   /*Info gerais*/
                            cabecalho();
                            printf("INFORMACOES GERAIS:\n\n");
                            if(c[0].ativo){
                                printf("Numero de problemas do chamado atual :%d\n",c[0].problema[primProblm(&(c[0].problema[0]))].contador);
                                printf("Numero de chamados abertos:%d \n",contChamado);
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

            case 2:  /*opcoes e base de dados (arvore)*/
                do{
                    cabecalho();
                    menu = menu_base();
                    switch(menu){
                        case 0: /*VOLTAR*/
                            break;

                        case 1: /*CADASTRAR PC*/
                                cabecalho();
                                contpcTOTAL++;
                                if(contpcTOTAL == NMAXPCS){
                                    printf("banco cheio!\n");
                                    exit(2);
                                }
                                ind = livrePC(&pc[0]);
                                pcAux = lerinfos(pcAux);
                                ind2 = pesqID(&pc[0],pcAux.id);
                                if(ind2 == -1){
                                    ins_ele(&pc[ind],pcAux);
                                    printf("Computador cadastrado com sucesso!\n");
                                }else
                                    printf("ERRO! ID ja encontrado na Base de dados!\n");
                                fpause2();
                            break;

                        case 2: /*LISTAR MAQUINAS EM ORDEM ID*/
                        		if(pc[0].id != -1)
                                	listarTodosPcs(&pc[0],contpcTOTAL);
                                else
                                	printf("Nenhum computador cadastrado! \n");
                                fpause2();
                            break;

                        case 3: /*REMOVERPC*/
                                printf("Informe o ID a ser removido: \n");
                                scanf("%d",&aux);
                                ind = pesqID(&pc[0],aux);
                                if(ind != -1){
                                    remocaoPC(&pc[ind]);
                                    printf("Removido com sucesso!\n");
                                    contpcTOTAL--;
                                }else{
                                    printf("ID nao encontrado na base de dados!\n");
                                }
                                fpause2();
                            break;

                        case 4: /*ALTERAR CADASTRO*/
							printf("ALTERAR CADASTRO:\n\n");
							printf("Informe o ID: \n");
                            scanf("%d",&aux);
                            ind = pesqID(&pc[0],aux);
                            if(ind == -1)
                                printf("ID nao encontrado! \n");
                            else
                                alterarCad(&pc[ind]);
                            fpause2();  
                            break;

                        case 5: /*PESQUISAR ID*/
                                printf("Informe o ID a ser procurado: \n");
                                scanf("%d",&aux);
                                ind = pesqID(&pc[0],aux);
                                if(ind == -1)
                                    printf("ID nao encontrado! \n");
                                else
                                    listarPC(&pc[ind]);
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
/*--------------------------------Funcoes --------------------------------*/

void iniciar_chamado(CHAMADOS *c){
    int i,j;
    for (i=0; i<NMAXCHAMADOS; i++){
            (*(c+i)).ativo=0;
            for(j=0;j<NMAXPROBLEMAS;j++){
                (*(c+i)).problema[j].contador = -1;
            }
        }
}
void iniciar_pc(MAQUINA *pc){
    int i;
    for (i=0; i<NMAXPCS; i++){
        (*(pc+i)).id=-1;
    }
}

int livreChamado(CHAMADOS *c){
    int i,j;
    for (i=0; i<NMAXCHAMADOS; i++){
        if(!(*(c+i)).ativo)
            return i;
    }
    printf("BANCO CHEIO!\n");
    exit(1);
}

int livreProblema(PROBLEMAS * p){
    int i;
    for (i=0; i<NMAXPROBLEMAS; i++){
        if((*(p+i)).contador == -1)
            return i;
    }
    printf("BANCO CHEIO!\n");
    exit(1);
}

int livrePC(MAQUINA *pc){
    int i;
    for (i=0; i<NMAXPCS; i++){
        if((*(pc+i)).id==-1)
            return i;
    }
    printf("BANCO CHEIO!\n");
    exit(2);
}

void ins_problm (PROBLEMAS *p, int op,int contProblm){
    int aux;
    if(op==8){
        (*p).problm.defeito = -1;   
        printf("Qual o problema? Descreva-o sucintamente.\n");
        
        setbuf(stdin,NULL);
        fflush(stdin);
        scanf("%99[^\n]",(*p).problm.outro);
    }else{
        (*p).problm.outro[0]='\0';                                   
        (*p).problm.defeito = op;
    }
    printf("Anexar um computador ao problema?. (S ou N) \n");
    do{
        aux = chrpergunta();
        if(aux == 1){
            printf("Informe o ID do computador : \n");
            scanf("%d",&((*p).problm.maquina));   
        }else if(!aux){
            (*p).problm.maquina = -1;
        }else{
            printf("Opcao invalida! \n");  
        }   
    }while(aux == -1);	
    (*p).contador = contProblm;
}
int primProblm(PROBLEMAS * p){
    int i;
    for (i=NMAXPROBLEMAS-1; i>=0; i--){
        if((*(p+i)).contador != -1)
            return i;
    }
}

void inserir_chamado (CHAMADOS *c,int ind){
    (*(c+ind)).ativo;
}

int pesqID(MAQUINA *pc, int id){
    int i;
    if ((*(pc)).id == -1){  /*Vet vazio*/
        return -1;
    }
    else{ 
        for(i=0;i<NMAXPCS;i++){
                if(id == (*(pc+i)).id){ 
                    return i;
                    break;
                }
        }  
        return -1;
    }
}

void ins_ele(MAQUINA *pc, MAQUINA comp){
        (*(pc))=comp;
}

void listarPC(MAQUINA * pc){
    printf("\n-----------------------------------------------------------------------\n");
    printf("Numero de Serie (ID): %d\n\n",(*(pc)).id);
    printf("Marca: %s\n",(*(pc)).marca);
    printf("Modelo: %s\n",(*(pc)).modelo);
    printf("Sistema Operacional: %s\n",(*(pc)).SO);
    printf("Estado da Maquina: ");
    if(((*(pc)).estado == 'M') || ((*(pc)).estado == 'm'))
        printf("M - Manutencao.\n");
    else if(((*(pc)).estado == 'B') || ((*(pc)).estado == 'b'))
        printf("B - Bom estado / Em uso.\n");
    else
         printf("D - Deposito.\n");
    printf("IP: %d.%d.%d.%d \n", (*(pc)).ip.dig1, (*(pc)).ip.dig2, (*(pc)).ip.dig3, (*(pc)).ip.dig4);
    printf("\n-----------------------------------------------------------------------\n");
}

void listarTodosPcs(MAQUINA *pc,int qtdpc){
    if ((*(pc)).id == -1)
        printf("Nenhum computador foi cadastrado\n");
    else{ 
       int i;
       selectionSort(&pc[0],qtdpc);
       for(i=0;i<NMAXPCS;i++){
       		if((*(pc+i)).id != -1){
                listarPC((pc+i));
            }else
                break;
       }
    		
    }
}

void selectionSort(MAQUINA *vetorDesordenado, int tamanhoVetor ){ 
	MAQUINA aux;
	int i, j, posicaoValorMinimo;
	for (i = 0; i < ( tamanhoVetor - 1 ); i++){ 
		posicaoValorMinimo = i; 
		for (j = ( i + 1 ); j < tamanhoVetor; j++){ 		
			if( (*(vetorDesordenado+j)).id < (*(vetorDesordenado+posicaoValorMinimo)).id){ 
				posicaoValorMinimo = j; 
			}
		}
		if ( i != posicaoValorMinimo ){
			trocarPosicaoValores( &vetorDesordenado[i],&vetorDesordenado[posicaoValorMinimo]); 
		}
	}
}

void trocarPosicaoValores( MAQUINA *posicaoA, MAQUINA *posicaoB){ 
	MAQUINA temporario;
	temporario = *posicaoA;
	*posicaoA = *posicaoB;
	*posicaoB = temporario;     
}

void remocaoPC(MAQUINA *pc) {
    int i;
    for(i=0;(*(pc+i)).id != -1;(*(pc+i))=(*(pc+i+1)),i++);
}

void remocaoChamado(CHAMADOS *c) {
    int i;
    for(i=0;(*(c+i)).ativo;(*(c+i))=(*(c+i+1)),i++);
}

void remocaoProblm(PROBLEMAS *p){
    (*p).contador = -1;
}

void alterarCad(MAQUINA *pc) {
	int aux;
    if ((*(pc)).id == -1)
        printf("Nenhum computador foi cadastrado\n");
    do{
		cabecalho();
		printf("MAQUINA: \n");
		listarPC(&pc[0]);
		aux = menu_alterarCad();
		
		switch(aux){
			case 0:/*voltar*/
				break;

			case 1: /*marca*/
				printf("Marca atual: %s\n",(*(pc)).marca);
				
				setbuf(stdin,NULL);
				fflush(stdin);
				printf("Informe a Marca: ");
				scanf("%29[^\n]",(*(pc)).marca);
				fpause2();
				break;

			case 2:/*modelo*/
				printf("Modelo atual: %s\n",(*(pc)).modelo);

				setbuf(stdin,NULL);
				fflush(stdin);
				printf("Informe o modelo: ");
				scanf("%29[^\n]",(*(pc)).modelo);
				fpause2();
				break;

			case 3:/*SO*/
				printf("Sistema Operacional atual: %s\n",(*(pc)).SO);
				setbuf(stdin,NULL);
				fflush(stdin);
				printf("Informe o Sistema Operacional: ");
				scanf("%29[^\n]",(*(pc)).SO);
				fpause2();
				break;

			case 4:/*ESTADO */
				printf("Estado atual da Maquina: ");
				if(((*(pc)).estado == 'M') || ((*(pc)).estado == 'm'))
					printf("M - Manutencao.\n");
				else if(((*(pc)).estado == 'B') || ((*(pc)).estado == 'b'))
					printf("B - Bom estado / Em uso.\n");
				else
					printf("D - Deposito.\n");
				
				setbuf(stdin,NULL);
				fflush(stdin);
				printf("Informe o novo estado da maquina: \nM - Manutencao. \n B - Bom estado/em uso. \n D - Deposito. \n");
				scanf("%c",&(*(pc)).estado);
				
				fpause2();
				break;

			case 5:/*IP*/
				printf("IP: %d.%d.%d.%d \n", (*(pc)).ip.dig1, (*(pc)).ip.dig2, (*(pc)).ip.dig3, (*(pc)).ip.dig4);

				setbuf(stdin,NULL);
				fflush(stdin);
				printf("Informe o Novo IP da maquina: (0 a 255, com espacos)Ex: 192 168 0 20 \n");
				scanf("%d %d %d %d", &(*(pc)).ip.dig1, &(*(pc)).ip.dig2, &(*(pc)).ip.dig3, &(*(pc)).ip.dig4);
				fpause2();
				break;
		}
	}while(aux);
}

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

int menu_base(){
    int escolha;
    do{
        cabecalho();
        printf("1 - Cadastrar computador.\n");
        printf("2 - Listar maquinas por ordem crescente de ID. \n");
        printf("3 - Remover computador. \n");
        printf("4 - Alterar Cadastro. \n");
        printf("5 - Pesquisar por ID. \n");
        printf("\n0 - Voltar \n");
        
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

void problemaDec(int cod){
    switch(cod){
        case 1:
            printf("O computador nao liga.\n");
            break;
        case 2:
            printf("O computador liga,mas nao aparece algum erro no monitor.\n");
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
