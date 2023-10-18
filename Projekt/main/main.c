#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_SIZE 64
#define MAX_LINE 1024

typedef struct _Student {

	char m_Ime[MAX_NAME_SIZE];
	char m_Prezime[MAX_NAME_SIZE];
	int m_Bodovi;
} Student;

int main() {

	FILE* fileHandle = NULL;
	fopen_s(&fileHandle, "studenti.txt", "r");
	if (fileHandle == NULL) {
		printf("Nemoguće otvoriti datoteku.\n");
		return -1;
	}

	char curLineBuf[MAX_LINE] = { 0 };
	int numStudents = 0;
	while (!feof(fileHandle))
	{
		numStudents++;
		fgets(curLineBuf, MAX_LINE, fileHandle);
		// printf("Line: %s", curLineBuf);
	}

	printf("Number of lines: %d", numStudents);

	fclose(fileHandle);
	return 0;
}