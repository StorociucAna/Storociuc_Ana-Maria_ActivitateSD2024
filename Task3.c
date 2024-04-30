/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

struct Scoala {
    int cod;
    char* denumire;
    int nrElevi;
    char** numeElevi;
};

// Funcție pentru citirea unei școli din fișier
struct Scoala citesteScoalaFisier(FILE* fisier) {
    struct Scoala scoala;

    printf("Citind codul școlii...\n");
    if (fscanf(fisier, "%d", &scoala.cod) != 1) {
        printf("Eroare la citirea codului școlii.\n");
        exit(EXIT_FAILURE);
    }
    printf("Codul școlii citit: %d\n", scoala.cod);

    char temp[MAX_LEN];
    printf("Citind denumirea școlii...\n");
    if (fscanf(fisier, "%s", temp) != 1) {
        printf("Eroare la citirea denumirii școlii.\n");
        exit(EXIT_FAILURE);
    }
    scoala.denumire = _strdup(temp);
    printf("Denumirea școlii citită: %s\n", scoala.denumire);

    printf("Citind numărul de elevi...\n");
    if (fscanf(fisier, "%d", &scoala.nrElevi) != 1) {
        printf("Eroare la citirea numărului de elevi.\n");
        exit(EXIT_FAILURE);
    }
    printf("Numărul de elevi citit: %d\n", scoala.nrElevi);

    scoala.numeElevi = (char**)malloc(scoala.nrElevi * sizeof(char*));
    if (scoala.numeElevi == NULL) {
        printf("Eroare la alocarea memoriei pentru numele elevilor.\n");
        exit(EXIT_FAILURE);
    }

    printf("Citind numele elevilor...\n");
    for (int i = 0; i < scoala.nrElevi; ++i) {
        if (fscanf(fisier, "%s", temp) != 1) {
            printf("Eroare la citirea numelui elevului %d.\n", i + 1);
            exit(EXIT_FAILURE);
        }
        scoala.numeElevi[i] = _strdup(temp);
        printf("Numele elevului %d citit: %s\n", i + 1, scoala.numeElevi[i]);
    }

    return scoala;
}

// Funcție pentru a citi obiectele din fișier și a le salva într-un vector
struct Scoala* citesteVectorScoliFisier(const char* numeFisier, int* dimensiuneVector) {
    FILE* fisier;
    if ((fisier = fopen(numeFisier, "r")) == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        exit(EXIT_FAILURE);
    }

    struct Scoala* vectorScoli = NULL;
    struct Scoala scoala;
    int capacitateVector = 0;
    int index = 0;

    while (fscanf(fisier, "%d", &scoala.cod) == 1) {
        char temp[MAX_LEN];
        if (fscanf(fisier, "%s", temp) != 1) {
            printf("Eroare la citirea denumirii școlii.\n");
            exit(EXIT_FAILURE);
        }
        scoala.denumire = _strdup(temp);

        if (fscanf(fisier, "%d", &scoala.nrElevi) != 1) {
            printf("Eroare la citirea numărului de elevi.\n");
            exit(EXIT_FAILURE);
        }

        scoala.numeElevi = (char**)malloc(scoala.nrElevi * sizeof(char*));
        if (scoala.numeElevi == NULL) {
            printf("Alocare de memorie esuata pentru numele elevilor.\n");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < scoala.nrElevi; ++i) {
            if (fscanf(fisier, "%s", temp) != 1) {
                printf("Eroare la citirea numelui elevului %d.\n", i + 1);
                exit(EXIT_FAILURE);
            }
            scoala.numeElevi[i] = _strdup(temp);
        }

        // Realocare vector și adăugare școală
        if (index >= capacitateVector) {
            capacitateVector += 10;  // Creștere cu un număr arbitrar
            vectorScoli = (struct Scoala*)realloc(vectorScoli, capacitateVector * sizeof(struct Scoala));
            if (vectorScoli == NULL) {
                printf("Realocare de memorie esuata pentru vectorul de școli.\n");
                exit(EXIT_FAILURE);
            }
        }
        vectorScoli[index++] = scoala;
    }

    *dimensiuneVector = index;  // Actualizare dimensiune vector
    fclose(fisier);
    return vectorScoli;
}

// Funcție pentru a salva un obiect într-un fișier text
void salveazaScoalaFisier(FILE* fisier, struct Scoala scoala) {
    fprintf(fisier, "%d\n", scoala.cod);
    fprintf(fisier, "%s\n", scoala.denumire);
    fprintf(fisier, "%d\n", scoala.nrElevi);
    for (int i = 0; i < scoala.nrElevi; ++i) {
        fprintf(fisier, "%s\n", scoala.numeElevi[i]);
    }
}

// Funcție pentru a salva un vector de obiecte într-un fișier text
void salveazaVectorScoliFisier(const char* numeFisier, struct Scoala* vectorScoli, int dimensiuneVector) {
    FILE* fisier = fopen(numeFisier, "w");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fisier, "%d\n", dimensiuneVector);
    for (int i = 0; i < dimensiuneVector; ++i) {
        salveazaScoalaFisier(fisier, vectorScoli[i]);
    }

    fclose(fisier);
}

int main() {
    // Citirea obiectelor din fișier și salvarea lor într-un vector
    int dimensiuneVector;
    struct Scoala* vectorScoli = citesteVectorScoliFisier("scoli.txt", &dimensiuneVector);
  

    // Afisarea vectorului de scoli citit din fisier
    printf("Scolile citite din fisier sunt:\n");
    for (int i = 0; i < dimensiuneVector; ++i) {
        printf("Scoala %d:\n", i + 1);
        printf("Cod: %d\n", vectorScoli[i].cod);
        printf("Denumire: %s\n", vectorScoli[i].denumire);
        printf("Numar de elevi: %d\n", vectorScoli[i].nrElevi);
        printf("Numele elevilor:\n");
        for (int j = 0; j < vectorScoli[i].nrElevi; ++j) {
            printf("- Elevul %d: %s\n", j + 1, vectorScoli[i].numeElevi[j]);
        }
        printf("\n");
    }
    salveazaVectorScoliFisier("scoliM.txt", vectorScoli, dimensiuneVector);

    // Eliberarea memoriei alocate dinamic
    for (int i = 0; i < dimensiuneVector; ++i) {
        free(vectorScoli[i].denumire);
        for (int j = 0; j < vectorScoli[i].nrElevi; ++j) {
            free(vectorScoli[i].numeElevi[j]);
        }
        free(vectorScoli[i].numeElevi);
    }
    free(vectorScoli);

    return 0;
}*/
