#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <conio2.h>
#include "TadPalavra.h"
#include "TadPalavraFreq.h"
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
