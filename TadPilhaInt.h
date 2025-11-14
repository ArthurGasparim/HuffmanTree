 typedef struct pilhaInt{
	int valor;
	struct pilhaInt *prox;
} Pilha;

int POP(Pilha **P){
	Pilha *Aux;
	Aux = *P;
	*P = (*P) -> prox;
	return Aux -> valor;
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

void exibeP(Pilha *P){
	Pilha *Aux;
	while(!isEmpty(P))
	{
		Aux = POP(&P);
		printf("[%d]", Aux -> valor);
	}
}
