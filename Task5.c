/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Nod {
    struct Scoala* scoala;
    struct Nod* urmator;
};

struct ListaSimpluInlantuita {
    struct Nod* primul;
};

struct Scoala {
    int cod;
    char* denumire;
    int nrElevi;
    char** numeElevi;
};

struct Nod* creareNod(struct Scoala* scoala) {
    struct Nod* nodNou = (struct Nod*)malloc(sizeof(struct Nod));
    if (nodNou == NULL) {
        printf("Eroare la alocarea de memorie pentru nod.\n");
        exit(EXIT_FAILURE);
    }
    nodNou->scoala = scoala;
    nodNou->urmator = NULL;
    return nodNou;
}

void adaugaNod(struct ListaSimpluInlantuita* lista, struct Scoala* scoala) {
    struct Nod* nodNou = creareNod(scoala);
    if (lista->primul == NULL) {
        lista->primul = nodNou;
    }
    else {
        struct Nod* curent = lista->primul;
        while (curent->urmator != NULL) {
            curent = curent->urmator;
        }
        curent->urmator = nodNou;
    }
}

void stergeNod(struct ListaSimpluInlantuita* lista, int pozitie) {
    if (lista == NULL || lista->primul == NULL) {
        return;
    }

    struct Nod* anterior = NULL;
    struct Nod* curent = lista->primul;
    int index = 0;

    while (curent != NULL && index != pozitie) {
        anterior = curent;
        curent = curent->urmator;
        index++;
    }

    if (curent == NULL) {
        printf("Lista are mai putine noduri decat pozitia data.\n");
        return;
    }

    if (anterior == NULL) {
        lista->primul = curent->urmator;
    }
    else {
        anterior->urmator = curent->urmator;
    }

    free(curent->scoala->denumire);
    for (int i = 0; i < curent->scoala->nrElevi; ++i) {
        free(curent->scoala->numeElevi[i]);
    }
    free(curent->scoala->numeElevi);
    free(curent->scoala);
    free(curent);
}

// Functie pentru a insera un element intr-o lista sortata
void insereazaSortat(struct ListaSimpluInlantuita* lista, struct Scoala* scoala) {
    struct Nod* nodNou = creareNod(scoala);

    if (lista->primul == NULL || lista->primul->scoala->cod >= scoala->cod) {
        nodNou->urmator = lista->primul;
        lista->primul = nodNou;
    }
    else {
        struct Nod* curent = lista->primul;
        while (curent->urmator != NULL && curent->urmator->scoala->cod < scoala->cod) {
            curent = curent->urmator;
        }
        nodNou->urmator = curent->urmator;
        curent->urmator = nodNou;
    }
}

// Functie care verifica daca o scoala are un numar de elevi mai mare decat o anumita valoare
int conditie(struct Scoala* scoala, int valoare) {
    return scoala->nrElevi > valoare;
}

// Functie care copiaza in vector toate elementele care indeplinesc o anumita conditie
struct Scoala** selecteazaElemente(struct ListaSimpluInlantuita* lista, int* dimensiuneVector, int valoare) {
    *dimensiuneVector = 0;
    struct Nod* curent = lista->primul;
    while (curent != NULL) {
        if (conditie(curent->scoala, valoare)) {
            (*dimensiuneVector)++;
        }
        curent = curent->urmator;
    }

    struct Scoala** vectorScoli = (struct Scoala**)malloc(*dimensiuneVector * sizeof(struct Scoala*));
    if (vectorScoli == NULL) {
        printf("Eroare la alocarea de memorie pentru vectorul de scoli.\n");
        exit(EXIT_FAILURE);
    }

    curent = lista->primul;
    int index = 0;
    while (curent != NULL) {
        if (conditie(curent->scoala, valoare)) {
            struct Scoala* copieScoala = (struct Scoala*)malloc(sizeof(struct Scoala));
            if (copieScoala == NULL) {
                printf("Eroare la alocarea de memorie pentru copia de scoala.\n");
                exit(EXIT_FAILURE);
            }
            copieScoala->cod = curent->scoala->cod;
            copieScoala->denumire = _strdup(curent->scoala->denumire);
            copieScoala->nrElevi = curent->scoala->nrElevi;
            copieScoala->numeElevi = (char**)malloc(copieScoala->nrElevi * sizeof(char*));
            if (copieScoala->numeElevi == NULL) {
                printf("Eroare la alocarea de memorie pentru numele elevilor.\n");
                exit(EXIT_FAILURE);
            }
            for (int i = 0; i < copieScoala->nrElevi; ++i) {
                copieScoala->numeElevi[i] = _strdup(curent->scoala->numeElevi[i]);
            }
            vectorScoli[index++] = copieScoala;
        }
        curent = curent->urmator;
    }

    return vectorScoli;
}

// Functie pentru interschimbarea elementelor de pe doua pozitii din lista
void interschimbaPozitii(struct ListaSimpluInlantuita* lista, int pozitie1, int pozitie2) {
    if (lista == NULL || lista->primul == NULL) {
        return;
    }

    if (pozitie1 == pozitie2) {
        return;
    }

    int min = (pozitie1 < pozitie2) ? pozitie1 : pozitie2;
    int max = (pozitie1 > pozitie2) ? pozitie1 : pozitie2;

    if (min < 0) {
        printf("Pozitiile trebuie sa fie pozitive sau zero.\n");
        return;
    }

    struct Nod* anterior1 = NULL;
    struct Nod* curent1 = lista->primul;
    int index1 = 0;
    while (curent1 != NULL && index1 != min) {
        anterior1 = curent1;
        curent1 = curent1->urmator;
        index1++;
    }

    struct Nod* anterior2 = NULL;
    struct Nod* curent2 = lista->primul;
    int index2 = 0;
    while (curent2 != NULL && index2 != max) {
        anterior2 = curent2;
        curent2 = curent2->urmator;
        index2++;
    }

    if (curent1 == NULL || curent2 == NULL) {
        printf("Pozitiile depasesc lungimea listei.\n");
        return;
    }

    if (anterior1 != NULL) {
        anterior1->urmator = curent2;
    }
    else {
        lista->primul = curent2;
    }

    if (anterior2 != NULL) {
        anterior2->urmator = curent1;
    }
    else {
        lista->primul = curent1;
    }

    struct Nod* temp = curent1->urmator;
    curent1->urmator = curent2->urmator;
    curent2->urmator = temp;
}

