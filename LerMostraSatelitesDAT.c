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

void ordenaSatelitesAltitudeOrbita(void)
{ 	
	
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
	ordenaSatelitesAltitudeOrbita();	
	geraArquivoDAT ();
	mostraArquivoDAT();
	getch();
	return 0;
}