//7.Napisati program koji pomoću vezanih listi(stabala) predstavlja strukturu direktorija.
//Omogućiti unos novih direktorija i pod - direktorija, ispis sadržaja direktorija i
//povratak u prethodni direktorij.Točnije program treba preko menija simulirati
//korištenje DOS naredbi : 1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _directory;
typedef struct _directory* PositionDirectory;
typedef struct _directory {
    char name[50];
    PositionDirectory subDirectories;
    PositionDirectory next;
    PositionDirectory parentDirectory; //$$
} Directory;

PositionDirectory createDirectory(char* directoryName);
int createSubdirectory(char* directoryName, PositionDirectory currentDirectory);
PositionDirectory chageDirectory(PositionDirectory currentDirectory, char* nameDirectory);
PositionDirectory returnToParentDirectory(PositionDirectory currentDirectory);

int main() {
    Directory headDirectory = {
        .name = {0},
        .subDirectories = NULL,
        .next = NULL
    };
    PositionDirectory rootDirectory = createDirectory("C:");
    headDirectory.next = rootDirectory;

    PositionDirectory currentDirectory = rootDirectory;
    int command = 0;

    do {
        printf("\nMenu:\n");
        printf("1 - MD (make directory)\n");
        printf("2 - CD (dir change directory)\n");
        printf("3 - CD.. (exit derectory)\n");
        printf("4 - DIR (list subdirectories)\n");
        printf("5 - izlaz\n");
        printf(":");
        scanf("%d", &command);
        //varijabla imena direktorija se mora deklarirat prije switcha jer se u switchu nemogu deklarirat varijable
        char directoryName[50];

        switch (command) {
        case 1:
            printf("Ime direktorija: ");
            scanf(" %s", directoryName);
            createSubdirectory(directoryName, currentDirectory);
            break;
        case 2:
            printf("Ime direktorija: ");
            scanf(" %s", directoryName);
            currentDirectory = chageDirectory(currentDirectory, directoryName);
            break;
        case 3:
            //$$
            currentDirectory = returnToParentDirectory(currentDirectory);
            break;
        case 4:
            listSubdirectories(currentDirectory);
            break;
        case 5:
            printf("Izlaz\n");
            break;
        default:
            printf("Ne postoji ta naredba\n");
        }
    } while (command != 5);

    free(rootDirectory); //nece osloboditi memoriju pod-direktotija, implementirati rekurzivno oslobadanje memorije
    return 0;
}

PositionDirectory createDirectory(char* directoryName) {
    PositionDirectory newDirectory = (PositionDirectory)malloc(sizeof(Directory));
    if (!newDirectory) {
        printf("Neispravno alocirana memorija direktorija\n");
        return NULL;
    }
    strcpy(newDirectory->name, directoryName);
    newDirectory->subDirectories = NULL;
    newDirectory->next = NULL;
    newDirectory->parentDirectory = NULL; //$$
    return newDirectory;
}

int createSubdirectory(char* directoryName, PositionDirectory currentDirectory) {
    PositionDirectory subDirecotry = createDirectory(directoryName);
    if (!subDirecotry) {
        printf("Neuspjesno alocirana memorija poddirektorija\n");
        return -1;
    }
    subDirecotry->next = currentDirectory->subDirectories;
    currentDirectory->subDirectories = subDirecotry;
    subDirecotry->parentDirectory = currentDirectory; //$$
    return 0;
}

PositionDirectory chageDirectory(PositionDirectory currentDirectory, char* nameDirectory){
    PositionDirectory current = currentDirectory->subDirectories;
    while (current != NULL) {
        if (strcmp(current, nameDirectory) == 0) {
            return current;
        }
        current = current->next;
    }
    printf("Nepostoji direktorij tog imena\n");
    return currentDirectory;
}

int listSubdirectories(PositionDirectory currnetDirectory) {
    PositionDirectory current = currnetDirectory->subDirectories;
    if (!current) {
        printf(" %s nema subdirektorija", currnetDirectory);
    }
    else {
        while (current != NULL) {
            printf(" %s", current->name);
            current = current->next;
        }
    }
    return 0;
}

PositionDirectory returnToParentDirectory(PositionDirectory currentDirectory) {

    if (currentDirectory->parentDirectory != NULL) {
        currentDirectory = currentDirectory->parentDirectory;
    }
    else {
        printf("Greska u strukturi direktorija\n");
        return NULL;
    }
    return currentDirectory;
}
