/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Casa {
    int numarCasa;
    char* adresa;
    int nrCamere;
    int* dimensiune;
};

struct Casa* adaugaCasa(struct Casa* vector, struct Casa casa, int* dimensiune) {
    struct Casa* copie = (struct Casa*)malloc(sizeof(struct Casa) * ((*dimensiune) + 1));

    for (int i = 0; i < (*dimensiune); i++) {
        copie[i] = vector[i];
    }
    copie[(*dimensiune)] = casa;
    (*dimensiune)++;

    if (vector)
        free(vector);

    return copie;
}

struct Casa* citireFisier(const char* numeFisier, int* nrCase) {
    struct Casa* vectorCase = NULL;
    vectorCase = NULL;

    FILE* f = fopen(numeFisier, "r");

    if (f != NULL) {
        (*nrCase) = 0;
        char buffer[100];
        while (fgets(buffer, 99, f) != NULL) {
            struct Casa casa;
            char delimitator[] = ",\n";
            char* token = strtok(buffer, delimitator);
            casa.numarCasa = atoi(token);
            token = strtok(NULL, delimitator);
            casa.adresa = _strdup(token);
            token = strtok(NULL, delimitator);
            casa.nrCamere = atoi(token);

            casa.dimensiune = (int*)malloc(casa.nrCamere * sizeof(int));
            if (casa.dimensiune == NULL) {
                printf("Eroare la alocarea memoriei pentru dimensiunile camerelor.\n");
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < casa.nrCamere; ++i) {
                token = strtok(NULL, delimitator);
                casa.dimensiune[i] = atoi(token);
            }

            vectorCase = adaugaCasa(vectorCase, casa, nrCase);
        }
        fclose(f);
    }
    return vectorCase;
}

void afisareCasa(struct Casa* casa) {
    printf("Casa cu numarul: %d, adresa: %s, are %d camere:\n", casa->numarCasa, casa->adresa, casa->nrCamere);
    printf("Dimensiunile camerelor:\n");
    for (int i = 0; i < casa->nrCamere; ++i) {
        printf("- Camera %d: %d\n", i + 1, casa->dimensiune[i]);
    }
}

void afisareVectorCase(struct Casa* vectorCase, int dim) {
    printf("Afisare vector: \n");
    for (int i = 0; i < dim; i++) {
        afisareCasa(&vectorCase[i]);
    }
}

void dezalocareVector(struct Casa** vectorCase, int* dim) {
    for (int i = 0; i < (*dim); i++) {
        free((*vectorCase)[i].adresa);
        free((*vectorCase)[i].dimensiune);
    }
    free(*vectorCase);
    (*vectorCase) = NULL;
    (*dim) = 0;
}

int main() {
    int dimensiune = 3;
    struct Casa* vectorCase = NULL;
    vectorCase = citireFisier("case.txt", &dimensiune);
    afisareVectorCase(vectorCase, dimensiune);
    dezalocareVector(&vectorCase, &dimensiune);

    return 0;
}*/
