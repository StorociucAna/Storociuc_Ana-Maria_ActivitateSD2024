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
	scanf("%s", temp, sizeof(temp));
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
		printf("Introduceti dimensiunile camerei %d: ", i + 1);
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

struct Casa* copiazaCase(struct Casa* vector, int dimensiuneVector, int nrCamere, int* dimensiuneVectorNoua) {
	int numarCase = 0;
	for (int i = 0; i <= dimensiuneVector;i++) {
		if (vector[i].nrCamere == nrCamere) {
			numarCase = numarCase + 1;
		}
	}

	struct Casa* vectorNou = (struct Casa*)malloc(numarCase * sizeof(struct Casa));

	int index = 0;
	for (int i = 0; i <= dimensiuneVector; i++) {
		if (vector[i].nrCamere == nrCamere) {
			vectorNou[index++] = vector[i];
		}
	}
	*dimensiuneVectorNoua = numarCase;
	return vectorNou;
}
struct Casa* copiazaCaseDimensiuniEgale(struct Casa* vector, int dimensiuneVector, int sumaDimensiuni, int* dimensiuneVectorNoua) {
	int numarCaseVectorNou = 0;
	for (int i = 0; i <= dimensiuneVector; i++) {
		if (sumaDimensiuniCasa(vector[i]) == sumaDimensiuni) {
			numarCaseVectorNou++;
		}
	}
	struct Casa* vectorNou = (struct Casa*)malloc(numarCaseVectorNou * sizeof(struct Casa));
	int index = 0;
	for (int i = 0; i <= dimensiuneVector; i++) {
		if (sumaDimensiuniCasa(vector[i]) == sumaDimensiuni) {
			vectorNou[index++] = vector[i];
		}
	}
	*dimensiuneVectorNoua = numarCaseVectorNou;
	return vectorNou;
}
struct Casa* concatenareVectori(struct Casa* vector1, int dimensiuneVector1, struct Casa* vector2, int dimensiuneVector2) {
	struct Casa* vectorNou = (struct Casa*)malloc((dimensiuneVector1 + dimensiuneVector2) * sizeof(struct Casa*));
	if (vectorNou == NULL) {
		printf("Alocare de memorie esuata.\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < dimensiuneVector1; i++) {
		vectorNou[i] = vector1[i];
	}
	for (int i = 0; i < dimensiuneVector2;i++) {
		vectorNou[dimensiuneVector1 + i] = vector2[i];
	}
	return vectorNou;
}

int main() {
	int dimensiuneVector = 5;
	struct Casa* vectorCasa = (struct Casa*)malloc(dimensiuneVector * sizeof(struct Casa));

	printf("Introducti date pentru case: ");
	for (int i = 0;i < dimensiuneVector;i++) {
		printf("Casa %d : ", i + 1);
		vectorCasa[i] = citesteInfoCasa();
	}

	printf("Afisare case: \n\n");
	for (int i = 0;i < dimensiuneVector;i++) {
		printf("Casa %d : ", i + 1);
		afiseazaInfoCasa(vectorCasa[i]);
	}
	int dimensiuneVectorNoua;
	int nrCamere = 3;
	struct Casa* vectorCuNumarCamereDorit = copiazaCase(vectorCasa, dimensiuneVector, nrCamere, &dimensiuneVectorNoua);
	printf("Afisare case vector cu numar camere dorit: \n\n");
	for (int i = 0;i < dimensiuneVectorNoua;i++) {
		printf("Casa %d : ", i + 1);
		afiseazaInfoCasa(vectorCuNumarCamereDorit[i]);
	}

	int dimensiuneVectorNoua2;
	int sumaDimensiuni = 50;
	struct Casa* vectorCuDimensiuniEgale = copiazaCaseDimensiuniEgale(vectorCasa, dimensiuneVector, sumaDimensiuni, &dimensiuneVectorNoua2);
	printf("Afiseaza vector cu dimensiuni egale: \n\n");
	for (int i = 0;i < dimensiuneVectorNoua2;i++) {
		printf("Casa %d : ", i + 1);
		afiseazaInfoCasa(vectorCuDimensiuniEgale[i]);
	}

	struct Casa* vectorConcatenat = concatenareVectori(vectorCuNumarCamereDorit, dimensiuneVectorNoua, vectorCuDimensiuniEgale, dimensiuneVectorNoua2);
	printf("Afiseaza vectorul concatenat\n\n");
	for (int i = 0; i < dimensiuneVectorNoua + dimensiuneVectorNoua2; i++) {
		printf("Casa %d : ", i + 1);
		afiseazaInfoCasa(vectorConcatenat[i]);
	}

	return 0;
}*/