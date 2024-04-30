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

struct Node {
    struct Scoala scoala;
    struct Node* prev;
    struct Node* next;
};

struct Node* createNode(struct Scoala scoala) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Eroare la alocarea memoriei pentru nodul nou.\n");
        exit(1);
    }
    newNode->scoala = scoala;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Functie pentru a citi obiectele dintr-un fisier text si a le salva intr-o lista dublu inlantuita
struct Node* citesteSiSalveaza(const char* numeFisier) {
    FILE* fisier = fopen(numeFisier, "r");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        exit(1);
    }

    struct Node* head = NULL;
    struct Node* tail = NULL;

    char linie[100]; // Presupunem că fiecare linie din fișier are maxim 100 de caractere

    while (fgets(linie, sizeof(linie), fisier)) {
        struct Scoala scoala;

        // Alocare memorie pentru denumire
        scoala.denumire = (char*)malloc(50 * sizeof(char)); // Presupunem că denumirea școlii are maxim 50 de caractere
        if (scoala.denumire == NULL) {
            printf("Eroare la alocarea memoriei pentru denumire.\n");
            exit(1);
        }

        // Citirea valorilor din linie
        sscanf(linie, "%d %s %d", &scoala.cod, scoala.denumire, &scoala.nrElevi);

        // Alocare memorie pentru numeElevi
        scoala.numeElevi = (char**)malloc(scoala.nrElevi * sizeof(char*));
        if (scoala.numeElevi == NULL) {
            printf("Eroare la alocarea memoriei pentru numeElevi.\n");
            exit(1);
        }

        // Citirea numelor elevilor
        for (int i = 0; i < scoala.nrElevi; ++i) {
            scoala.numeElevi[i] = (char*)malloc(50 * sizeof(char)); // Presupunem că numele elevilor au maxim 50 de caractere
            if (scoala.numeElevi[i] == NULL) {
                printf("Eroare la alocarea memoriei pentru numeElevi[%d].\n", i);
                exit(1);
            }
            sscanf(linie + 14 + i * 7, "%s", scoala.numeElevi[i]); // Offsetul de 15 pentru a evita spațiile și caracterele nedorite
        }

        // Creare nod nou
        struct Node* newNode = createNode(scoala);
        if (head == NULL) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    fclose(fisier);
    return head;
}

// Functie pentru a afisa informatiile unei scoli
void afiseazaScoala(struct Scoala scoala) {
    printf("Cod: %d, Denumire: %s, Numar elevi: %d\n", scoala.cod, scoala.denumire, scoala.nrElevi);
    printf("Nume elevi:\n");
    for (int i = 0; i < scoala.nrElevi; ++i) {
        printf("- %s\n", scoala.numeElevi[i]);
    }
    printf("\n");
}

// Functie pentru a afisa lista dublu inlantuita
void afiseazaLista(struct Node* head) {
    printf("Lista dublu inlantuita:\n");
    while (head != NULL) {
        afiseazaScoala(head->scoala);
        head = head->next;
    }
}
void stergeNod(struct Node** headRef, int pozitie) {
    if (*headRef == NULL) {
        printf("Lista este goala.\n");
        return;
    }

    struct Node* temp = *headRef;
    int count = 1;

    // ștergerea primului nod
    if (pozitie == 1) {
        *headRef = temp->next;
        if (*headRef != NULL) {
            (*headRef)->prev = NULL;
        }
        free(temp);
        return;
    }

    // Găsirea nodului de pe poziția dată
    while (temp != NULL && count < pozitie) {
        temp = temp->next;
        count++;
    }

    if (temp == NULL) {
        printf("Nu exista nod pe pozitia data.\n");
        return;
    }

    // Ștergerea nodului
    temp->prev->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
}
// Comparator pentru sortarea după codul școlii
int comparareCod(const void* a, const void* b) {
    const struct Node* nodA = *(const struct Node**)a;
    const struct Node* nodB = *(const struct Node**)b;
    return nodA->scoala.cod - nodB->scoala.cod;
}

void sortareCrescatoare(struct Node** headRef) {
    int numarNoduri = 0;
    struct Node* temp = *headRef;
    while (temp != NULL) {
        numarNoduri++;
        temp = temp->next;
    }

    // Creare un vector de pointeri la noduri
    struct Node** vectorNoduri = (struct Node**)malloc(numarNoduri * sizeof(struct Node*));
    if (vectorNoduri == NULL) {
        printf("Eroare la alocarea memoriei pentru vectorNoduri.\n");
        exit(1);
    }

    temp = *headRef;
    int index = 0;
    while (temp != NULL) {
        vectorNoduri[index] = temp;
        temp = temp->next;
        index++;
    }

    // Sortare vector de noduri
    qsort(vectorNoduri, numarNoduri, sizeof(struct Node*), comparareCod);

    // Refacere legături între noduri pentru a reflecta ordinea sortată
    for (int i = 0; i < numarNoduri - 1; i++) {
        vectorNoduri[i]->next = vectorNoduri[i + 1];
        vectorNoduri[i + 1]->prev = vectorNoduri[i];
    }
    vectorNoduri[numarNoduri - 1]->next = NULL;
    *headRef = vectorNoduri[0];

    free(vectorNoduri);
}
void afiseazaCrescator(struct Node* head) {
    printf("Elementele listei sortate crescator dupa codul scolii:\n");
    while (head != NULL) {
        afiseazaScoala(head->scoala);
        head = head->next;
    }
}

void afiseazaDescrescator(struct Node* tail) {
    printf("Elementele listei sortate descrescator dupa codul scolii:\n");
    while (tail != NULL) {
        afiseazaScoala(tail->scoala);
        tail = tail->prev;
    }
}

int main() {
    struct Node* lista = citesteSiSalveaza("scoli.txt");
    afiseazaLista(lista);

    // Exemplu de stergere a unui nod
    stergeNod(&lista, 2);
    printf("Lista dupa stergerea unui nod:\n");
    afiseazaLista(lista);

    // Sortarea crescatoare dupa codul scolii si afisarea rezultatului
    sortareCrescatoare(&lista);
    printf("Lista sortata crescator dupa codul scolii:\n");
    afiseazaLista(lista);

    // Afisarea listei in ordine crescatoare si descrescatoare
    afiseazaCrescator(lista);
    afiseazaDescrescator(lista);

    return 0;
}*/
