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
        scanf("%s", nume, sizeof(nume));
        scoala.numeElevi[i] = (char*)malloc(strlen(nume) + 1);
        strcpy(scoala.numeElevi[i], nume);
    }

    return scoala;
}
// Funcție pentru a găsi cel mai lung nume de elev din școală
char* gasesteCelMaiLungNume(struct Scoala scoala) {
    if (scoala.nrElevi == 0) {
        return NULL; // Nu există elevi în școală
    }

    int indexMax = 0;
    for (int i = 1; i < scoala.nrElevi; ++i) {
        if (strlen(scoala.numeElevi[i]) > strlen(scoala.numeElevi[indexMax])) {
            indexMax = i;
        }
    }

    return scoala.numeElevi[indexMax];
}

// Funcție pentru modificarea denumirii unei școli
void modificaDenumire(struct Scoala* scoala, char* nouaDenumire) {
    free(scoala->denumire);
    scoala->denumire = (char*)malloc(strlen(nouaDenumire) + 1);
    strcpy(scoala->denumire, nouaDenumire);
}

// Funcție pentru afișarea informațiilor despre o școală
void afiseazaScoala(struct Scoala scoala) {
    printf("Cod: %d\n", scoala.cod);
    printf("Denumire: %s\n", scoala.denumire);
    printf("Numar de elevi: %d\n", scoala.nrElevi);
    printf("Numele elevilor:\n");
    for (int i = 0; i < scoala.nrElevi; ++i) {
        printf("- Elevul %d: %s\n", i + 1, scoala.numeElevi[i]);
    }
}

int main() {
    struct Scoala SA = citesteScoala();

    printf("\nInformatii despre Scoala:\n");
    afiseazaScoala(SA);

    printf("\nCel mai lung nume de elev: %s\n", gasesteCelMaiLungNume(SA));

    modificaDenumire(&SA, "Scoala Altfel");

    printf("\nDenumirea actualizata a Scolii:\n");
    afiseazaScoala(SA);

    // Eliberare memorie alocată dinamic
    free(SA.denumire);
    for (int i = 0; i < SA.nrElevi; ++i) {
        free(SA.numeElevi[i]);
    }
    free(SA.numeElevi);

    return 0;
}*/
