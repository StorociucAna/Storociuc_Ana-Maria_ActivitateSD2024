/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define LINE_SIZE 250

typedef struct Comanda Comanda;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Comanda {
    unsigned int numarComanda;
    char* dataLivrareProgramata;
    char* dataLivrareEfectuata;
    char* numeClient;
    float suma;
};

struct Nod {
    Comanda info;
    Nod* next;
    Nod* prev;
};

struct ListaDubla {
    Nod* head;
    Nod* tail;
};

void inserareInceput(ListaDubla* listaDubla, Comanda c) {
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    if (nod == NULL) {
        printf("Eroare la alocarea memoriei pentru nodul nou.\n");
        exit(EXIT_FAILURE);
    }
    nod->info = c;
    nod->next = listaDubla->head;
    nod->prev = NULL;
    if (listaDubla->head) {
        listaDubla->head->prev = nod;
    }
    else {
        listaDubla->tail = nod;
    }
    listaDubla->head = nod;
}

void citireListaDinFisier(ListaDubla* listaDubla, char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Nu am putut deschide fisierul %s.\n", filename);
        return; 
    }

    unsigned char nrComenzi;
    fscanf(file, "%hhu", &nrComenzi);

    for (unsigned char i = 0; i < nrComenzi; i++) {
        Comanda c;

        // Alocare de memorie pentru șirurile de caractere
        c.dataLivrareEfectuata = (char*)malloc(sizeof(char) * LINE_SIZE);
        c.dataLivrareProgramata = (char*)malloc(sizeof(char) * LINE_SIZE);
        c.numeClient = (char*)malloc(sizeof(char) * LINE_SIZE);

        // Citirea datelor
        fscanf(file, "%u", &c.numarComanda);
        fscanf(file, "%s", c.dataLivrareEfectuata);
        fscanf(file, "%s", c.dataLivrareProgramata);
        fscanf(file, "%s", c.numeClient); 
        fscanf(file, "%f", &c.suma); 

        inserareInceput(listaDubla, c); 
    }
    fclose(file);
}

void afisareListaInceput(ListaDubla listaDubla) {
    Nod* current = listaDubla.head;
    while (current) {
        printf("Comanda: %u in suma de %.2f pentru clientul %s a fost programata pentru livrare la data %s si efectuata la data %s\n",
            current->info.numarComanda, current->info.suma, current->info.numeClient,
            current->info.dataLivrareProgramata, current->info.dataLivrareEfectuata);
        current = current->next;
    }
    printf("\n");
}

// Funcție pentru a elibera memoria alocată pentru lista dublă
void eliberareMemorieListaDubla(ListaDubla* listaDubla) {
    Nod* current = listaDubla->head;
    while (current) {
        Nod* temp = current;
        current = current->next;
        free(temp->info.dataLivrareProgramata);
        free(temp->info.dataLivrareEfectuata);
        free(temp->info.numeClient);
        free(temp);
    }
}
// Structura pentru a stoca numele clientului și numărul de comenzi
typedef struct {
    char* numeClient;
    int numarComenzi;
} Client;

// Funcție pentru a găsi indexul unui client în vectorul de clienți
int gasesteClient(Client* clienti, int numarClienti, char* numeClient) {
    for (int i = 0; i < numarClienti; i++) {
        if (strcmp(clienti[i].numeClient, numeClient) == 0) {
            return i; 
        }
    }
    return -1; 
}

// Funcție pentru a adăuga un client în vectorul de clienți
void adaugaClient(Client** clienti, int* numarClienti, char* numeClient) {
    (*numarClienti)++;
    *clienti = realloc(*clienti, (*numarClienti) * sizeof(Client));
    if (!(*clienti)) {
        fprintf(stderr, "Eroare la realocarea memoriei.\n");
        exit(EXIT_FAILURE);
    }
    (*clienti)[*numarClienti - 1].numeClient = _strdup(numeClient);
    (*clienti)[*numarClienti - 1].numarComenzi = 0;
}

// Funcție pentru a incrementa numărul de comenzi pentru un client dat
void incrementeazaNumarComenzi(Client* clienti, int numarClienti, char* numeClient) {
    int index = gasesteClient(clienti, numarClienti, numeClient);
    if (index != -1) {
        clienti[index].numarComenzi++;
    }
}
Client gasesteClientMaxim(ListaDubla listaDubla) {
    Client* clienti = NULL;
    int numarClienti = 0;

    Nod* current = listaDubla.head;
    while (current) {
        if (gasesteClient(clienti, numarClienti, current->info.numeClient) == -1) {
            adaugaClient(&clienti, &numarClienti, current->info.numeClient);
        }
        incrementeazaNumarComenzi(clienti, numarClienti, current->info.numeClient);
        current = current->next;
    }

    Client clientMaxim = clienti[0];
    for (int i = 1; i < numarClienti; i++) {
        if (clienti[i].numarComenzi > clientMaxim.numarComenzi) {
            clientMaxim = clienti[i];
        }
    }
    return clientMaxim;
}

int main() {
    ListaDubla listaDubla = { NULL,NULL };
    citireListaDinFisier(&listaDubla, "comenzi.txt");
    afisareListaInceput(listaDubla);
    // Găsirea clientului cu cele mai multe comenzi
    Client clientMaxim = gasesteClientMaxim(listaDubla);

    // Afișarea rezultatului
    printf("Clientul cu cele mai multe comenzi este: %s, cu un total de %d comenzi.\n", clientMaxim.numeClient, clientMaxim.numarComenzi);


    eliberareMemorieListaDubla(&listaDubla);

    return 0;
}
*/