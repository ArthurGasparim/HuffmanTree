#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <conio2.h>

#include "TadPilhaInt.h"
#include "TadPalavra.h"
#include "TadPalavraFreq.h"
#include "TadTree.h"
#include "TadTabela.h"

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

char* getCode(char texto[500],Tabela *T){
	while(T != NULL && strcmp(texto,T->texto))
		T = T-> prox;
	if(T != NULL)
		return T->huffman;
}


void constroiVetor(Palavra *P, Tabela *T, char vet[10000]){
	int i = 0,j,size;
	char code[50];
	while(P != NULL){
		j = 0;
		strcpy(code,getCode(P->texto,T));
		while(code[j]!='\0')
			vet[i++] = code[j++];
		P = P->prox;
	}
	vet[i] = '\0';
	size = strlen(vet)%8;
	if(strlen(vet) > 8)
		size = 8-size;
	for(j = 0; j < size;j++){
		vet[i++] = '0';
	}
	vet[i] = '\0';
}

Palavra* constroiArq(FILE *arq1){
	char frase[5000],frase2[5000];
	int pos1,pos2;
	Palavra* P = NULL;
	fseek(arq1, 0, 2);
	pos1 = ftell(arq1);
	fseek(arq1, 0, 0);
	fread(frase,pos1,1,arq1);
	pos1 = pos2 = 0;
	while(frase[pos1] != '\0'){
		if(frase[pos1] == ' ')
		{
		
			frase2[pos2] = '\0';
			pos2 = 0;
			pos1++;
			insertWord(&P, frase2);
			insertWord(&P, (char *) " ");
		}
		else
			if(isLetter(frase[pos1]))
				frase2[pos2++] = frase[pos1++];
			else		
				pos1++;

				
			
	}
	frase2[pos2] = '\0';
	insertWord(&P, frase2);
	return P;
}


int main(){
	char frase[5000], frase2[5000],vet[10000];
	int i,pos1,pos2;
	unsigned char vet2[32];
	Pilha *PI;
	FILE *arq1 = fopen("TextoMontagemArvore.txt","r"),*arq2 = fopen("TextoCodificacao.txt","r");
	FILE *ptrArq = fopen("codificacao.dat","wb"),*cur2 = fopen("tabela.dat","wb");
	struct bits uval;
	TreeList *TL;
	Tabela *T = NULL,*Aux,write;
	Palavra *P = NULL,*P2 = NULL;
	init(&PI);
	PalavraFreq *PF = NULL;
	P2 = constroiArq(arq2);
	P = constroiArq(arq1);
	PrepararFreq(&PF,P);
	TL = makeTreeList(PF);
	//ExibeTL(TL);
	MakeTree(&TL);
	//getch();
	printf("\n");
	//ExibeTL(TL);
	printf("\n");
	exibeh(TL -> tree);
	getch();
	init(&PI);
	constroiTabela(TL -> tree,PF,&PI,&T);
	exibeTabela(T);
	constroiVetor(P2,T,vet);
	i = 0;
	while(vet[i]!= '\0')
	{
		uval.b0 = vet[i++] - '0';
		uval.b1 = vet[i++] - '0';
		uval.b2 = vet[i++]- '0';
		uval.b3 = vet[i++]- '0';
		uval.b4 = vet[i++]- '0';
		uval.b5 = vet[i++]- '0';
		uval.b6 = vet[i++]- '0';
		uval.b7 = vet[i++]- '0';
		
		fwrite(&uval,sizeof(unsigned char),1,ptrArq);
	}
	fclose(ptrArq);
	Aux = T;
	while(Aux != NULL){
		write = *Aux;
		fwrite(&write,sizeof(Tabela),1,cur2);
		Aux = Aux -> prox;
	}
	fclose(cur2);
	fclose(arq1);
	fclose(arq2);
	ExcluiTree(TL -> tree);
	free(&TL);//Só tem uma arvore msm;
	ExcluiPalavra(P);
	ExcluiPalavra(P2);
	ExcluiTabela(T);
	ExcluiPalavraFreq(PF);
	ExcluiPilha(PI);
}
