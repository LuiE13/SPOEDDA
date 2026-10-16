//{"Brasília", "Curitiba", "Natal", "Porto Alegre", "São Paulo"}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int buscaBinaria(char vetor[5][20], char procurado[20]){
	int inicio = 0;
	int fim = 4;
	int meio;	
	while(inicio<=fim){
		meio = (fim+inicio)/2;
		if(strcmp(vetor[meio],procurado)==0){
			return meio;
		}
		if(strcmp(vetor[meio],procurado)<0){
			fim=meio-1;
		}else{
			inicio= meio+1;
		}
		return -1;
	}
}

int main(){
	char lista[5][20] = {"Brasília", "Curitiba", "Natal", "Porto Alegre", "São Paulo"};
	int i = buscaBinaria(lista,"Natal");
	printf("Posição : %i",i);
}
