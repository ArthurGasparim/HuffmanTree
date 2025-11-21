 typedef struct pilhaInt{
	int valor;
	struct pilhaInt *prox;
} Pilha;

void ExcluiPilha(Pilha *T){
	if(T !=  NULL){		
		ExcluiPilha(T->prox);
		free(&T);
	}

}

Pilha *POP(Pilha **P){
	Pilha *Aux;
	Aux = *P;
	*P = (*P) -> prox;
	return Aux;
}

void PUSH(Pilha **P, int i){
	Pilha *NC = (Pilha*)malloc(sizeof(Pilha));
	NC -> valor = i;
	NC -> prox = NULL;
	if(*P == NULL ){
		*P = NC;
	}
	else{
		NC -> prox = *P;
		*P = NC;
	}
}

void init(Pilha **P){
	*P = NULL;
}

char isEmpty(Pilha *P){
	return P == NULL;
}


char *retornaCod(Pilha *P){
	char code[20];
	int i;
	code[0] = '\0';
	while(P!=NULL){
		i = 0;
		while(code[i]!= '\0')
			i++;
		while(i != -1)
			code[i+1] = code[i--];
		code[0] = P->valor + '0';
		P = P->prox;
	}
	return code;
}



void exibeP(Pilha *P){
	Pilha *Aux;
	while(!isEmpty(P))
	{
		Aux = POP(&P);
		printf("[%d]", Aux -> valor);
	}
}
