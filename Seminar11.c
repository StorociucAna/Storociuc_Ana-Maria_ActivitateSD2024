/*#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct Elev Elev;
typedef struct Nod Nod;
struct Elev {
	int id;
	int nrMedii;
	float* medii;
};

struct Nod {
	Elev info;
	Nod* stanga;
	Nod* dreapta;
};

void inserareArbore(Nod** radacina, Elev e) {
	if ((*radacina) != NULL) {
		if ((*radacina)->info.id > e.id) {
			inserareArbore(&((*radacina)->stanga), e);
		}
		else {
			inserareArbore(&((*radacina)->dreapta), e);
		}
		int grad = gradEchilibru((*radacina));
		if (grad == 2) {
			if (gradEchilibru((*radacina)->stanga) == 1) {
				(*radacina) = rotireDreapta((*radacina));
			}
			else {
				(*radacina)->stanga = rotireStanga((*radacina)->stanga);
				(*radacina) = rotireDreapta((*radacina));
			}
		}
		else if (grad == -2) {
			if (gradEchilibru((*radacina)->dreapta) == 1) {
				(*radacina)->dreapta = rotireDreapta((*radacina)->dreapta);
			}
			(*radacina) = rotireStanga((*radacina));
		}
	}
	else {
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = e;
		nod->stanga = NULL;
		nod->dreapta = NULL;

		*radacina = nod;
	}
}

Nod* rotireDreapta(Nod* radacina) {
	Nod* nod = radacina->stanga;
	radacina->stanga = nod->dreapta;
	nod->dreapta = radacina;
	return nod;
}
Nod* rotireStanga(Nod* radacina) {
	Nod* nod;
	nod = radacina->dreapta;
	radacina->dreapta = nod->stanga;
	nod->stanga = radacina;
	return nod;
}
int inaltime(Nod* radacina) {
	if (radacina == NULL) {
		return 0;
	}
	else {
		int inaltimeSt = inaltime(radacina->stanga);
		int inaltimeDr = inaltime(radacina->dreapta);
		if (inaltimeSt > inaltimeDr) {
			return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
		}
	}
}
int gradEchilibru(Nod* radacina) {
	int inaltimeSt = inaltime(radacina->stanga);
	int inaltimeDr = inaltime(radacina->dreapta);
	return inaltimeSt - inaltimeDr;
}


Elev citireElev(FILE* fp) {
	Elev e;
	fscanf(fp, "%d", &e.id);
	fscanf(fp, "%d", &e.nrMedii);
	e.medii = malloc(sizeof(float) * e.nrMedii);
	for (int i = 0; i < e.nrMedii; i++) {
		fscanf(fp, "%f", &e.medii[i]);
	}
	return e;
}

Nod* citireFisier(char* numeFisier) {
	Nod* arbore = NULL;
	if (!numeFisier) {
		return NULL;
	}
	else {
		FILE* fp = fopen(numeFisier, "r");
		int nrElevi;
		fscanf(fp, "%d", &nrElevi);
		for (int i = 0; i < nrElevi; i++) {
			Elev e = citireElev(fp);
			inserareArbore(&arbore, e);
		}
		fclose(fp);
	}
	return arbore;
}
void afisareElev(Elev e) {
	printf("Elevul cu id ul %d are mediile", e.id);
	for (int i = 0; i < e.nrMedii; i++) {
		printf(" %5.2f ", e.medii[i]);
	}
	printf("\n");
}

void afisareInOrder(Nod* arbore) {
	if (arbore != NULL) {
		afisareInOrder(arbore->stanga);
		afisareElev(arbore->info);
		afisareInOrder(arbore->dreapta);
	}
}
float calculeazaMedieElev(Elev e) {
	if (e.nrMedii != 0) {
		float suma = 0;
		for (int i = 0; i < e.nrMedii; i++) {
			suma += e.medii[i];
		}
		return suma / e.nrMedii;
	}
	else {
		printf("elevul nu are medii!");
	}
}
float calculeazaSumaNote(Nod* arbore, int* nrNote) {
	if (arbore != NULL) {
		float suma = 0;
		//r
		for (int i = 0; i < arbore->info.nrMedii; i++) {
			suma += arbore->info.medii[i];
		}
		//s
		float sumaStanga = calculeazaSumaNote(arbore->stanga, nrNote);
		//d
		float sumaDreapta = calculeazaSumaNote(arbore->dreapta, nrNote);
		(*nrNote) += arbore->info.nrMedii;
		return suma + sumaStanga + sumaDreapta;
	}
	else {
		return 0;
	}
}
float calculeazaMedieGenerala(Nod* arbore) {
	int nrNote = 0;
	int suma = calculeazaSumaNote(arbore, &nrNote);
	if (nrNote > 0) {
		return suma / nrNote;
	}
	else {
		return 0;
	}

}
void main() {
	Nod* arbore = citireFisier("Elevi.txt");
	afisareInOrder(arbore);
	printf("Media este: %5.2f", calculeazaMedieGenerala(arbore));
}*/