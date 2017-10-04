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
///---------------------------------------
 printf("paiinfo: %d\n",(info->pc).id);
                   printf("filho esq info: %d\n",((info->left)->pc).id);
                	printf("filho dir info: %d\n",((info->right)->pc).id);
                	fpause2();   