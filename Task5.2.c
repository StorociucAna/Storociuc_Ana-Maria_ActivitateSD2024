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

struct Nod {
    struct Casa* casa;
    struct Nod* urmator;
};

struct ListaSimpluInlantuita {
    struct Nod* primul;
};

// Functie pentru crearea unui nod nou
struct Nod* creareNod(struct Casa* casa) {
    struct Nod* nod = (struct Nod*)malloc(sizeof(struct Nod));
    if (nod == NULL) {
        printf("Eroare la alocarea memoriei pentru un nou nod.\n");
        exit(EXIT_FAILURE);
    }
    nod->casa = casa;
    nod->urmator = NULL;
    return nod;
}

// Functie pentru adaugarea unui nod la finalul listei
void adaugaNod(struct ListaSimpluInlantuita* lista, struct Casa* casa) {
    struct Nod* nou = creareNod(casa);
    if (lista->primul == NULL) {
        lista->primul = nou;
    }
    else {
        struct Nod* curent = lista->primul;
        while (curent->urmator != NULL) {
            curent = curent->urmator;
        }
        curent->urmator = nou;
    }
}

// Functie pentru citirea datelor din fisier si adaugarea acestora in lista
void citireSiAdaugareInLista(const char* numeFisier, struct ListaSimpluInlantuita* lista) {
    FILE* fisier = fopen(numeFisier, "r");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fisier) != NULL) {
        int numarCasa, nrCamere;
        char adresa[100];
        int dimensiuni[10];

        sscanf(buffer, "%d,%99[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d",
            &numarCasa, adresa, &nrCamere,
            &dimensiuni[0], &dimensiuni[1], &dimensiuni[2], &dimensiuni[3], &dimensiuni[4],
            &dimensiuni[5], &dimensiuni[6], &dimensiuni[7], &dimensiuni[8], &dimensiuni[9]);

        // Alocare casa si adaugare in lista
        struct Casa* casa = (struct Casa*)malloc(sizeof(struct Casa));
        if (casa == NULL) {
            printf("Eroare la alocarea memoriei pentru o casa.\n");
            exit(EXIT_FAILURE);
        }
        casa->numarCasa = numarCasa;
        casa->adresa = _strdup(adresa);
        casa->nrCamere = nrCamere;
        casa->dimensiune = (int*)malloc(nrCamere * sizeof(int));
        if (casa->dimensiune == NULL) {
            printf("Eroare la alocarea memoriei pentru dimensiunile camerelor.\n");
            exit(EXIT_FAILURE);
        }
        memcpy(casa->dimensiune, dimensiuni, nrCamere * sizeof(int));

        adaugaNod(lista, casa);
    }

    fclose(fisier);
}

// Functie pentru afisarea listei
void afisareLista(struct ListaSimpluInlantuita* lista) {
    struct Nod* curent = lista->primul;
    while (curent != NULL) {
        printf("Numar casa: %d, Adresa: %s, Numar camere: %d\n", curent->casa->numarCasa, curent->casa->adresa, curent->casa->nrCamere);
        curent = curent->urmator;
    }
}

// Functie pentru dezalocarea memoriei ocupate de lista
void dezalocareLista(struct ListaSimpluInlantuita* lista) {
    struct Nod* curent = lista->primul;
    while (curent != NULL) {
        struct Nod* temp = curent;
        curent = curent->urmator;
        free(temp->casa->adresa);
        free(temp->casa->dimensiune);
        free(temp->casa);
        free(temp);
    }
    lista->primul = NULL;
}

// Functie pentru stergerea unui nod de pe o pozitie data
void stergeNod(struct ListaSimpluInlantuita* lista, int index) {
    if (lista->primul == NULL) {
        printf("Lista este goala, nu exista elemente de sters.\n");
        return;
    }

    struct Nod* curent = lista->primul;
    struct Nod* anterior = NULL;
    int pozitie = 0;

    while (curent != NULL && pozitie != index) {
        anterior = curent;
        curent = curent->urmator;
        pozitie++;
    }

    if (curent == NULL) {
        printf("Indexul dat depaseste lungimea listei, nu se poate realiza stergerea.\n");
        return;
    }

    if (anterior == NULL) {
        lista->primul = curent->urmator;
    }
    else {
        anterior->urmator = curent->urmator;
    }

    free(curent->casa->adresa);
    free(curent->casa->dimensiune);
    free(curent->casa);
    free(curent);
}

// Functie pentru inserarea unei case in lista astfel incat sa fie sortate crescator dupa numarul casei
void inserareSortata(struct ListaSimpluInlantuita* lista, struct Casa* casa) {
    struct Nod* nou = creareNod(casa);
    if (lista->primul == NULL || lista->primul->casa->numarCasa >= casa->numarCasa) {
        nou->urmator = lista->primul;
        lista->primul = nou;
    }
    else {
        struct Nod* curent = lista->primul;
        while (curent->urmator != NULL && curent->urmator->casa->numarCasa < casa->numarCasa) {
            curent = curent->urmator;
        }
        nou->urmator = curent->urmator;
        curent->urmator = nou;
    }
}

// Functie care verifica daca o casa indeplineste o anumita conditie (numarul de camere >= 3)
int indeplinesteConditia(struct Casa* casa) {
    return casa->nrCamere >= 3;
}

// Functie pentru copierea in vector a caselor care indeplinesc o anumita conditie
struct Casa** copiereCasaInVector(struct ListaSimpluInlantuita* lista, int* dimensiuneVector, int (*conditie)(struct Casa*)) {
    struct Nod* curent = lista->primul;
    *dimensiuneVector = 0;

