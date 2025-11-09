#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <conio2.h>
struct bits
{
	unsigned char b7:1;
	unsigned char b6:1;
	unsigned char b5:1;
	unsigned char b4:1;
	unsigned char b3:1;
	unsigned char b2:1;
	unsigned char b1:1;
	unsigned char b0:1;
};

typedef struct palavra{
	char texto[500];
	struct palavra *prox;
}Palavra;

typedef struct palavraFreq{
	char texto[500];
	int freq;
	struct palavraFreq *prox;
}PalavraFreq;



char isLetter(char letter){
	return (letter >= 65 && letter <=90) || (letter >= 97 && letter <=122);
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
		if(NC -> freq > (*PF) -> freq){
			NC -> prox = *PF;
			*PF = NC;
		}
		else{
			Aux = (*PF) -> prox;
			Ant = *PF;
			while(Aux != NULL && Aux -> freq > NC -> freq){
				Ant = Aux;
				Aux = Aux -> prox;
			}
			NC -> prox = Aux;
			Ant -> prox = NC;
		}
	}
}

void PrepararFreq(PalavraFreq **PF, Palavra *P){
	PalavraFreq *NC;
	Palavra *Aux = P;
	while(Aux != NULL){
		if(!isInPF(*PF,Aux))
			inserirOrd(&(*PF),P,Aux -> texto);
		Aux = Aux -> prox;
	}
	
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

void exibeWordsPF(PalavraFreq *P){
	while(P != NULL){
		printf("%s, %d ", P -> texto,P->freq);
		P = P -> prox;
	}
}

void exibeWords(Palavra *P){
	while(P != NULL){
		printf("%s - ", P -> texto);
		P = P -> prox;
	}
}

int main(){
	char frase[5000], frase2[5000];
	int TL=32,i,pos1,pos2;
	unsigned char vet2[32];
	FILE *ptrArq = fopen("codificacao.dat","wb");
	struct bits uval;
	Palavra *P = NULL;
	PalavraFreq *PF = NULL;
	gets(frase);
	pos1 = pos2 = 0;
	while(frase[pos1] != '\0'){
		if(frase[pos1] == ' ')
		{
			frase2[pos2] = '\0';
			pos2 = 0;
			pos1++;
			insertWord(&P, frase2);
		}
		else
			if(isLetter(frase[pos1]))
				frase2[pos2++] = frase[pos1++];
			else
				pos1++;
			
	}
	frase2[pos2] = '\0';
	insertWord(&P, frase2);
	exibeWords(P);
	PrepararFreq(&PF,P);
	printf("\n");
	exibeWordsPF(PF);
	getch();
	/*for(i=0;i<32;){
		uval.b0 = vet[i++];
		uval.b1 = vet[i++];
		uval.b2 = vet[i++];
		uval.b3 = vet[i++];
		uval.b4 = vet[i++];
		uval.b5 = vet[i++];
		uval.b6 = vet[i++];
		uval.b7 = vet[i++];
		
		fwrite(&uval,sizeof(unsigned char),1,ptrArq);
	}
	
	
	fclose(ptrArq);
	
	//---------------------------
	
	ptrArq = fopen("codificacao.dat","rb");
	fread(&uval,sizeof(unsigned char),1,ptrArq);
	i=0;
	while(!feof(ptrArq)){
		vet2[i++] = uval.b0 ;
		vet2[i++] = uval.b1 ;
		vet2[i++] = uval.b2 ;
		vet2[i++] = uval.b3;
		vet2[i++] = uval.b4 ;
		vet2[i++] = uval.b5 ;
		vet2[i++] = uval.b6 ;
		vet2[i++] = uval.b7 ;
		fread(&uval,sizeof(unsigned char),1,ptrArq);
	}
	fclose(ptrArq);
	
	for(i = 0; i<TL;i++)
		printf("%d",vet2[i]);
	
	*/
}
