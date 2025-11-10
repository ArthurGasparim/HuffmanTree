typedef struct palavraFreq{
	int code;
	char texto[500];
	int freq;
	struct palavraFreq *prox;
}PalavraFreq;



char isInPF(PalavraFreq *PF, Palavra *P){
	while(PF != NULL && strcmp(PF -> texto,P -> texto))
		PF = PF -> prox;	
	return PF != NULL;
}

void inserirOrd(PalavraFreq **PF, Palavra *P,char texto[50]){
	PalavraFreq *Ant,*Aux,*NC = (PalavraFreq *)malloc(sizeof(PalavraFreq));
	NC -> prox = NULL;
	strcpy(NC -> texto, texto);
	NC -> freq = acharFreq(P,texto);
	if(*PF == NULL)
		*PF = NC;
	else{
		if(NC -> freq < (*PF) -> freq){
			NC -> prox = *PF;
			*PF = NC;
		}
		else{
			Aux = (*PF) -> prox;
			Ant = *PF;
			while(Aux != NULL && Aux -> freq < NC -> freq){
				Ant = Aux;
				Aux = Aux -> prox;
			}
			NC -> prox = Aux;
			Ant -> prox = NC;
		}
	}
}

void PrepararFreq(PalavraFreq **PF, Palavra *P){
	PalavraFreq *AuxPF;
	int count = 0;
	Palavra *Aux = P;
	while(Aux != NULL){
		if(!isInPF(*PF,Aux))
			inserirOrd(&(*PF),P,Aux -> texto);
		Aux = Aux -> prox;
	}
	AuxPF = *PF;
	while(AuxPF != NULL){
		AuxPF -> code = count++;
		AuxPF = AuxPF -> prox;
	}
	
}

void exibeWordsPF(PalavraFreq *P){
	while(P != NULL){
		printf("%d - %s - %d\n",P -> code, P -> texto,P->freq);
		P = P -> prox;
	}
}
