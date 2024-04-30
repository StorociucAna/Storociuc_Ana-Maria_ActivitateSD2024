/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Scoala {
    int cod;
    char* denumire;
    int nrElevi;
    char** numeElevi;
};

// Funcție pentru citirea unei școli de la tastatură
struct Scoala citesteScoala() {
    struct Scoala scoala;

    printf("Introduceti codul: ");
    scanf("%d", &scoala.cod);

    printf("Introduceti denumirea: ");
    char temp[100];
    scanf("%s", temp);
    scoala.denumire = (char*)malloc(strlen(temp) + 1);
    strcpy(scoala.denumire, temp);

    printf("Introduceti numarul de elevi: ");
    scanf("%d", &scoala.nrElevi);

    scoala.numeElevi = (char**)malloc(scoala.nrElevi * sizeof(char*));
    printf("Introduceti numele elevilor:\n");
    for (int i = 0; i < scoala.nrElevi; ++i) {
        printf("Numele elevului %d: ", i + 1);
        char nume[100];
        scanf("%s", nume);
        scoala.numeElevi[i] = (char*)malloc(strlen(nume) + 1);
        strcpy(scoala.numeElevi[i], nume);
    }

    return scoala;
}

// Funcție pentru a elibera memoria alocată pentru o școală
void elibereazaScoala(struct Scoala* scoala) {
    free(scoala->denumire);
    for (int i = 0; i < scoala->nrElevi; ++i) {
        free(scoala->numeElevi[i]);
    }
    free(scoala->numeElevi);
}

// Funcție pentru a afișa o școală
void afiseazaScoala(struct Scoala scoala) {
    printf("Cod: %d\n", scoala.cod);
    printf("Denumire: %s\n", scoala.denumire);
    printf("Numar de elevi: %d\n", scoala.nrElevi);
    printf("Numele elevilor:\n");
    for (int i = 0; i < scoala.nrElevi; ++i) {
        printf("- Elevul %d: %s\n", i + 1, scoala.numeElevi[i]);
    }
}

// Funcție pentru a copia școlile care îndeplinesc o anumită condiție într-un nou vector
struct Scoala* copiazaScolile(struct Scoala* vector, int dimensiune, int* dimensiuneNoua, int codCautat) {
    *dimensiuneNoua = 0;
    for (int i = 0; i < dimensiune; ++i) {
        if (vector[i].cod == codCautat) {
            (*dimensiuneNoua)++;
        }
    }

    struct Scoala* vectorNou = (struct Scoala*)malloc(*dimensiuneNoua * sizeof(struct Scoala));
    if (vectorNou == NULL) {
        printf("Alocare de memorie esuata.\n");
        exit(EXIT_FAILURE);
    }

    int indexNou = 0;
    for (int i = 0; i < dimensiune; ++i) {
        if (vector[i].cod == codCautat) {
            vectorNou[indexNou++] = vector[i];
        }
    }

    return vectorNou;
}

// Funcție pentru a muta școlile care îndeplinesc o anumită condiție într-un nou vector
struct Scoala* mutaScolile(struct Scoala* vector, int dimensiune, int* dimensiuneNoua, int nrMinimElevi) {
    *dimensiuneNoua = 0;
    for (int i = 0; i < dimensiune; ++i) {
        if (vector[i].nrElevi >= nrMinimElevi) {
            (*dimensiuneNoua)++;
        }
    }

    struct Scoala* vectorNou = (struct Scoala*)malloc(*dimensiuneNoua * sizeof(struct Scoala));
    if (vectorNou == NULL) {
        printf("Alocare de memorie esuata.\n");
        exit(EXIT_FAILURE);
    }

    int indexNou = 0;
    for (int i = 0; i < dimensiune; ++i) {
        if (vector[i].nrElevi >= nrMinimElevi) {
            vectorNou[indexNou++] = vector[i];
        }
    }

    return vectorNou;
}

// Funcție pentru a concatena doi vectori de școli
struct Scoala* concateneazaVectori(struct Scoala* vector1, int dimensiune1, struct Scoala* vector2, int dimensiune2) {
    struct Scoala* vectorNou = (struct Scoala*)malloc((dimensiune1 + dimensiune2) * sizeof(struct Scoala));
    if (vectorNou == NULL) {
        printf("Alocare de memorie esuata.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dimensiune1; ++i) {
        vectorNou[i] = vector1[i];
    }

    for (int i = 0; i < dimensiune2; ++i) {
        vectorNou[dimensiune1 + i] = vector2[i];
    }

    return vectorNou;
}

int main() {
    int dimensiuneVector = 2;
    struct Scoala* vectorScoli = (struct Scoala*)malloc(dimensiuneVector * sizeof(struct Scoala));

    printf("Introduceti datele pentru scoli:\n");
    for (int i = 0; i < dimensiuneVector; ++i) {
        printf("Scoala %d:\n", i + 1);
        vectorScoli[i] = citesteScoala();
    }

    printf("\nScolile citite sunt:\n");
    for (int i = 0; i < dimensiuneVector; ++i) {
        printf("Scoala %d:\n", i + 1);
        afiseazaScoala(vectorScoli[i]);
    }

    // Exemplu de copiere a școlilor cu un anumit cod într-un nou vector
    int dimensiuneNoua;
    int codCautat = 1; // Codul școlii căutate
    struct Scoala* vectorScoliCod = copiazaScolile(vectorScoli, dimensiuneVector, &dimensiuneNoua, codCautat);
    printf("\nScolile cu codul %d sunt:\n", codCautat);
    for (int i = 0; i < dimensiuneNoua; ++i) {
        printf("Scoala %d:\n", i + 1);
        afiseazaScoala(vectorScoliCod[i]);
    }
    free(vectorScoliCod);

    // Exemplu de mutare a școlilor cu un număr minim de elevi într-un nou vector
    int nrMinimElevi = 2; // Numărul minim de elevi pentru mutare
    struct Scoala* vectorScoliNrMinim = mutaScolile(vectorScoli, dimensiuneVector, &dimensiuneNoua, nrMinimElevi);
    printf("\nScolile cu cel putin %d elevi sunt:\n", nrMinimElevi);
    for (int i = 0; i < dimensiuneNoua; ++i) {
        printf("Scoala %d:\n", i + 1);
        afiseazaScoala(vectorScoliNrMinim[i]);
    }
    free(vectorScoliNrMinim);

    // Exemplu de concatenare a doi vectori de școli
    struct Scoala* vectorScoliConcatenat = concateneazaVectori(vectorScoli, dimensiuneVector, vectorScoli, dimensiuneVector);
    printf("\nVectorul de scoli concatenat:\n");
    for (int i = 0; i < dimensiuneVector * 2; ++i) {
        printf("Scoala %d:\n", i + 1);
        afiseazaScoala(vectorScoliConcatenat[i]);
    }
    free(vectorScoliConcatenat);

    // Eliberare memorie alocată dinamic
    for (int i = 0; i < dimensiuneVector; ++i) {
        elibereazaScoala(&vectorScoli[i]);
    }
    free(vectorScoli);

    return 0;
}*/
