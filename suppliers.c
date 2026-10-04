#include <stdio.h>
#include <string.h>
#include "config.h"
#include "utilities.h"
#include "suppliers.h"

#define STARTING_ID 1001

static int providerIds[MAX_SUPPLIERS];
static char providerNames[MAX_SUPPLIERS][NAME_LEN];
static char providerEmails[MAX_SUPPLIERS][EMAIL_LEN];
static char providerPhones[MAX_SUPPLIERS][PHONE_LEN];
static char providerCities[MAX_SUPPLIERS][TOWN_LEN];

static int totalProviders = 0;
static int idGenerator = STARTING_ID;

int findSupplierById(int id) 
{
    for (int index = 0; index < totalProviders; ++index) {
        if (providerIds[index] == id) {
            return index;
        }
    }
    return -1;
}

int getSupplierCount(void) 
{
    return totalProviders;
}

static int locateProviderByName(const char *targetName) 
{
    for (int index = 0; index < totalProviders; ++index) {
        if (equalsIgnoreCase(providerNames[index], targetName)) {
            return index;
        }
    }
    return -1;
}

static void drawTableHeader(FILE *stream) 
{
    fprintf(stream, "%-6s %-28s %-32s %-14s %-12s\n",
            "ID", "Supplier name", "Email", "Telephone", "Town");
    printLine(stream, '-', 96);
}

// Internal helper rewritten
static void outputProviderRecord(FILE *stream, int index) 
{
    fprintf(stream, "%-6d %-28.28s %-32.32s %-14.14s %-12.12s\n",
            providerIds[index], providerNames[index], providerEmails[index], 
            providerPhones[index], providerCities[index]);
}

void printSupplierTable(FILE *out) 
{
    if (totalProviders == 0) {
        fprintf(out, "  (no suppliers registered)\n");
        return;
    }
    
    drawTableHeader(out);           
    for (int idx = 0; idx < totalProviders; ++idx) {        
        outputProviderRecord(out, idx);
    }
}

void addSupplier(void) 
{
    char inputName[NAME_LEN];
    char inputEmail[EMAIL_LEN];
    char inputPhone[PHONE_LEN];

    printTitle(stdout, "ADD SUPPLIER");
    
    if (totalProviders >= MAX_SUPPLIERS) {
        printf("The supplier table is full (%d suppliers).\n", MAX_SUPPLIERS);
        return;
    }

    while (1) {
        readText("Supplier name : ", inputName, NAME_LEN);
        if (locateProviderByName(inputName) != -1) {
            printf("  A supplier with that name is already registered.\n");
        } else {
            break;
        }
    }
    
    while (1) {
        readText("Email         : ", inputEmail, EMAIL_LEN);
        if (isValidEmail(inputEmail)) {
            break;
        }
        printf("  Invalid email. Example: sales@company.com.na\n");
    }
   
    while (1) {
        readText("Telephone     : ", inputPhone, PHONE_LEN);
        if (isValidPhone(inputPhone)) {
            break;
        }
        printf("  Invalid telephone. Use at least 7 digits, e.g. 061 234 5678 or +264 61 234 5678.\n");
    }
    
    int newIndex = totalProviders;
    providerIds[newIndex] = idGenerator++;
    
    strcpy(providerNames[newIndex], inputName);          
    strcpy(providerEmails[newIndex], inputEmail);
    strcpy(providerPhones[newIndex], inputPhone);
    readText("Town/Location : ", providerCities[newIndex], TOWN_LEN);
    
    totalProviders++;
    printf("\nSupplier registered with ID %d.\n", providerIds[newIndex]);
}

void displaySuppliers(void) 
{
    printTitle(stdout, "ALL SUPPLIERS");
    printSupplierTable(stdout);
    printf("\nTotal suppliers: %d\n", totalProviders);
}

void searchSupplier(void) 
{
    int selection, targetId, recordIndex;
    int foundCount = 0;
    char searchString[NAME_LEN];
    
    printTitle(stdout, "SEARCH SUPPLIER");
    printf("1. Search by supplier ID\n");
    printf("2. Search by name (part of a name is fine)\n");
    printf("3. Search by town\n");
    selection = readInt("Choose search type: ", 1, 3);
    
    if (selection == 1) {
        targetId = readInt("Enter supplier ID: ", 1, 999999);
        recordIndex = findSupplierById(targetId);
        
        if (recordIndex == -1) {
            printf("  No supplier with ID %d was found.\n", targetId);
        } else {
            drawTableHeader(stdout);
            outputProviderRecord(stdout, recordIndex);
        }
        return;
    }
    
    if (selection == 2) {
        readText("Enter name to search: ", searchString, NAME_LEN);
    } else {
        readText("Enter town: ", searchString, TOWN_LEN);
    }
    
    for (int idx = 0; idx < totalProviders; ++idx) {
        int isMatch = 0;
        if (selection == 2) {
            isMatch = containsIgnoreCase(providerNames[idx], searchString);
        } else {
            isMatch = equalsIgnoreCase(providerCities[idx], searchString);
        }
        
        if (isMatch) {
            if (foundCount == 0) {
                drawTableHeader(stdout);
            }
            outputProviderRecord(stdout, idx);
            foundCount++;
        }
    }
    printf("\n%d supplier(s) found.\n", foundCount);
}

