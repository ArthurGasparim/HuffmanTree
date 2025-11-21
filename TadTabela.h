typedef struct tabela{
	int code;
	char texto[500];
	char huffman[20];
	struct tabela *prox;
}Tabela;

char* getText(int code, Tabela*T){
	while(T != NULL && code != T->code)
		T = T-> prox;
	if(T != NULL)
		return T->texto;
}

void ExcluiTabela(Tabela *T){
	if(T !=  NULL){		
		ExcluiTabela(T->prox);
		free(&T);
	}

}

void insereTabela(Tabela **Tab, Tree *T, Pilha *P, PalavraFreq *PF){
	Tabela *NC = (Tabela *)malloc(sizeof(Tabela)),*Aux;
	NC -> code = T->code;
	strcpy(NC -> texto, retornaTexto(NC->code,PF));
	strcpy(NC -> huffman,retornaCod(P));
	if(*Tab == NULL){
		*Tab = NC;
	}
	else{
		Aux = *Tab;
		while(Aux -> prox != NULL)
			 Aux = Aux -> prox;
		Aux -> prox =  NC;
	}
}

void exibeTabela(Tabela *P){
	while(P != NULL){
		printf("%d - %s - %s\n",P -> code, P -> texto,P->huffman);
		P = P -> prox;
	}
}

void constroiTabela(Tree *T, PalavraFreq *PF, Pilha **P, Tabela **tab){
	if(T != NULL){
		if(T -> code != -1){
			insereTabela(&(*tab), T, *P,PF);
			POP(&(*P));
		}
		else{
			if(T -> esq != NULL){
				PUSH(&(*P),0);
				constroiTabela(T -> esq, PF, &(*P), &(*tab));
			}
				
			if(T -> dir != NULL){
				PUSH(&(*P),1);
				constroiTabela(T -> dir,PF, &(*P), &(*tab));	
			if(!isEmpty(*P))
				POP(&(*P));
				
			}
		
		}		
	}
}


	
/*
Tabela *constroiTabela(Tree *T, PalavraFreq *P){
	PilhaT *PT;
	Tree *Aux;
	initT(&PT);
	Push(&PT,T);
	while(!isEmptyT(PT)){
		Aux = POP(&PT);
		if(Aux -> dir != NULL)
		{
			PUSHT(&PT,Aux->dir);
		}
			
		if(Aux -> esq != NULL)
		{
			PUSHT(&PT,Aux->esq);
		}
	}
}
*/
