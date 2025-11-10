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
		if(NC -> tree -> freq < (*TL) -> tree -> freq){
			NC -> prox = *TL;
			*TL = NC;
		}
		else{
			Aux = (*TL) -> prox;
			Ant = *TL;
			while(Aux != NULL && Aux -> tree -> freq < NC -> tree -> freq){
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

TreeList* remove(TreeList **TL){
	TreeList *Aux;
	Aux = *TL;
	*TL = (*TL) -> prox;
	return Aux;
}

int size(TreeList *TL){
	int cont = 0;
	while(TL != NULL)
		{
			cont++;
			TL = TL -> prox;	
		}
	return cont;
}

void exibe(Tree* raiz, int x, int y, int dist){
	
	if(raiz != NULL){
		gotoxy(y,x);
			printf("[%d - %d] -> ",raiz -> code, raiz -> freq);
		gotoxy(y-dist/1.2,x+2);
		printf("/");
		gotoxy(y+dist/1.2,x+2);
		printf("\\");
		
		exibe(raiz -> esq, x+4, y - dist, dist/1.5);
		exibe(raiz -> dir, x + 4,y + dist,dist/1.5);
	}
}

void MakeTree(TreeList **TL){
	TreeList *T1,*T2, NTL;
	Tree *NT;
	
	while(size(*TL) > 1){
		T1 = remove(&(*TL));
		T2 = remove(&(*TL));
		NT = (Tree *)malloc(sizeof(Tree));
		NT -> freq = T1 -> tree -> freq + T2 -> tree -> freq;
		NT -> code = -1;
		NT -> esq = T1 -> tree;
		NT -> dir = T2 -> tree;
		inserirOrdTL(&(*TL),NT);
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
