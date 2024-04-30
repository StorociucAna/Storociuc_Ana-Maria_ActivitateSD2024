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
struct Scoala* citesteVectorScoliFisier(const char* numeFisier, int* dimensiuneVector) {
    FILE* fisier = fopen(numeFisier, "r");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        exit(EXIT_FAILURE);
    }

    int capacitateVector = 10;  // Capacitate ini?ial? arbitrar?
    struct Scoala* vectorScoli = (struct Scoala*)malloc(capacitateVector * sizeof(struct Scoala));
    if (vectorScoli == NULL) {
        printf("Alocare de memorie esuata pentru vectorul de scoli.\n");
        exit(EXIT_FAILURE);
    }

    struct Scoala scoala;
    int index = 0;

    while (fscanf(fisier, "%d", &scoala.cod) == 1) {
        char temp[MAX_LEN];
        if (fscanf(fisier, "%s", temp) != 1) {
            printf("Eroare la citirea denumirii ?colii.\n");
            exit(EXIT_FAILURE);
        }
        scoala.denumire = _strdup(temp);

        if (fscanf(fisier, "%d", &scoala.nrElevi) != 1) {
            printf("Eroare la citirea num?rului de elevi.\n");
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

        // Realocare vector ?i ad?ugare ?coal?, dac? este necesar
        if (index >= capacitateVector) {
            capacitateVector += 10;  // Cre?tere cu un num?r arbitrar
            vectorScoli = (struct Scoala*)realloc(vectorScoli, capacitateVector * sizeof(struct Scoala));
            if (vectorScoli == NULL) {
                printf("Realocare de memorie esuata pentru vectorul de ?coli.\n");
                exit(EXIT_FAILURE);
            }
        }
        vectorScoli[index++] = scoala;
    }

    *dimensiuneVector = index;  // Actualizare dimensiune vector
    fclose(fisier);
    return vectorScoli;
}
char** copiazaSiSorteaza(struct Scoala* vectorScoli, int dimensiuneVector) {
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

        sprintf(matrice[i], "Cod: %d, Denumire: %s, Numar elevi: %d, Numele elevilor: ", vectorScoli[i].cod, vectorScoli[i].denumire, vectorScoli[i].nrElevi);
        for (int j = 0; j < vectorScoli[i].nrElevi; ++j) {
            strcat(matrice[i], vectorScoli[i].numeElevi[j]);
            strcat(matrice[i], ", ");
        }
        // Eliminarea virgulei de la final, dac? exist?
        int len = strlen(matrice[i]);
        if (len > 0 && matrice[i][len - 2] == ',') {
            matrice[i][len - 2] = '\0';
        }
    }

    return matrice;
}

void sorteazaLinii(char** matrice, int dimensiuneMatrice) {
    for (int i = 0; i < dimensiuneMatrice - 1; ++i) {
        for (int j = i + 1; j < dimensiuneMatrice; ++j) {
            if (strlen(matrice[i]) > strlen(matrice[j])) {
                char* temp = matrice[i];
                matrice[i] = matrice[j];
                matrice[j] = temp;
            }
        }
    }
}

void afiseazaMatrice(char** matrice, int dimensiuneMatrice) {
    for (int i = 0; i < dimensiuneMatrice; ++i) {
        printf("%s\n", matrice[i]);
    }
}
int main() {
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

    // Copierea ?i sortarea elementelor într-o matrice
    char** matrice = copiazaSiSorteaza(vectorScoli, dimensiuneVector);

    // Afisarea matricei
    printf("Matricea sortata dupa codul scolii:\n");
    afiseazaMatrice(matrice, dimensiuneVector);

    // Sortarea liniilor matricei dupa numarul de caractere
    sorteazaLinii(matrice, dimensiuneVector);

    // Afisarea matricei dupa sortare
    printf("\nMatricea sortata dupa lungimea liniilor:\n");
    afiseazaMatrice(matrice, dimensiuneVector);

    // Eliberarea memoriei alocate dinamic pentru vectorul de scoli
    for (int i = 0; i < dimensiuneVector; ++i) {
        free(vectorScoli[i].denumire);
        for (int j = 0; j < vectorScoli[i].nrElevi; ++j) {
            free(vectorScoli[i].numeElevi[j]);
        }
        free(vectorScoli[i].numeElevi);
    }
    free(vectorScoli);

    // Eliberarea memoriei alocate dinamic pentru matrice
    for (int i = 0; i < dimensiuneVector; ++i) {
        free(matrice[i]);
    }
    free(matrice);

    return 0;
}*/
