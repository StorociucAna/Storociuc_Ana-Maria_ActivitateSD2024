/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

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
    FILE* fisier = fopen(numeFisier, "r");

    if (fisier != NULL) {
        (*nrCase) = 0;
        char buffer[MAX_LEN];

        while (fgets(buffer, MAX_LEN, fisier) != NULL) {
            struct Casa casa;

            char* token = strtok(buffer, ",");
            casa.numarCasa = atoi(token);

            token = strtok(NULL, ",");
            casa.adresa = _strdup(token);

            token = strtok(NULL, ",");
            casa.nrCamere = atoi(token);

            casa.dimensiune = (int*)malloc(casa.nrCamere * sizeof(int));
            if (casa.dimensiune == NULL) {
                printf("Eroare la alocarea memoriei pentru dimensiunile camerelor.\n");
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < casa.nrCamere; ++i) {
                token = strtok(NULL, ",");
                casa.dimensiune[i] = atoi(token);
            }

            vectorCase = adaugaCasa(vectorCase, casa, nrCase);
        }

        fclose(fisier);
    }

    return vectorCase;
}
char** copiazaSiSorteaza(struct Casa* vector, int dimensiuneVector) {
    char** matrice = (char**)malloc(dimensiuneVector * sizeof(char*));
    if (matrice == NULL) {
        printf("Alocare de memorie esuata pentru matrice.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dimensiuneVector; ++i) {
        matrice[i] = (char*)malloc(MAX_LEN * sizeof(char));
        if (matrice[i] == NULL) {
            printf("Alocare de memorie esuata pentru linia %d a matricei.\n", i + 1);
            exit(EXIT_FAILURE);
        }

        // Concatenarea informațiilor
        sprintf(matrice[i], "Numar casa: %d, Adresa: %s, Numar camere: %d, Dimensiuni camere: ", vector[i].numarCasa, vector[i].adresa, vector[i].nrCamere);
        for (int j = 0; j < vector[i].nrCamere; ++j) {
            char temp[MAX_LEN];
            sprintf(temp, "%d, ", vector[i].dimensiune[j]);
            strcat(matrice[i], temp);
        }
        // Eliminarea virgulei de la final, dacă există
        int len = strlen(matrice[i]);
        if (len > 0 && matrice[i][len - 2] == ',') {
            matrice[i][len - 2] = '\0';
        }
    }

    return matrice;
}
int cmp(const void* a, const void* b) {
    const char* strA = *(const char**)a;
    const char* strB = *(const char**)b;
    return strlen(strA) - strlen(strB);
}

void sorteazaLinii(char** matrice, int dimensiuneMatrice) {
    qsort(matrice, dimensiuneMatrice, sizeof(char*), cmp);
}
void afisareMatrice(char** matrice, int dimensiuneMatrice) {
    for (int i = 0; i < dimensiuneMatrice; ++i) {
        printf("%s\n", matrice[i]);
    }
}
int main() {
    int dimensiune = 0;
    struct Casa* vectorCase = citireFisier("case.txt", &dimensiune);

    char** matrice = copiazaSiSorteaza(vectorCase, dimensiune);
    printf("Matricea inainte de sortare:\n");
    afisareMatrice(matrice, dimensiune);

    sorteazaLinii(matrice, dimensiune);
    printf("\nMatricea dupa sortare:\n");
    afisareMatrice(matrice, dimensiune);

    // Eliberarea memoriei alocate dinamic
    for (int i = 0; i < dimensiune; ++i) {
        free(vectorCase[i].adresa);
        free(vectorCase[i].dimensiune);
    }
    free(vectorCase);

    // Eliberarea memoriei alocate dinamic pentru matrice
    for (int i = 0; i < dimensiune; ++i) {
        free(matrice[i]);
    }
    free(matrice);

    return 0;
}*/