#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct City {
    char name[50];
    int population;
    struct City* next;
} City;
 
typedef struct Country {
    City* cities;
    char name[50];
    struct Country* next;
} Country;
 
typedef struct CityNode {
    char name[50];
    int population;
    struct CityNode* left;
    struct CityNode* right;
} CityNode;
 
typedef struct CountryNode {
    char name[50];
    struct CityNode* cities;
    struct CountryNode* left;
    struct CountryNode* right;
} CountryNode;
 
City* addCity(City* head, char name[], int population) {
    City* newCity = (City*) malloc(sizeof(City));
    strcpy(newCity->name, name);
    newCity->population = population;
    newCity->next = head;
    return newCity;
}
 
City* addCityInOrder(City* head, const char* cityName, int population) {
 
    City* newNode = (City*) malloc(sizeof(City));
    strcpy(newNode->name, cityName);
    newNode->population = population;
 
    if (head == NULL || population > head->population) {
        newNode->next = head;
        return newNode;
    }
 
    City* current = head;
 
    while (current->next != NULL && population < current->next->population) {
        current = current->next;
    }
 
    newNode->next = current->next;
    current->next = newNode;
 
    return head;
}
 
Country* addCountry(Country* head, char name[]) {
    Country* newCountry = (Country*) malloc(sizeof(Country));
    strcpy(newCountry->name, name);
    newCountry->cities = NULL;
    newCountry->next = head;
    return newCountry;
}
 
CountryNode* addCountryToTree(CountryNode* root, char name[]) {
    if (root == NULL) {
        CountryNode* newNode = (CountryNode*) malloc(sizeof(CountryNode));
        strcpy(newNode->name, name);
        newNode->cities = NULL;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
 
    int cmp = strcmp(name, root->name);
    if (cmp < 0) {
        root->left = addCountryToTree(root->left, name);
    }
    else if (cmp > 0) {
        root->right = addCountryToTree(root->right, name);
    }
 
    return root;
}
 
CityNode* createCityNode(const char* cityName, int population) {
    CityNode* newNode = (CityNode*) malloc(sizeof(CityNode));
    if (newNode != NULL) {
        strcpy(newNode->name, cityName);
        newNode->population = population;
        newNode->left = newNode->right = NULL;
    }
    return newNode;
}
 
CountryNode* addCityToCountryTree(CountryNode* country, const char* cityName, int population) {
    if (country == NULL) {
        CountryNode* newCountry = (CountryNode*) malloc(sizeof(CountryNode));
        if (newCountry != NULL) {
            strcpy(newCountry->name, "");
            newCountry->cities = createCityNode(cityName, population);
            newCountry->left = newCountry->right = NULL;
            return newCountry;
        }
        return NULL;
    }
 
    int compareResult = strcmp(cityName, country->name);
    if (compareResult < 0) {
        country->left = addCityToCountryTree(country->left, cityName, population);
    }
    else if (compareResult > 0) {
        country->right = addCityToCountryTree(country->right, cityName, population);
    }
    else {
        CityNode* newCity = createCityNode(cityName, population);
        if (newCity != NULL) {
            if (population < country->cities->population) {
                newCity->left = country->cities;
                country->cities = newCity;
            }
            else {
                CityNode* currentCity = country->cities;
                while (currentCity->right != NULL && population > currentCity->right->population) {
                    currentCity = currentCity->right;
                }
                newCity->right = currentCity->right;
                currentCity->right = newCity;
            }
        }
    }
 
    return country;
}
 
CountryNode* findCountryByName(CountryNode* countryTree, const char* countryName) {
    if (countryTree == NULL) {
        return NULL;
    }
 
    int compareResult = strcmp(countryName, countryTree->name);
    if (compareResult < 0) {
        return findCountryByName(countryTree->left, countryName);
    }
    else if (compareResult > 0) {
        return findCountryByName(countryTree->right, countryName);
    }
    else {
        return countryTree;
    }
}
 
 
void printCities(City* cities) {
    while (cities != NULL) {
        printf("%s (%d)  ", cities->name, cities->population);
        cities = cities->next;
    }
    printf("\n");
}
 
void printCountries(Country* countries) {
    while (countries != NULL) {
        printf("%s:\n", countries->name);
        printCities(countries->cities);
        printf("\n");
        countries = countries->next;
    }
}
 
void printCitiesInTree(CityNode* root) {
    if (root == NULL) {
        return;
    }
 
    printCitiesInTree(root->left);
 
    printf("%s (%d)  ", root->name, root->population);
 
    printCitiesInTree(root->right);
}
 
 
void printCountriesInTree(CountryNode* root) {
    if (root != NULL) {
        printCountriesInTree(root->left);
        printf("%s:\n", root->name);
        printCitiesInTree(root->cities);
        printf("\n");
        printCountriesInTree(root->right);
    }
}
 
void searchCities(Country* countries, int populationThreshold) {
    int found = 0;
 
    while (countries != NULL) {
        City* city = countries->cities;
        while (city != NULL) {
            if (city->population > populationThreshold) {
                if (!found) {
                    printf("Gradovi s brojem stanovnika vecim od %d:\n", populationThreshold);
                    found = 1;
                }
                printf("%s, %s (%d)\n", countries->name, city->name, city->population);
            }
            city = city->next;
        }
        countries = countries->next;
    }
 
    if (!found) {
        printf("Nema gradova s brojem stanovnika vecim od %d.\n", populationThreshold);
    }
}
 
int main() {
 
    FILE* file = fopen("drzave.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
 
    char countryName[50];
    char cityFileName[50];
    char cityName[50];
    int population;
 
    Country* countriesList = NULL; // Vezana lista država
    CountryNode* countriesTree = NULL; // Binarno stablo država
 
    while (fscanf(file, "%s %s", countryName, cityFileName) == 2) {
        countriesList = addCountry(countriesList, countryName);
 
        countriesTree = addCountryToTree(countriesTree, countryName);
 
        FILE* cityFile = fopen(cityFileName, "r");
        if (cityFile == NULL) {
            perror("Error opening city file");
            return 1;
        }
 
        while (fscanf(cityFile, "%s %d", cityName, &population) == 2) {
 
            addCityToCountryTree(findCountryByName(countriesTree, countryName), cityName, population);
 
            Country* currentCountry = countriesList;
            while (currentCountry != NULL) {
                if (strcmp(currentCountry->name, countryName) == 0) {
                    currentCountry->cities = addCityInOrder(currentCountry->cities, cityName, population);
                    break;
                }
                currentCountry = currentCountry->next;
            }
 
        }
 
        fclose(cityFile);
    }
 
    fclose(file);
 
    printf("Drzave i gradovi iz vezane liste:\n");
    printCountries(countriesList);
 
    printf("\nDrzave i gradovi iz binarnog stabla:\n");
    printCountriesInTree(countriesTree);
 
    int populationThreshold;
    printf("\nUnesite broj stanovnika za pretragu: ");
    scanf("%d", &populationThreshold);
    searchCities(countriesList, populationThreshold);
 
    return 0;
}
