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

char* getTexto(char code[50],Tree *T,Tabela*Tab){
	int i =0;
	while(code[i]!='\0'){
		if(code[i] == '0'){
			T = T-> esq;
		}
		else{
			T = T -> dir;
		}
		i++;
	}
	if(T -> code != -1)
		return getText(T->code,Tab);
	return NULL;
}

void insereTabela2(Tabela T, Tabela **Tab){
	Tabela *Aux,*NC = (Tabela*)malloc(sizeof(Tabela));
	*NC = T;
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

Tree *novaCaixa(int code, char texto[500]){
	Tree *NC = (Tree *)malloc(sizeof(Tree));
	NC -> code = code;
	NC -> esq = NC -> dir = NULL;
	return NC;
}

void criarArvore(Tree **tree, Tabela *T){
	int i;
	char code[50];
	Tree *Aux,*Ant;
	*tree = novaCaixa(-1,"");
	while(T != NULL){
		Aux = *tree;
		i = 0;
		strcpy(code,T->huffman);
		while(code[i] != '\0'){
			Ant = Aux;
			if(code[i] == '0'){
				if(Aux -> esq == NULL){
					Aux -> esq = novaCaixa(-1,(char*)"");
				}
				Aux = Aux -> esq;
			}
			else{
				if(Aux -> dir == NULL){
					Aux -> dir = novaCaixa(-1,(char*)"");
				}
				Aux = Aux -> dir;
			}
			i++;
		}
		if(code[i-1] == '0'){
			Ant ->esq =  novaCaixa(T->code,T->texto);
		}else{
			Ant -> dir = novaCaixa(T->code,T->texto);
		}
		T = T-> prox;
	}
}

void trim(Palavra *P,Palavra *Ant,int *flag ){
	if(P != NULL){
		trim(P->prox,P,&(*flag));
		if(strcmp(P-> texto,(char*)" "))
			*flag = 1;
		if(!flag){
			Ant -> prox = NULL;
			free(P);
		}
	}
}


int main(){
	FILE *ptrArq = fopen("codificacao.dat","rb"),*cur2 = fopen("tabela.dat","rb");
	char vet[10000],code[50];
	Palavra *P  = NULL;
	Tabela *T = NULL,read;
	Tree *tree = NULL;
	int i=0,j;
	struct bits uval;
	
	fread(&uval,sizeof(unsigned char),1,ptrArq);
	while(!feof(ptrArq)){
		vet[i++] = uval.b0 + '0';
		vet[i++] = uval.b1  + '0';
		vet[i++] = uval.b2 + '0' ;
		vet[i++] = uval.b3 + '0';
		vet[i++] = uval.b4 + '0' ;
		vet[i++] = uval.b5 + '0' ;
		vet[i++] = uval.b6 + '0' ;
		vet[i++] = uval.b7 + '0' ;
		fread(&uval,sizeof(unsigned char),1,ptrArq);
	}
	fclose(ptrArq);
	
	fread(&read,sizeof(Tabela),1,cur2);
	while(!feof(cur2)){
		read.prox =NULL;
		insereTabela2(read,&T);
		fread(&read,sizeof(Tabela),1,cur2);
	}
	
	exibeTabela(T);
	vet[i] = '\0';
	i = 0;j = 0;
	criarArvore(&tree, T);
	exibeh2(tree);

	while(vet[i]!= '\0'){
		code[j++] = vet[i++];
		code[j] = '\0';
		if(getTexto(code,tree,T) != NULL){
			insertWord(&P,getTexto(code,tree,T));
			j = 0;
		}
	}
	i = 0;
	exibeTexto(P);
	ExcluiTabela(T);
	ExcluiTree(tree);
	ExcluiPalavra(P);
	fclose(cur2);
}
