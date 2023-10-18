#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_SIZE 64
#define MAX_LINE 1024
#define MAX_POINTS 30

typedef struct _Student {

	char m_Ime[MAX_NAME_SIZE];
	char m_Prezime[MAX_NAME_SIZE];
	double m_Bodovi;
} Student;

int ReadNumRowsInFile(FILE* fileHandle, int* numRows);
int ReadStudentsFromFile(FILE* fileHandle, int numStudents, Student** outStudents);
int PrintStudents(Student* students, int numStudents);

int main() {

	FILE* fileHandle = NULL;
	fopen_s(&fileHandle, "students.txt", "r");
	if (fileHandle == NULL) {
		printf("Failed to open the file.\n");
		return -1;
	}

	int numStudents = 0;
	if (!ReadNumRowsInFile(fileHandle, &numStudents))
	{
		fclose(fileHandle);
		printf("Failed to read the number of students.\n");
		return -1;
	}

	Student* students = NULL;
	if (!ReadStudentsFromFile(fileHandle, numStudents, &students))
	{
		fclose(fileHandle);
		printf("Failed to read the students from the file.\n");
		return -1;
	}

	fclose(fileHandle);

	if (!PrintStudents(students, numStudents))
	{
		free(students);
		printf("Failed to print the students.\n");
		return -1;
	}

	free(students);
	return 0;
}

int ReadNumRowsInFile(FILE* fileHandle, int* numRows)
{
	fseek(fileHandle, 0, SEEK_SET);

	int numLines = 0;
	char curLineBuf[MAX_LINE] = { 0 };

	while (!feof(fileHandle))
	{
		numLines++;
		fgets(curLineBuf, MAX_LINE, fileHandle);
	}

	*numRows = numLines;
	return 1;
}

int ReadStudentsFromFile(FILE* fileHandle, int numStudents, Student** outStudents)
{
	fseek(fileHandle, 0, SEEK_SET);

	Student* students = (Student*)malloc(numStudents * sizeof(Student));
	*outStudents = students;

	if (students == NULL)
		return 0;

	int studentIdx = 0;

	while (!feof(fileHandle))
	{
		fscanf(fileHandle, " %s %s %lf", 
			students[studentIdx].m_Ime,
			students[studentIdx].m_Prezime,
			&students[studentIdx].m_Bodovi
		);
	
		if (++studentIdx >= numStudents)
			break;
	}

	return 1;
}

int PrintStudents(Student* students, int numStudents)
{
	for (int studentIdx = 0; studentIdx < numStudents; studentIdx++)
	{
		printf("%s %s %.2lf (%.2lf %%)\n", 
			students[studentIdx].m_Ime,
			students[studentIdx].m_Prezime,
			students[studentIdx].m_Bodovi,
			(students[studentIdx].m_Bodovi / MAX_POINTS) * 100.00
		);
	}

	return 1;
}