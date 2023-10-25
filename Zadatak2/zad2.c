#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

typedef struct osoba* Pozicija; // Pokazivač na strukturu (omogućuje povezivanje čvorova u dinamičkoj listi)

typedef struct osoba {           // Definicija strukture osoba
    char ime[MAX];
    char prezime[MAX];
    int datum;
    Pozicija sljedeca_poz;    // Pokazivač na sljedeću osobu
} osoba;

// Deklaracija funkcija
Pozicija dodaj_na_pocetak(Pozicija); // Vraća novu poziciju/cvor koji će biti postavljen kao trenutna pozicija
void ispisi_listu(Pozicija);        // Prima head
Pozicija dodaj_na_kraj(Pozicija); // Vraća novu poziciju/cvor koji će biti postavljen kao trenutna pozicija
void pronadi_osobu(Pozicija, char[]); // Prima poziciju i niz znakova (prezime)
Pozicija izbrisi_osobu(Pozicija, char[]); // Vraća novu poziciju/cvor koji će biti postavljen kao trenutna pozicija
void odabir_fje(Pozicija);

int main() {
    osoba Head = { .ime = {0}, .prezime = {0}, .datum = 0, .sljedeca_poz = 0 }; // Stvaranje liste
    Head.sljedeca_poz = NULL; // Inicijalizacija liste
    odabir_fje(&Head);   // Odabir operacija nad listom
}

// Funkcija za dodavanje nove osobe na početak liste
Pozicija dodaj_na_pocetak(Pozicija head) {
    char ime[MAX];
    char prezime[MAX];
    int datum;

    Pozicija nova_osoba = (Pozicija)malloc(sizeof(osoba));

    if (nova_osoba == NULL) {
        printf("Greška pri dodavanju osobe na početak liste.\n");
        return head;
    }

    printf("Unesite ime, prezime i godinu rođenja: ");
    scanf("%s %s %d", ime, prezime, &datum);

    strcpy(nova_osoba->ime, ime);
    strcpy(nova_osoba->prezime, prezime);
    nova_osoba->datum = datum;
    nova_osoba->sljedeca_poz = head;

    return nova_osoba;
}

// Funkcija za ispisivanje liste
void ispisi_listu(Pozicija head) {
    printf("Popis osoba:\n");

    while (head != NULL) {
        printf("%s %s %d\n", head->ime, head->prezime, head->datum);
        head = head->sljedeca_poz;
    }
}

// Funkcija za dodavanje nove osobe na kraj liste
Pozicija dodaj_na_kraj(Pozicija head) {
    char ime[MAX];
    char prezime[MAX];
    int datum;

    Pozicija nova_osoba = (Pozicija)malloc(sizeof(osoba));

    if (nova_osoba == NULL) {
        printf("Greška pri dodavanju osobe na kraj liste.\n");
        return head;
    }

    printf("Unesite ime, prezime i godinu rođenja: ");
    scanf("%s %s %d", ime, prezime, &datum);

    strcpy(nova_osoba->ime, ime);
    strcpy(nova_osoba->prezime, prezime);
    nova_osoba->datum = datum;
    nova_osoba->sljedeca_poz = NULL;

    if (head == NULL) {
        return nova_osoba;
    }

    Pozicija trenutna = head;
    while (trenutna->sljedeca_poz != NULL) {
        trenutna = trenutna->sljedeca_poz;
    }

    trenutna->sljedeca_poz = nova_osoba;

    return head;
}

// Funkcija za pronalazak osobe po prezimenu
void pronadi_osobu(Pozicija head, char prezime[]) {
    int pronadena = 0;

    while (head != NULL) {
        if (strcmp(head->prezime, prezime) == 0) {
            printf("Pronađena osoba:\n");
            printf("%s %s %d\n", head->ime, head->prezime, head->datum);
            pronadena = 1;
        }
        head = head->sljedeca_poz;
    }

    if (pronadena == 0) {
        printf("Osoba s tim prezimenom nije pronađena.\n");
    }
}

// Funkcija za brisanje određene osobe iz liste
Pozicija izbrisi_osobu(Pozicija head, char prezime[]) {
    if (head == NULL) {
        printf("Nema osoba u listi.\n");
        return NULL;
    }

    if (strcmp(head->prezime, prezime) == 0) {
        Pozicija temp = head;
        head = head->sljedeca_poz;
        free(temp);
        return head;
    }

    Pozicija trenutna = head;
    while (trenutna->sljedeca_poz != NULL) {
        if (strcmp(trenutna->sljedeca_poz->prezime, prezime) == 0) {
            Pozicija temp = trenutna->sljedeca_poz;
            trenutna->sljedeca_poz = temp->sljedeca_poz;
            free(temp);
            return head;
        }
        trenutna = trenutna->sljedeca_poz;
    }

    printf("Osoba s tim prezimenom nije pronađena.\n");
    return head;
}

void odabir_fje(Pozicija head) {
    char izbor;
    char prezime[MAX];

    do {
        printf("Odaberite akciju:\n");
        printf("A - Dodaj osobu na početak liste\n");
        printf("B - Ispiši listu\n");
        printf("C - Dodaj osobu na kraj liste\n");
        printf("D - Pronađi osobu\n");
        printf("E - Obriši osobu\n");
        printf("Q - Prekini odabir\n");

        scanf(" %c", &izbor);

        switch (izbor) {
        case 'A':
            head = dodaj_na_pocetak(head);
            break;
        case 'B':
            ispisi_listu(head);
            break;
        case 'C':
            head = dodaj_na_kraj(head);
            break;
        case 'D':
            printf("Unesite prezime osobe koju tražite: ");
            scanf("%s", prezime);
            pronadi_osobu(head, prezime);
            break;
        case 'E':
            printf("Unesite prezime osobe koju želite izbrisati: ");
            scanf("%s", prezime);
            head = izbrisi_osobu(head, prezime);
            break;
        case 'Q':
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Nepostojeća opcija. Molimo vas da odaberete ponovno.\n");
        }
    } while (izbor != 'Q');
}
