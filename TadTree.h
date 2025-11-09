typedef struct tree{
	int code, freq;
	struct tree *esq,*dir;
}Tree;

typedef struct treeList{
	Tree *tree;
	struct treeList *prox;
}TreeList;

void inserirOrdTL(TreeList **TL, Tree *T){
	TreeList *Ant,*Aux,*NC = (TreeList *)malloc(sizeof(TreeList));
	NC -> prox = NULL;
	NC -> tree = T;
	if(*TL == NULL)
		*TL = NC;
	else{
		if(NC -> tree -> freq > (*TL) -> tree -> freq){
			NC -> prox = *TL;
			*TL = NC;
		}
		else{
			Aux = (*TL) -> prox;
			Ant = *TL;
			while(Aux != NULL && Aux -> tree -> freq > NC -> tree -> freq){
				Ant = Aux;
				Aux = Aux -> prox;
			}
			NC -> prox = Aux;
			Ant -> prox = NC;
		}
	}
}

void ExibeTL(TreeList *TL){
	while(TL != NULL){
		printf("[%d - %d] -> ",TL -> tree -> code, TL -> tree -> freq);
		TL = TL -> prox;
		
	}
}

TreeList *makeTreeList(PalavraFreq *PF){
	Tree *T;
	TreeList *TL = NULL;
	while(PF != NULL){
		T = (Tree *)malloc(sizeof(Tree));
		T -> code = PF ->code;
		T -> freq = PF -> freq;
		T -> esq = T -> dir = NULL;
		inserirOrdTL(&TL,T);
		PF = PF -> prox;
	}
	return TL;
}
