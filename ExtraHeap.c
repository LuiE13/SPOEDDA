#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

// Definição da estrutura para armazenar os dados de cada produto
typedef struct {
    int codigo;
    char nome[50];
    float preco;
} Produto;

#define TAMANHO_VETOR  20

 Produto produtos[20] = {
        {101, "Notebook", 3500.00},
        {102, "Celular", 2000.00},
        {103, "Teclado", 150.00},
        {104, "Mouse", 80.00},
        {105, "Monitor", 1200.00},
        {106, "Fone", 250.00},
        {107, "Cadeira", 800.00},
        {108, "Impressora", 600.00},
        {109, "Webcam", 200.00},
        {110, "Gabinete", 350.00},
        {111, "HD Externo", 300.00},
        {112, "SSD", 250.00},
        {113, "Roteador", 180.00},
        {114, "Microfone", 400.00},
        {115, "Tablet", 1500.00},
        {116, "Pendrive", 50.00},
        {117, "Joystick", 220.00},
        {118, "Mousepad", 45.00},
        {119, "Estabilizador", 120.00},
        {120, "Caixa de Som", 110.00}
    };


/*=========Rotinas de apoio ao HeapSort apresentadas na aula de 25/09/26:================*/
/* Considerando que heap é um array e que a posição de um nó é i, a posição do seu filho da
esquerda será (i * 2 + 1). */
int esquerdo(int i)
{
 return (2*i+1);
}
/* Considerando que heap é um array e que a posição de um nó é i, a posição do seu filho da
direita será (i * 2 + 1) + 1. */
int direito(int i)
{
 return (2*i+2);
}


/* Considerando que heap é um array e que a posição de um nó é i, a posição do seu pai será
(i - 1) / 2. */
int pai(int i)
{
 return ( (i-1)/2 );
}


void troca(Produto *A, Produto *B) {
    Produto aux = *A;
    *A = *B;
    *B = aux;
}


void BuildHeap(Produto *vetor) {
    int i, atual;
    
    for(i = 1; i < TAMANHO_VETOR; i++) {
        atual = i;
        
        while(atual > 0 && strcmp(vetor[atual].nome, vetor[pai(atual)].nome) > 0) {
            troca(&vetor[atual], &vetor[pai(atual)]);
            atual = pai(atual);
        }
    }
}

void gotoxy(int x, int y){
  COORD c;
  c.X = x;
  c.Y = y;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void mostra_heap (Produto *vetor)
{
    int i, lin=30, col=40;
    printf ("\n---------------------------------------- HEAP ----------------------------------------\n");
    /* imprime a raiz */
    gotoxy(col, lin); printf ("%s",  
               vetor[0].nome);
    gotoxy( 20,   4); printf ("--------------------|--------------------");
    /* percorre o vetor */
    for (i=1; i<TAMANHO_VETOR; i++)
    {
       /* enquanto tiver 2 filhos */
       switch (i)
       { 
	     case  1:{ lin=35; col=20; } break;
	     case  2:{ lin=35; col=60; } break;
	     case  3:{ lin=37; col=10; } break;
	     case  4:{ lin=37; col=30; } break;
	     case  5:{ lin=37; col=50; } break;
	     case  6:{ lin=37; col=70; } break;
	     case  7:{ lin=39; col=5;  } break;
	     case  8:{ lin=39; col=15; } break;
	     case  9:{ lin=39; col=25; } break;
	     case 10:{ lin=39; col=35; } break;
         case 11:{ lin=39; col=45; } break;
         case 12:{ lin=39; col=55; } break;
         case 13:{ lin=39; col=65; } break;
         case 14:{ lin=39; col=75; } break;
	   }
	   gotoxy(col, lin);  printf ("%s ", 
               vetor[i].nome);
	   switch (i)
       { 
	     case  1:{ gotoxy(10, 36); printf("----------|---------"); } break;
	     case  2:{ gotoxy(50, 36); printf("----------|---------"); } break;
	     case  3:{ gotoxy( 5, 38); printf("-----|-----"); } break;
	     case  4:{ gotoxy(25, 38); printf("-----|-----"); } break;
	     case  5:{ gotoxy(45, 38); printf("-----|-----"); } break;
	     case  6:{ gotoxy(65, 38); printf("-----|-----"); } break;
	   }
    }
	printf ("\n\n------------------------------------------------------------------------------------\n");
    getch();
}

void heap_sort(Produto *vetor) {
    int i, atual;
    
    
    BuildHeap(vetor);
    mostra_heap(vetor);

    for(i = TAMANHO_VETOR - 1; i > 0; i--) {
        troca(&vetor[0], &vetor[i]); 

        atual = 0;
        while(direito(atual) <= (i - 1) && 
              (strcmp(vetor[atual].nome, vetor[esquerdo(atual)].nome) < 0 || 
               strcmp(vetor[atual].nome, vetor[direito(atual)].nome) < 0)) {
            
            if(strcmp(vetor[esquerdo(atual)].nome, vetor[direito(atual)].nome) > 0) {
                troca(&vetor[atual], &vetor[esquerdo(atual)]);
                atual = esquerdo(atual);
            } else {
                troca(&vetor[atual], &vetor[direito(atual)]);
                atual = direito(atual);
            }
        }

        if(esquerdo(atual) <= i - 1 && strcmp(vetor[atual].nome, vetor[esquerdo(atual)].nome) < 0) {
            troca(&vetor[atual], &vetor[esquerdo(atual)]);
            atual = esquerdo(atual);
        }
    }
}

void geraArquivoDAT (void)
{
	FILE *Arq;
	Arq = fopen("heap.DAT", "w");
	if (Arq == NULL)
	{
		printf ("\nErro ao criar heap.DAT!");
		getch();
		exit(0);
	}
	fwrite(&produtos, sizeof(produtos), 1, Arq);
	fclose(Arq);
}

int main() {
    // Inicialização do vetor (matriz de registros) com os 20 produtos
   

    printf("--- LISTA DE PRODUTOS ---\n");
    printf("%-6s | %-15s | %-10s\n", "Codigo", "Nome", "Preco (R$)");
    printf("------------------------------------\n");
	int i;
    for (i = 0; i < 20; i++) {
        printf("%-6d | %-15s | R$ %8.2f\n", 
               produtos[i].codigo, 
               produtos[i].nome, 
               produtos[i].preco);
    }
    printf("\n\n");
    heap_sort(produtos);
	for (i = 0; i < 20; i++) {
        printf("%-6d | %-15s | R$ %8.2f\n", 
               produtos[i].codigo, 
               produtos[i].nome, 
               produtos[i].preco);
    }
    printf("criando dat");
    geraArquivoDAT();
    return 0;
}
