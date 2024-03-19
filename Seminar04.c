/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct Aeroport {
	int id;
	char* nume;
	int nrTerminale;
};

struct Aeroport* adaugaAeroport(struct Aeroport* vector, struct Aeroport aeroport, int* dimensiune) {
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dimensiune) + 1));

	for (int i = 0; i < (*dimensiune); i++) {
		copie[i] = vector[i];
	}
	copie[(*dimensiune)] = aeroport;
	(*dimensiune)++;
	if (vector)
		free(vector);


	return copie;
}

struct Aeroport* citireFisier(const char* numeFisier, int* nrAeroporturi) {
	struct Aeroport* vectorAeroporturi;
	vectorAeroporturi = NULL;

	//deschidere fisier
	FILE* f = fopen(numeFisier, "r");

	if (f != NULL) {
		(*nrAeroporturi) = 0;
		char buffer[100];
		while (fgets(buffer, 99, f) != NULL) {
			struct Aeroport aeroport;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			aeroport.id = atoi(token);
			token = strtok(NULL, delimitator);
			aeroport.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);
			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);

			vectorAeroporturi = adaugaAeroport(vectorAeroporturi, aeroport, nrAeroporturi);
		}
		fclose(f);
	}
	return vectorAeroporturi;
}

void afisareAeroport(struct Aeroport* aeroport) {
	printf("%d, %s are %d terminale.\t", aeroport->id, aeroport->nume, aeroport->nrTerminale);
}
void afisareVectorAeroporturi(struct Aeroport* aeroporturi, int dim) {
	printf("Afisare vector: \n");
	for (int i = 0; i < dim; i++) {
		afisareAeroport(&aeroporturi[i]);
	}
}

void dezalocareVector(struct Aeroport** aeroporturi, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		free((*aeroporturi)[i].nume);
		free(aeroporturi[i]);
	}
	free(*aeroporturi);
	(*aeroporturi) = NULL;
	(*dim) = 0;
}

void citireMatriceFisier(const char* numeFisier, int* nrAeroporturiLinie, int nrClustere, struct Aeroport** aeroporturi) {


	//deschidere fisier
	FILE* f = fopen(numeFisier, "r");

	if (f != NULL) {
		char buffer[100];
		while (fgets(buffer, 99, f) != NULL) {
			struct Aeroport aeroport;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			aeroport.id = atoi(token);
			token = strtok(NULL, delimitator);
			aeroport.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);
			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);

			int poz = aeroport.nrTerminale % 2;

			aeroporturi[poz] = adaugaAeroport(aeroporturi[poz], aeroport, &(nrAeroporturiLinie[poz]));
		}
		fclose(f);
	}
}

void afisareMatrice(struct Aeroport** matrice, int nrClustere, int* nrColoane) {
	for (int i = 0; i < nrClustere; i++) {
		for (int j = 0; j < nrColoane; j++) {
			afisareAeroport(&matrice[i][j]);
		}
		printf("\n");
	}
}
float mediaTerminale(struct Aeroport** matrice, int nrClustere, int* nrAeroporturiLinie, int paritate) {
	paritate = paritate % 2;
	int suma = 0;
	for (int i = 0; i < nrAeroporturiLinie[paritate]; i++) {
		suma += matrice[paritate][i].nrTerminale;
	}
	if (nrAeroporturiLinie[paritate]) {
		return suma / nrAeroporturiLinie[paritate];
	}
	return 0;
}

struct Aeroport* cautaAeroportID(struct Aeroport** matrice, int* nrColoane, int nrLinii, int ID) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++)
		{
			if (matrice[i][j].id == ID) {
				return &(matrice[i][j]);
			}
		}
	}
}

void dezalocareMatrice(struct Aeroport*** matrice, int** nrColoane, int* nrClustere) {
	for (int i = 0; i < (*nrClustere); i++) {
		dezalocareVector(&((*matrice)[i]), &((*nrColoane)[i]));
	}
	free(*matrice);
	(*matrice) = NULL;
	free(*nrColoane);
	(*nrColoane) = NULL;
	(*nrClustere) = 0;
}
void main() {

	struct Aeroport** aeroporturi;
	int nrLinii = 2;
	int* nrColoane = (int*)malloc(sizeof(int));

	aeroporturi = (struct Aeroport**)malloc(sizeof(struct Aeroport*) * nrLinii);
	for (int i = 0; i < nrLinii; i++) {
		nrColoane[i] = 0;
		aeroporturi[i] = NULL;
	}
	citireMatriceFisier("aeroporturi.txt", nrColoane, nrLinii, aeroporturi);
	afisareMatrice(aeroporturi, nrLinii, nrColoane);
	float medie = mediaTerminale(aeroporturi, nrLinii, nrColoane, 12);
	printf("Media paritate: %.2f", medie);
	printf("\n\n");
	afisareAeroport(cautaAeroportID(aeroporturi, nrColoane, nrLinii, 2));
	dezalocareMatrice(&aeroporturi, &nrColoane, &nrLinii);


}*/