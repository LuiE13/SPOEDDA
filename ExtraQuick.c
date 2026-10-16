#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    int id_produto;
    char descritivo[100];
    char unidade_medida[30];
    int quantidade_por_cesta;
    int validade_em_dias;
} ProdutoCesta;


void troca (ProdutoCesta *A, ProdutoCesta *B) 
{
  ProdutoCesta aux = *A; 
  *A = *B; 
  *B = aux;
}

int particiona (ProdutoCesta * vetor, int ini, int pivo) 
{    
    int   i;
    int   p_maior = ini; /* a posição do maior é a do início do vetor */    
    
    for ( i=ini; i<pivo; i++ ) /* percorre o vetor da posição ini até a do pivô */
    {        
       if ( vetor[i].validade_em_dias < vetor[pivo].validade_em_dias ) /*se o elemento da posição atual for menor que o pivô...*/
       {            
            troca(  &vetor[i], &vetor[p_maior] ); /*...troca o atual com o maior */
            p_maior++; /* o maior avança uma posição */
       }    
   }     
   /* percorrido o vetor, o pivô troca de posição com a do maior elemento... */
   troca(  &vetor[p_maior], &vetor[pivo] ); 
   if(pivo==11 && ini==0){
	   printf("--- Lista de Produtos da Cesta (1º particionamento) ---\n\n");
	    for (i = 0; i < pivo; i++) {
	        printf("ID: %02d\n", vetor[i].id_produto);
	        printf("Descricao: %s\n", vetor[i].descritivo);
	        printf("Unidade: %s\n", vetor[i].unidade_medida);
	        printf("Quantidade: %d\n", vetor[i].quantidade_por_cesta);
	        printf("Validade: %d dias\n", vetor[i].validade_em_dias);
	        printf("----------------------------------\n");
	    }
	}
   return p_maior; /* ... e o maior elemento passa a ser o novo pivô */ 
}

void quick_sort	(ProdutoCesta * vetor, int ini, int fim) 
{    
   int pivo;
   if ( ini<fim ) /* Caso base */ 
   {        
        pivo = particiona ( vetor, ini, fim ); /* Particiona o vetor*/ 
        quick_sort( vetor, ini,    pivo-1 );    /* Ordena do início do vetor até antes do pivô */
        quick_sort( vetor, pivo+1, fim);      /* Ordena desde após o pivô até o fim do vetor */
   } 
}

int main() {
   
    ProdutoCesta cesta[12] = {
        {1,  "Leite em po integral para bebida", "400 g",  2, 1095},
        {2,  "Farinha de mandioca branca",      "500 g",  1, 2190},
        {3,  "Oleo de soja",                    "900 ml", 1, 400},
        {4,  "Polpa ou pure de tomate",         "caixa",  1, 300},
        {5,  "Sardinha em oleo comestivel",     "lata",   2, 1825},
        {6,  "Racao animal",                    "1 Kg",   1, 180},
        {7,  "Sabonete de corpo",               "barra",  1, 1095},
        {8,  "Creme dental",                    "bisnaga",1, 700},
        {9,  "Absorvente higienico",            "pacote", 1, 1825},
        {10, "Agua sanitaria",                  "1L",     1, 2190},
        {11, "Detergente em po",                "1 Kg",   1, 1825},
        {12, "Desinfetante",                    "500 ml", 1, 730}
    };

    int total_produtos = sizeof(cesta) / sizeof(cesta[0]);
	int i;
    
    printf("--- Lista de Produtos da Cesta ---\n\n");
    for ( i = 0; i < total_produtos; i++) {
        printf("ID: %02d\n", cesta[i].id_produto);
        printf("Descricao: %s\n", cesta[i].descritivo);
        printf("Unidade: %s\n", cesta[i].unidade_medida);
        printf("Quantidade: %d\n", cesta[i].quantidade_por_cesta);
        printf("Validade: %d dias\n", cesta[i].validade_em_dias);
        printf("----------------------------------\n");
    }
    
    quick_sort(cesta , 0, total_produtos-1);
	printf("\n--- Ordenado! ---\n\n");
	system("pause");
	
	    
    printf("--- Lista de Produtos da Cesta (Ordenaçao final) ---\n\n");
    for (i = 0; i < total_produtos; i++) {
        printf("ID: %02d\n", cesta[i].id_produto);
        printf("Descricao: %s\n", cesta[i].descritivo);
        printf("Unidade: %s\n", cesta[i].unidade_medida);
        printf("Quantidade: %d\n", cesta[i].quantidade_por_cesta);
        printf("Validade: %d dias\n", cesta[i].validade_em_dias);
        printf("----------------------------------\n");
    }

    return 0;
}
