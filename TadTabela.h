typedef struct tabela{
	int code;
	char texto[500];
	char huffman[20];
}Tabela;

void insereTabela(Tabela **Tab, Tree *T, Pilha *P, PalavraFreq *PF){
	Tabela *NC = (Tabela *)malloc(sizeof(Tabela));
	
}

void constroiTabela(Tree *T, PalavraFreq *PF, Pilha **P, Tabela **tab){
	if(T != NULL){
		if(T -> code != -1){
			insereTabela(&(*tab), T, P,PF);
			POP(P);
		}
		else{
			if(T -> esq != NULL)
				constroiTabela(T -> esq,*PF, &(*P), &(*tab));
			if(T -> dir != NULL)
				constroiTabela(T -> dir,*PF, &(*P), &(*tab));	
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
