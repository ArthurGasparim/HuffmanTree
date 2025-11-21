typedef struct palavra{
	char texto[500];
	struct palavra *prox;
}Palavra;

char isLetter(char letter){
	return (letter >= 65 && letter <=90) || (letter >= 97 && letter <=122);
}

void ExcluiPalavra(Palavra *T){
	if(T !=  NULL){		
		ExcluiPalavra(T->prox);
		free(&T);
	}

}


Palavra *CriaCaixa(char frase[500]){
	Palavra *NC = (Palavra *)malloc(sizeof(Palavra));
	strcpy(NC -> texto,frase);
	NC -> prox = NULL;
	return NC;
}

int acharFreq(Palavra *P, char texto[50]){
	int cont = 0;
	while(P != NULL){
		if(!strcmp(P->texto,texto))
			cont++;
		P = P -> prox;
	}
	return cont;
}


void insertWord(Palavra **P, char frase[500]){
	Palavra *Aux,*NC = CriaCaixa(frase); 
	if(*P == NULL){
		*P = NC;
	}
	else{
		Aux = *P;
		while(Aux -> prox != NULL)
			 Aux = Aux -> prox;
		Aux -> prox =  NC;
	}
}

void exibeWords(Palavra *P){
	while(P != NULL){
		printf("%s - ", P -> texto);
		P = P -> prox;
	}
}
void exibeTexto(Palavra *P){
	while(P != NULL){
		printf("%s", P -> texto);
		P = P -> prox;
		}
	}
	