// Functie pentru citirea obiectelor din fisier si adaugarea lor in lista
void citireSiAdaugareInLista(const char* numeFisier, struct ListaSimpluInlantuita* lista) {
    FILE* fisier = fopen(numeFisier, "r");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fisier) != NULL) {
        struct Scoala* scoala = (struct Scoala*)malloc(sizeof(struct Scoala));
        if (scoala == NULL) {
            printf("Eroare la alocarea de memorie pentru o scoala.\n");
            exit(EXIT_FAILURE);
        }

        char* token = strtok(buffer, " ");
        scoala->cod = atoi(token);
        token = strtok(NULL, " ");
        scoala->denumire = _strdup(token);
        token = strtok(NULL, " ");
        scoala->nrElevi = atoi(token);
        scoala->numeElevi = (char**)malloc(scoala->nrElevi * sizeof(char*));
        if (scoala->numeElevi == NULL) {
            printf("Eroare la alocarea de memorie pentru numele elevilor.\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < scoala->nrElevi; ++i) {
            token = strtok(NULL, " ");
            scoala->numeElevi[i] = _strdup(token);
        }

        adaugaNod(lista, scoala);
    }

    fclose(fisier);
}

// Functie pentru afisarea listei
void afisareLista(struct ListaSimpluInlantuita* lista) {
    struct Nod* curent = lista->primul;
    while (curent != NULL) {
        printf("Cod: %d, Denumire: %s, Numar elevi: %d\n", curent->scoala->cod, curent->scoala->denumire, curent->scoala->nrElevi);
        for (int i = 0; i < curent->scoala->nrElevi; ++i) {
            printf("- Elevul %d: %s\n", i + 1, curent->scoala->numeElevi[i]);
        }
        curent = curent->urmator;
    }
}

// Functie pentru dezalocarea memoriei ocupata de lista
void dezalocareLista(struct ListaSimpluInlantuita* lista) {
    struct Nod* curent = lista->primul;
    while (curent != NULL) {
        struct Nod* temp = curent;
        curent = curent->urmator;
        free(temp->scoala->denumire);
        for (int i = 0; i < temp->scoala->nrElevi; ++i) {
            free(temp->scoala->numeElevi[i]);
        }
        free(temp->scoala->numeElevi);
        free(temp->scoala);
        free(temp);
    }
    lista->primul = NULL;
}

int main() {
    // Initializare lista
    struct ListaSimpluInlantuita lista;
    lista.primul = NULL;

    // Citire din fisier si adaugare in lista
    citireSiAdaugareInLista("scoli.txt", &lista);

    // Afisare lista
    printf("Lista initiala:\n");
    afisareLista(&lista);


    // Exemplu de utilizare a functiilor definite
    stergeNod(&lista, 2);
    printf("\nLista dupa stergerea nodului de pe pozitia 2:\n");
    afisareLista(&lista);

    struct Scoala* scoalaNoua = (struct Scoala*)malloc(sizeof(struct Scoala));
    if (scoalaNoua == NULL) {
        printf("Eroare la alocarea de memorie pentru scoala noua.\n");
        return -1;
    }
    scoalaNoua->cod = 555;
    scoalaNoua->denumire = _strdup("ScoalaX");
    scoalaNoua->nrElevi = 3;
    scoalaNoua->numeElevi = (char**)malloc(scoalaNoua->nrElevi * sizeof(char*));
    if (scoalaNoua->numeElevi == NULL) {
        printf("Eroare la alocarea de memorie pentru numele elevilor din scoala noua.\n");
        return -1;
    }
    scoalaNoua->numeElevi[0] = _strdup("ElevX1");
    scoalaNoua->numeElevi[1] = _strdup("ElevX2");
    scoalaNoua->numeElevi[2] = _strdup("ElevX3");

    insereazaSortat(&lista, scoalaNoua);
    printf("\nLista dupa inserarea unei noi scoli sortate crescator dupa cod:\n");
    afisareLista(&lista);

    int dimensiuneVector;
    struct Scoala** vectorScoli = selecteazaElemente(&lista, &dimensiuneVector, 2);
    printf("\nVectorul cu scoli care au mai mult de 2 elevi:\n");
    for (int i = 0; i < dimensiuneVector; ++i) {
        printf("Cod: %d, Denumire: %s, Numar elevi: %d\n", vectorScoli[i]->cod, vectorScoli[i]->denumire, vectorScoli[i]->nrElevi);
        for (int j = 0; j < vectorScoli[i]->nrElevi; ++j) {
            printf("- Elevul %d: %s\n", j + 1, vectorScoli[i]->numeElevi[j]);
        }
    }

    interschimbaPozitii(&lista, 1, 3);
    printf("\nLista dupa interschimbarea elementelor de pe pozitiile 1 si 3:\n");
    afisareLista(&lista);

    // Dezalocare lista
    dezalocareLista(&lista);

    return 0;
}*/
