/*#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct Casa {
	int numarCasa;
	char* adresa;
	int nrCamere;
	int* dimensiune;
};
//Functia citire de la tastatura
struct Casa citesteInfoCasa() {
	struct Casa casa;
	printf("Introduceti numarCasa: ");
	scanf("%d", &casa.numarCasa);

	printf("Introduceti adresa: ");
	char temp[100];
	scanf("%s", temp);
	casa.adresa = (char*)malloc(strlen(temp) + 1);
	if (casa.adresa == NULL) {

		printf("Alocare de memorie esuata pentru adresa.\n");
		exit(EXIT_FAILURE);
	}
	strcpy(casa.adresa, temp);

	printf("Introduceti nrCamere: ");
	scanf("%d", &casa.nrCamere);

	casa.dimensiune = (int*)malloc(casa.nrCamere * sizeof(int));
	if (casa.dimensiune == NULL) {
		printf("Alocare dinamica esuata pentru dimensiuni.\n");
		exit(EXIT_FAILURE);
	}
	
	for (int i = 0;i < casa.nrCamere;i++) {
		printf("Introduceti dimensiunile camerei %d: ", i+1);
		scanf("%d", &casa.dimensiune[i]);
	}
	return casa;
}

//functie suma dimensiuni
int sumaDimensiuniCasa(struct Casa casa) {
	int suma = 0;
	for (int i = 0;i < casa.nrCamere;i++) {
		suma = suma + casa.dimensiune[i];
	}
	return suma;
}
void modificaAdresa(struct Casa* casa, char* adresaNoua) {
	free(casa->adresa);
	casa->adresa = (char*)malloc(sizeof(adresaNoua) + 1);
	strcpy(casa->adresa, adresaNoua);
}
void afiseazaInfoCasa(struct Casa casa) {
	printf("Casa are numarul: %d \n", casa.numarCasa);
	printf("Adresa: %s  \n", casa.adresa);
	printf("Numar camere: %d \n", casa.nrCamere);
	for (int i = 0;i < casa.nrCamere;i++) {
		printf("Dimensiune camera %d este : %d \n", i + 1, casa.dimensiune[i]);
	}
}

int main() {
	struct Casa casa1 = citesteInfoCasa();
	int totalDimensiune = sumaDimensiuniCasa(casa1);
	printf("Suma dimensiunilor camerelor este: %d\n", totalDimensiune);
	afiseazaInfoCasa(casa1);
	modificaAdresa(&casa1, "Adresa noua");
	afiseazaInfoCasa(casa1);

}*/