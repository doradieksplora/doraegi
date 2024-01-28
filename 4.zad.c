//4. Napisati program za zbrajanje i množenje polinoma.Koeficijenti i eksponenti se
//čitaju iz datoteke.
//Napomena: Eksponenti u datoteci nisu nužno sortirani.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _polinom;
typedef struct _polinom* Position;
typedef struct _polinom {
	int koeficjent;
	int eksponent;
	Position next;
}polinom;

Position initalizationOfStructure(int koeficjent, int eksponent);
int readingPolinoms(Position HeadFirst, Position HeadSecond);
int intsertElement(Position head, int koeficjent, int eksponent);
int addPolinoms(Position HeadFirst, Position HeadSecond, Position ResultPolinom);
int multiplyPolinoms(Position HeadFirst, Position HeadSecond, Position ResultPolinom);
int printPolinom(Position HeadNext);

int main() 
{
	polinom HeadFirst = { .koeficjent = 0, .eksponent = 0, .next = NULL };
	polinom HeadSecond = { .koeficjent = 0, .eksponent = 0, .next = NULL };
	polinom ResultPolinom = { .koeficjent = 0, .eksponent = 0, .next = NULL };
	readingPolinoms(&HeadFirst, &HeadSecond);
	printPolinom(HeadFirst.next);
	printPolinom(HeadSecond.next);

	addPolinoms(&HeadFirst, &HeadSecond, &ResultPolinom);
	printPolinom(ResultPolinom.next);

	multiplyPolinoms(&HeadFirst, &HeadSecond, &ResultPolinom);
	printPolinom(ResultPolinom.next);
}

Position initalizationOfStructure(int koeficjent, int eksponent) {
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(polinom));
	newElement->eksponent = eksponent;
	newElement->koeficjent = koeficjent;

	if (newElement == NULL) {
		printf("Nije ispravno inicijalzan novi element\n");
		return 0;
	}
	return newElement;
}

int readingPolinoms(Position HeadFirst, Position HeadSecond) {
	FILE* filepointer;
	filepointer = fopen("polinomi.txt", "r");
	if (filepointer == NULL) {
		printf("Nije moguce otvoriti teksutalnu datoteku\n");
		return 0;
	}

	char nextCharacter = "";
	int koeficjent, eksponent = 0;
	while (fscanf(filepointer, "%dx%d%c", &koeficjent, &eksponent, &nextCharacter) == 3) {

		intsertElement(HeadFirst, koeficjent, eksponent);
		//printf("%dx^%d ", koeficjent, eksponent); //provjera ispisa prvog polinoma

		if (nextCharacter == '\n') {
			break;
		}
	}

	while (fscanf(filepointer, "%dx%d%c", &koeficjent, &eksponent, &nextCharacter) == 3) {

		intsertElement(HeadSecond, koeficjent, eksponent);
		//printf("%dx^%d ", koeficjent, eksponent); //provjera ispisa

		if (nextCharacter == '\n') {
			break;
		}
	}
	return 0;
}

int intsertElement(Position head, int koeficjent, int eksponent) {
	Position element = NULL;
	element = initalizationOfStructure(koeficjent, eksponent);

	while (head->next != NULL && head->next->eksponent > element->eksponent) {
		head = head->next;
	}

	if (head->next != NULL) {
		if (element->eksponent == head->next->eksponent) {
			element->koeficjent += head->next->koeficjent;
			element->next = head->next->next;
			free(head->next);
			head->next = element;

			if (element->koeficjent == 0) {
				head->next = element->next;
				free(element);
			}
		}
		else {
			element->next = head->next;
			head->next = element;
		}
	}
	else {
		element->next = head->next;
		head->next = element;
	}
	return 0;
}

int addPolinoms(Position HeadFirst, Position HeadSecond, Position ResultPolinom) {
	Position temp = NULL;
	/*while (HeadFirst->next != NULL)	{
		ResultPolinom->next = HeadFirst->next;
		HeadFirst = HeadFirst->next;
		ResultPolinom = ResultPolinom->next;
	}*/

	while (HeadFirst != NULL && HeadSecond != NULL){
		//ovde je uvjet headFirst ne headFirst->next zato sto se mora izvrsit i za zadnji element polinoma
		if (HeadFirst->koeficjent == HeadSecond->koeficjent) {
			intsertElement(ResultPolinom, HeadFirst->koeficjent + HeadSecond->koeficjent, HeadFirst->eksponent);
			HeadFirst = HeadFirst->next;
			HeadSecond = HeadSecond->next;
		}
		else if (HeadFirst->koeficjent > HeadSecond->koeficjent) {
			intsertElement(ResultPolinom, HeadFirst->koeficjent, HeadFirst->eksponent);
			HeadFirst = HeadFirst->next;
		}
		else {
			intsertElement(ResultPolinom, HeadSecond->koeficjent, HeadSecond->eksponent);
			HeadSecond = HeadSecond->next;
		}
	}
	if (HeadFirst != NULL) {
		temp = HeadFirst;
	}
	else {
		temp = HeadSecond;
	}
	while (temp != NULL) {
		intsertElement(ResultPolinom, temp->koeficjent, temp->eksponent);
		temp = temp->next;
	}

	return 0;
}

int multiplyPolinoms(Position HeadFirst, Position HeadSecond, Position ResultPolinom) {
	for (Position current1 = HeadFirst; current1 != NULL; current1 = current1->next) {
		for (Position current2 = HeadSecond; current2 != NULL; current2 = current2->next) {
			intsertElement(ResultPolinom, current1->koeficjent * current2->koeficjent, current1->eksponent + current2->eksponent);
		}
	}
	return 0;
}

int printPolinom(Position HeadNext) {
	//printf("\n---------Ispis---------\n");
	for (; HeadNext != NULL; HeadNext = HeadNext->next) {
		if (HeadNext->eksponent != 0) {
			printf("%dx^%d ", HeadNext->koeficjent, HeadNext->eksponent);
		}
	}
	printf("\n");
	return 0;
}
