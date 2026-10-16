/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* Constantes */
#define TOTALELEMENTOS 18

/* Tipos pré-definidos */
typedef struct {
    int idSatelite;
    char nomeSatelite[70];
    char paisOperador[30];
    float altitudeOrbitaKm;
} regSatelite;

/* Variáveis globais */
regSatelite listaSatelites[TOTALELEMENTOS] = {
    { 1, "Hubble Space Telescope", 				"Estados Unidos",	540.5    },
    { 2, "ISS (Estacao Espacial Internacional)","Internacional",  	408.2    },
    { 3, "James Webb Space Telescope", 			"Estados Unidos", 	1500000.0},
    { 4, "Sentinel-6", 							"Uniao Europeia", 	1336.0   },
    { 5, "NOAA-20", 							"Estados Unidos", 	824.7    },
    { 6, "CBERS-4A", 							"Brasil / China", 	629.0    },
    { 7, "Starlink-1012", 						"Estados Unidos", 	550.0    },
    { 8, "GOES-16", 							"Estados Unidos", 	35786.0  },
    { 9, "Amazonia-1", 							"Brasil", 			752.4    },
    {10, "Meteosat-11", 						"Uniao Europeia", 	35793.2  },
    {11, "Landsat 9", 							"Estados Unidos", 	705.0    },
    {12, "TerraSAR-X", 							"Alemanha", 		514.8    },
    {13, "Envisat", 							"Uniao Europeia", 	782.4    },
    {14, "RADARSAT-2", 							"Canada", 			798.0    },
    {15, "Jason-3", 							"Franca / EUA", 	1336.5   },
    {16, "ALOS-2 (Daichi-2)", 					"Japao", 			628.0    },
    {17, "Inmarsat-5 F4", 						"Reino Unido", 		35786.5  },
    {18, "CALIPSO", 							"Franca / EUA", 	705.2    }
};

/* Funções */
void ordenaSatelitesAltitudeOrbita(int inicio, int fim);

void mostraSatelites (void)
{   int i;
    system("cls");
    system ("color 0b");
	printf ("\nidSatelite\t\t\tnomeSatelite\t\t\t\t\tpaisOrigemSatelite\taltitudeDeOrbita");
	printf ("\n===============================================================================================================================");
	for(i=0; i<TOTALELEMENTOS; i++)
	{
		printf ("\n%2i\t%-70s\t%-30s\t%10.2f", 
		listaSatelites[i].idSatelite,   listaSatelites[i].nomeSatelite, 
		listaSatelites[i].paisOperador, listaSatelites[i].altitudeOrbitaKm);
	}
	printf ("\n===============================================================================================================================");
	getch();
}

void merge (regSatelite * vetor, int inicio, int meio, int fim){
  int tamEsq, tamDir, i, idxEsq, idxDir;
  regSatelite *vetor_Esq;
  regSatelite *vetor_Dir;
  tamEsq = meio - inicio + 1; /* tamanho do subvetor esquerdo */
  tamDir = fim  - meio;       /* tamanho do subvetor direito  */	
  /* Tenta alocar tamEsq posições para abastecer o subvetor esquerdo */   
  vetor_Esq = (regSatelite *) malloc (tamEsq * sizeof (regSatelite)); 
  if (vetor_Esq == NULL)
  { printf ("malloc devolveu NULL!\n");
    getch();
    exit (EXIT_FAILURE);
  }        
  /* Tenta alocar tamDir posições para abastecer o subvetor direito */   
  vetor_Dir = (regSatelite *) malloc (tamDir * sizeof (regSatelite)); 
  if (vetor_Dir == NULL)
  { printf ("malloc devolveu NULL!\n");
    getch();
    exit (EXIT_FAILURE);
  }   
  for (i=0; i<tamEsq; i++)          /* inicializar vetor_Esq */
    vetor_Esq[i] = vetor[inicio+i]; /* elementos do subvetor esquerdo */
  for (i=0; i<tamDir; i++)          /* inicializar vetor_Dir */
    vetor_Dir[i] = vetor[meio+1+i]; /* elementos do subvetor direito */
  idxEsq = 0; /* índice do subvetor auxiliar esquerdo */
  idxDir = 0; /* índice do subvetor auxiliar direito  */
  for ( i=inicio; i<=fim; i++ )     /* intercala os vetores */
    if (idxEsq < tamEsq)
       if (idxDir < tamDir)
          if (vetor_Esq[idxEsq].altitudeOrbitaKm < vetor_Dir[idxDir].altitudeOrbitaKm)
            vetor[i] = vetor_Esq[idxEsq++];
          else
	 vetor[i] = vetor_Dir[idxDir++];
       else
          vetor[i] = vetor_Esq[idxEsq++];
    else
       vetor[i] = vetor_Dir[idxDir++];
}

void ordenaSatelitesAltitudeOrbita(int inicio, int fim)
{ 	
	
  int  meio;
  if ( inicio < fim )
  {
    meio = (inicio + fim) / 2;        /*calcula o meio                        */
    ordenaSatelitesAltitudeOrbita (inicio, meio); /*ordena o subvetor esquerdo            */
    ordenaSatelitesAltitudeOrbita (meio+1, fim ); /*ordena o subvetor direito             */
    merge (listaSatelites, inicio, meio, fim); /*funde os subvetores esquerdo e direito*/
  }

}

void mostraArquivoDAT (void)
{
	FILE 		*Arq;
	regSatelite	reg;
	Arq = fopen("SATELLITES_ORBIT.DAT", "r");
	if (Arq == NULL)
	{
		printf ("\nErro ao ler SATELLITES_ORBIT.DAT!");
		getch();
		exit(0);
	}
    system("cls");
    system ("color b0");	
	printf ("\nidSatelite\t\t\tnomeSatelite\t\t\t\t\tpaisOrigemSatelite\taltitudeDeOrbita");
	printf ("\n===============================================================================================================================");
	while (!feof(Arq))
	{
		fread(&reg, sizeof(reg), 1, Arq);
		if (!feof(Arq))
			printf ("\n%2i\t%-70s\t%-30s\t%10.2f", 
					reg.idSatelite, reg.nomeSatelite, reg.paisOperador, reg.altitudeOrbitaKm );
	}
	printf ("\n===============================================================================================================================");
	fclose(Arq);	
}

void geraArquivoDAT (void)
{
	FILE *Arq;
	Arq = fopen("SATELLITES_ORBIT.DAT", "w");
	if (Arq == NULL)
	{
		printf ("\nErro ao criar SATELLITES_ORBIT.DAT!");
		getch();
		exit(0);
	}
	fwrite(&listaSatelites, sizeof(listaSatelites), 1, Arq);
	fclose(Arq);
}

/* Corpo do programa */
int main()
{
	mostraSatelites();
	ordenaSatelitesAltitudeOrbita(0, 17);	
	geraArquivoDAT ();
	mostraArquivoDAT();
	getch();
	return 0;
}
