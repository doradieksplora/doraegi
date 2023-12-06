#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _stog;
typedef struct _stog* position;
typedef struct _stog {
	double number;
	position next;
}stog;

int readFromFile(char* postfix);
position createElement(double broj);
int calculatePostfix(position head, char* postfix, double* result);
int push(position head, position newElement);
int pop(position head, double* operand);
int popAndPerformOperation(position head, char operation, double* result);
int clearStog(head);

int main()
{
	stog head = { .number = 0, .next = NULL };
	char postfix[1024];
	double result = 0;

	calculatePostfix(&head, postfix, &result);

	return 0;
}

int readFromFile(char* postfix) {
	FILE* filepointer;
	filepointer = fopen("postfix.txt", "r");
	if (filepointer == NULL) {
		return 0;
	}
	fgets(postfix, 1024, filepointer);
	//printf("%s\n", postfix);
	fclose(filepointer);
	return 0;
}

position createElement(double number) {
	position newElement = NULL;
	newElement = (position)malloc(sizeof(stog));
	if (newElement == NULL) {
		printf("Krivo alocirana memorija\n");
		return 0;
	}
	newElement->number = number;
	newElement->next = NULL;
	return newElement;
}

int calculatePostfix(position head, char* postfix, double* result) {
	readFromFile(postfix);
	printf("%s\n", postfix);

	char* buffer = postfix; //mora biti pokazivac jer se izjednacava sa postifikson sta je pokazivac
	position newElement = NULL;
	int status = 0;
	double number = 0;
	int bytes = 0;
	char operation;

	while (strlen(buffer) > 0) {
		//printf("%s\n", buffer);
		status = sscanf(buffer, " %lf %n", &number, &bytes);
		//printf("1test %lf", number);
		if (status != 1) {
			sscanf(buffer, " %c %n", &operation, &bytes);
			status = popAndPerformOperation(head, operation, result);
			if (status != EXIT_SUCCESS) {
				return EXIT_FAILURE;
			}

			number = *result;
			//printf(" 2test %lf", number);
		}

		//printf(" 3test %lf", number);
		newElement = createElement(number);
		if (newElement == NULL) {
			return 0;
		}

		number = 0;

		buffer += bytes; //pomicanje pokazivaca za velicinu koja je unesena
		//printf("%d", bytes);
		printf("|%s| ----", buffer);
		push(head, newElement);
	}
	clearStog(head);
	return 0;
}

int push(position head, position newElement) {
	//unos na prvo misto
	newElement->next = head->next;
	head->next = newElement;

	while (head->next != NULL) {
		printf(" %0.1lf", head->next->number);
		head = head->next;
	}
	printf("\n");

	return EXIT_SUCCESS;
}

int pop(position head, double* operand) {
	position elementToDelete = NULL;

	elementToDelete = head->next;
	if (elementToDelete == NULL) {
		printf("Greska\n");
		return 0;
	}

	head->next = elementToDelete->next;
	*operand = elementToDelete->number;
	free(elementToDelete);

	return EXIT_SUCCESS;
}

int popAndPerformOperation(position head, char operation, double* result) {
	double operand1 = 0;
	double operand2 = 0;

	pop(head, &operand1);
	pop(head, &operand2);

	switch (operation) {
	case '+':
		*result = operand2 + operand1;
		break;
	case '-':
		*result = operand2 - operand1;
		break;
	case '*':
		*result = operand2 * operand1;
		break;
	case '/':
		if (operand1 != 0) {
			*result = operand2 / operand1;
		}
		else {
			printf("nemoze se dijeliti sa 0\n");
		}
		break;
	default:
		printf("Kirva operacija\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int clearStog(position head) {
	if (head->next->next != NULL) {
		printf("Greska\n");
		return EXIT_FAILURE;
	}
	else {
		printf("Rezultat je %0.2lf\n", head->next->number);
		free(head->next);
	}
	return EXIT_SUCCESS;
}