    while (curent != NULL) {
        if (conditie(curent->casa)) {
            (*dimensiuneVector)++;
        }
        curent = curent->urmator;
    }

    struct Casa** vector = (struct Casa**)malloc((*dimensiuneVector) * sizeof(struct Casa*));
    if (vector == NULL) {
        printf("Eroare la alocarea memoriei pentru vector.\n");
        exit(EXIT_FAILURE);
    }

    curent = lista->primul;
    int index = 0;
    while (curent != NULL) {
        if (conditie(curent->casa)) {
            vector[index] = (struct Casa*)malloc(sizeof(struct Casa));
            if (vector[index] == NULL) {
                printf("Eroare la alocarea memoriei pentru o casa in vector.\n");
                exit(EXIT_FAILURE);
            }
            vector[index]->numarCasa = curent->casa->numarCasa;
            vector[index]->adresa = _strdup(curent->casa->adresa);
            vector[index]->nrCamere = curent->casa->nrCamere;
            vector[index]->dimensiune = (int*)malloc(curent->casa->nrCamere * sizeof(int));
            if (vector[index]->dimensiune == NULL) {
                printf("Eroare la alocarea memoriei pentru dimensiunile camerelor in vector.\n");
                exit(EXIT_FAILURE);
            }
            memcpy(vector[index]->dimensiune, curent->casa->dimensiune, curent->casa->nrCamere * sizeof(int));
            index++;
        }
        curent = curent->urmator;
    }

    return vector;
}

// Functie pentru interschimbarea a doua noduri din lista
void interschimbareNoduri(struct ListaSimpluInlantuita* lista, int pozitie1, int pozitie2) {
    if (pozitie1 == pozitie2) {
        printf("Pozitiile sunt egale, nu este necesara interschimbarea.\n");
        return;
    }

    int minPozitie = (pozitie1 < pozitie2) ? pozitie1 : pozitie2;
    int maxPozitie = (pozitie1 > pozitie2) ? pozitie1 : pozitie2;

    if (minPozitie < 0 || maxPozitie < 0) {
        printf("Pozitiile trebuie sa fie pozitive.\n");
        return;
    }

    struct Nod* nod1 = lista->primul;
    struct Nod* nod2 = lista->primul;
    struct Nod* anterior1 = NULL;
    struct Nod* anterior2 = NULL;
    int pozitie = 0;

    while (nod1 != NULL && pozitie < minPozitie) {
        anterior1 = nod1;
        nod1 = nod1->urmator;
        pozitie++;
    }

    pozitie = 0;

    while (nod2 != NULL && pozitie < maxPozitie) {
        anterior2 = nod2;
        nod2 = nod2->urmator;
        pozitie++;
    }

    if (nod1 == NULL || nod2 == NULL) {
        printf("Una dintre pozitii depaseste lungimea listei.\n");
        return;
    }

    if (anterior1 != NULL) {
        anterior1->urmator = nod2;
    }
    else {
        lista->primul = nod2;
    }

    if (anterior2 != NULL) {
        anterior2->urmator = nod1;
    }
    else {
        lista->primul = nod1;
    }

    struct Nod* temp = nod1->urmator;
    nod1->urmator = nod2->urmator;
    nod2->urmator = temp;
}

int main() {
    // Initializare lista
    struct ListaSimpluInlantuita lista;
    lista.primul = NULL;

    // Citire din fisier si adaugare in lista
    citireSiAdaugareInLista("case.txt", &lista);

    // Afisare lista
    printf("Lista initiala:\n");
    afisareLista(&lista);
    printf("\n");

    // Stergere nod de pe o pozitie data
    stergeNod(&lista, 1);
    printf("Lista dupa stergerea nodului de pe pozitia 1:\n");
    afisareLista(&lista);
    printf("\n");

    // Inserare sortata dupa numarul casei
    struct Casa* casaNoua = (struct Casa*)malloc(sizeof(struct Casa));
    if (casaNoua == NULL) {
        printf("Eroare la alocarea memoriei pentru o casa noua.\n");
        exit(EXIT_FAILURE);
    }
    casaNoua->numarCasa = 4;
    casaNoua->adresa = _strdup("Strada Unirii");
    casaNoua->nrCamere = 3;
    casaNoua->dimensiune = (int*)malloc(casaNoua->nrCamere * sizeof(int));
    casaNoua->dimensiune[0] = 15;
    casaNoua->dimensiune[1] = 18;
    casaNoua->dimensiune[2] = 20;
    inserareSortata(&lista, casaNoua);
    printf("Lista dupa inserarea sortata:\n");
    afisareLista(&lista);
    printf("\n");

    // Copierea in vector a caselor care indeplinesc o anumita conditie (in acest caz, numarul de camere >= 3)
    int dimensiuneVector;
    struct Casa** vector = copiereCasaInVector(&lista, &dimensiuneVector, &indeplinesteConditia);
    printf("Vectorul de case cu numarul de camere >= 3:\n");
    for (int i = 0; i < dimensiuneVector; ++i) {
        printf("Numar casa: %d, Adresa: %s, Numar camere: %d\n", vector[i]->numarCasa, vector[i]->adresa, vector[i]->nrCamere);
        free(vector[i]->adresa);
        free(vector[i]->dimensiune);
        free(vector[i]);
    }
    free(vector);
    printf("\n");

    // Interschimbare noduri din lista
    interschimbareNoduri(&lista, 0, 2);
    printf("Lista dupa interschimbarea nodurilor de pe pozitiile 0 si 2:\n");
    afisareLista(&lista);
    printf("\n");

    // Dezalocare lista
    dezalocareLista(&lista);

    return 0;
}*/
