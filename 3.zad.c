/*3. Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,
B. dinamički dodaje novi element ispred određenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. čita listu iz datoteke.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[20];
	char surname[20];
	int birthYear;
	Position next;
} Person;

Position kreiranjeOsobe();
int unosNaPocetak(Position p);
int PrintList(Position p);
int unosNaKraj(Position p);
int trazi(Position p, char* prezime);
int brisanjeOdredenogElementa(Position p, char* prezime);
int unosIzaElementa(Position p, char* prezime);
int unosPrijeElementa(Position p, char* prezime);
int Sort(Position p);
int upisUDatoteku(Position p);
int ispisIzDatoteke();
int brisanjeListe(Position p);


int main()
{
	Person Head = { .next = NULL, .name = " ", .surname = " ", .birthYear = 0 };

	unosNaPocetak(&Head);
	unosNaKraj(&Head);
	unosNaKraj(&Head);
	PrintList(Head.next);

	char prezime[20] = " ";
	/*printf("Unesite prezime osobe koje zelite pronaci\n");
	scanf(" %s", prezime);
	trazi(&Head, prezime);

	printf("Unesite prezime osobe koje zelite izbrisati\n");
	scanf(" %s", prezime);
	brisanjeOdredenogElementa(&Head, prezime);

	PrintList(Head.next);*/

	/*printf("Unesite prezime osobe iza koje zelite upisati novi element\n");
	scanf(" %s", prezime);
	unosIzaElementa(&Head, prezime);

	PrintList(Head.next);*/

	printf("Unesite prezime osobe prije koje zelite upisati novi element\n");
	scanf(" %s", prezime);
	unosPrijeElementa(&Head, prezime);

	PrintList(Head.next);

	//upisUDatoteku(Head.next);

	//ispisIzDatoteke();

	Sort(&Head);
	PrintList(Head.next);
	upisUDatoteku(Head.next);

	/*brisanjeListe(&Head);
	PrintList(Head.next);*/

	return 0;
}


Position kreiranjeOsobe() {
	Position newPerson = NULL;
	char name[20] = " ";
	char surname[20] = " ";
	int birthYear = 0;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("Krivo alociranje memorije\n");
		exit(1);
	}

	printf("Unesite ime:\n");
	scanf(" %s", name);
	printf("Unesite prezime:\n");
	scanf(" %s", surname);
	printf("Unesite godinu rodenja:\n");
	scanf(" %d", &birthYear);

	//moramo sa strcpy jer kopiramo sadrzaj ne adrese pokazivaca
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;

	return newPerson;
}

int unosNaPocetak(Position p) {
	Position newPerson = NULL;

	newPerson = kreiranjeOsobe();

	if (newPerson != NULL) {
		newPerson->next = p->next;
		p->next = newPerson;
	}

	return 0;
}

int PrintList(Position p) {
	printf("\nIspis\n");
	printf("-------------\n");
	for (; p != NULL; p = p->next) {
		printf("Name: %s\t Surname: %s\t Birth year: %d\t\n", p->name, p->surname, p->birthYear);
	}
	printf("-------------\n");
	return 0;
}

int unosNaKraj(Position p) {
	Position newPerson = NULL;

	newPerson = kreiranjeOsobe();

	if (newPerson != NULL) {
		while (p->next != NULL) {
			p = p->next;
		}
		newPerson->next = p->next;
		p->next = newPerson;
	}

	return 0;
}

int trazi(Position p, char* prezime) {

	while (p != NULL && strcmp(p->surname, prezime) != 0) {
		p = p->next;
	}
	printf("\nPronadena osoba\n");
	printf("-------------\n");
	printf("Name: %s\t Surname: %s\t Birth year: %d\t\n", p->name, p->surname, p->birthYear);
	printf("-------------\n");
	return 0;
}

int brisanjeOdredenogElementa(Position p, char* prezime) {
	Position prev = NULL;

	while (p->next != NULL && strcmp(p->surname, prezime) != 0) {
		//strcmp vraca 0 ako su dva ista chara 
		prev = p;
		p = p->next;
	}

	if (p != NULL) {
		prev->next = p->next;
		free(p);
		printf("Obrisano\n");
	}

	return 0;
}

int unosIzaElementa(Position p, char* prezime) {

	while (p->next != NULL && strcmp(p->name, prezime) != 0) {
		p = p->next;
	}

	if (p != NULL) {
		Position newPerson = NULL;
		newPerson = kreiranjeOsobe();

		newPerson->next = p->next;
		p->next = newPerson;
	}

	return 0;
}

int unosPrijeElementa(Position p, char* prezime) {
	Position prev = NULL;

	while (p->next != NULL && strcmp(p->name, prezime) != 0) {
		prev = p;
		p = p->next;
	}

	if (p != NULL) {
		Position newPerson = NULL;
		newPerson = kreiranjeOsobe();

		newPerson->next = prev->next;
		prev->next = newPerson;
	}

	return 0;
}

int Sort(Position p){
	//Za sortiranje se koristi bubble sort
	Position j, prev_j, temp, end;
	end = NULL;

	while (p->next != end){
		prev_j = p;
		j = p->next;
		while (j->next != end){
			if (strcmp(j->surname, j->next->surname) > 0){
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}
			prev_j = j;
			j = j->next;
		}
		end = j;
	}
	return 0;
}

int upisUDatoteku(Position p) {
	FILE* filePointer = NULL;
	filePointer = fopen("DatotekaZaUpis.txt", "w");
	if (filePointer == NULL) {
		printf("Nije moguce stvoriti teksutalnu datoteku\n");
		exit(1);
	}

	//ispisuje se unesena lista u datoteku
	for(; p != NULL; p = p->next) {
		fprintf(filePointer, "%s\t%s\t%d\n", p->name, p->surname, p->birthYear);
	}

	fclose(filePointer);
}

int ispisIzDatoteke() {
	FILE* filePointer = NULL;
	filePointer = fopen("DatotekaZaIspis.txt", "r");
	if (filePointer == NULL) {
		printf("Nije moguce otvoriti teksutalnu datoteku\n");
		exit(1);
	}

	Person trenutni;
	while (fscanf(filePointer, "%s %s %d", trenutni.name, trenutni.surname, &trenutni.birthYear) == 3) {
		printf("%s %s %d\n", trenutni.name, trenutni.surname, trenutni.birthYear);
	}
	fclose(filePointer);
}

int brisanjeListe(Position p) {
	Position q;
	while (p->next != NULL) {
		q = p->next;
		p->next = q->next;
		free(q);
	}
}