void compareSuppliers(void) 
{
    printTitle(stdout, "COMPARE TWO SUPPLIERS");
    
    if (totalProviders < 2) {
        printf("  You need at least two registered suppliers to compare.\n");
        return;
    }
    
    int firstId = readInt("First supplier ID : ", 1, 999999);
    int secondId = readInt("Second supplier ID: ", 1, 999999);
    
    int index1 = findSupplierById(firstId);
    int index2 = findSupplierById(secondId);
    
    if (index1 == -1 || index2 == -1) {
        printf("  One of the supplier IDs was not found.\n");
        return;
    }
    if (index1 == index2) {
        printf("  Please choose two different suppliers.\n");
        return;
    }

    char name1Lower[NAME_LEN], name2Lower[NAME_LEN];
    toLowerCopy(name1Lower, providerNames[index1], NAME_LEN);
    toLowerCopy(name2Lower, providerNames[index2], NAME_LEN);
    
    int comparison = strcmp(name1Lower, name2Lower);
    
    printf("\n  A: %s (%s)\n  B: %s (%s)\n\n", 
           providerNames[index1], providerCities[index1], 
           providerNames[index2], providerCities[index2]);
           
    if (comparison < 0) {
        printf("  Alphabetically, \"%s\" comes before \"%s\".\n", providerNames[index1], providerNames[index2]);
    } else if (comparison > 0) {
        printf("  Alphabetically, \"%s\" comes before \"%s\".\n", providerNames[index2], providerNames[index1]);
    } else {
        printf("  The two names are identical.\n");
    }
    
    if (equalsIgnoreCase(providerCities[index1], providerCities[index2])) {
        printf("  Both suppliers are located in %s.\n", providerCities[index1]);
    } else {
        printf("  They are in different towns (%s and %s).\n", providerCities[index1], providerCities[index2]);
    }
    
    printf("  Name lengths: %d and %d characters.\n",
           (int)strlen(providerNames[index1]), (int)strlen(providerNames[index2]));
}

void supplierMenu(void) 
{
    int userChoice;
    
    do {
        printf("\n");
        printTitle(stdout, "SUPPLIER MANAGEMENT");
        printf("1. Add supplier\n");
        printf("2. Display all suppliers\n");
        printf("3. Search for a supplier\n");
        printf("4. Compare two suppliers\n");
        printf("5. Back to main menu\n");
        
        userChoice = readInt("Enter your choice: ", 1, 5);
        
        switch (userChoice) {
            case 1: 
                addSupplier();       
                break;
            case 2: 
                displaySuppliers();  
                break;
            case 3: 
                searchSupplier();    
                break;
            case 4: 
                compareSuppliers();  
                break;
            default: 
                break;
        }
        
        if (userChoice != 5) {
            pauseScreen();
        }
    } while (userChoice != 5);
}

int saveSuppliers(const char *path) 
{
    FILE *filePointer = fopen(path, "w");
    
    if (filePointer == NULL) {
        perror(path);
        return -1;
    }
    
    for (int idx = 0; idx < totalProviders; ++idx) {
        fprintf(filePointer, "%d|%s|%s|%s|%s\n", 
                providerIds[idx], providerNames[idx], providerEmails[idx],
                providerPhones[idx], providerCities[idx]);
    }
    
    fclose(filePointer);
    return totalProviders;
}

int loadSuppliers(const char *path) 
{
    FILE *filePointer = fopen(path, "r");
    if (filePointer == NULL) {
        return -1;
    }
    
    char buffer[256];
    char tempName[NAME_LEN], tempEmail[EMAIL_LEN], tempPhone[PHONE_LEN], tempCity[TOWN_LEN];
    int tempId;
    int skippedRecords = 0;
    
    totalProviders = 0;
    idGenerator = STARTING_ID;
    
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) {
        size_t length = strlen(buffer);
        
        while (length > 0 && (buffer[length - 1] == '\n' || buffer[length - 1] == '\r')) {
            buffer[--length] = '\0';
        }
        
        if (length == 0) continue;
        
        int parsedFields = sscanf(buffer, "%d|%49[^|]|%59[^|]|%19[^|]|%29[^|]",
                                  &tempId, tempName, tempEmail, tempPhone, tempCity);
                                  
        if (parsedFields == 5 && tempId > 0 && findSupplierById(tempId) == -1 && totalProviders < MAX_SUPPLIERS) {
            providerIds[totalProviders] = tempId;
            strcpy(providerNames[totalProviders], tempName);
            strcpy(providerEmails[totalProviders], tempEmail);
            strcpy(providerPhones[totalProviders], tempPhone);
            strcpy(providerCities[totalProviders], tempCity);
            
            totalProviders++;
            
            if (tempId >= idGenerator) {
                idGenerator = tempId + 1;    
            }
        } else {
            skippedRecords++;
        }
    }
    
    fclose(filePointer);
    
    if (skippedRecords > 0) {
        printf("  Warning: skipped %d invalid record(s) in %s\n", skippedRecords, path);
    }
    
    return totalProviders;
}
