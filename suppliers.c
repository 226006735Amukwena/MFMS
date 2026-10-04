#include <stdio.h>
#include <string.h>
#include "config.h"
#include "utils.h"
#include "suppliers.h"

#ifndef NAME_LEN
#define NAME_LEN 50
#endif

#ifndef EMAIL_LEN
#define EMAIL_LEN SUP_EMAIL_LEN
#endif

#ifndef PHONE_LEN
#define PHONE_LEN SUP_PHONE_LEN
#endif

#ifndef TOWN_LEN
#define TOWN_LEN SUP_TOWN_LEN
#endif

#define FIRST_SUPPLIER_ID 1001          //the first supplier ID to be assigned//

static int  supId[MAX_SUPPLIERS];
static char supName[MAX_SUPPLIERS][NAME_LEN];
static char supEmail[MAX_SUPPLIERS][EMAIL_LEN];
static char supPhone[MAX_SUPPLIERS][PHONE_LEN];
static char supTown[MAX_SUPPLIERS][TOWN_LEN];
static int  supCount = 0;
#define totalProviders supCount
static int  nextSupplierId = FIRST_SUPPLIER_ID;

int findSupplierById(int id) 
{
    for (int index = 0; index < totalProviders; ++index) {
        if (supId[index] == id) {
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
        if (equalsIgnoreCase(supName[index], targetName)) {
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
            supId[index], supName[index], supEmail[index], 
            supPhone[index], supTown[index]);
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
    char name[NAME_LEN];
    char email[EMAIL_LEN];
    char phone[PHONE_LEN];
    int n;
// displays the "ADD SUPPLIER" title and checks if the supplier table is full//
    printTitle(stdout, "ADD SUPPLIER");
    
    if (totalProviders >= MAX_SUPPLIERS) {
        printf("The supplier table is full (%d suppliers).\n", MAX_SUPPLIERS);
        return;
    }

   //prompts the user for supplier name, email, and phone number, validating each input//
    for (;;) {
        readText("Supplier name : ", name, NAME_LEN);
        if (findSupplierByName(name) != -1) {
            printf("  A supplier with that name is already registered.\n");
        } else {
            break;
        }
    }
    //
    for (;;) {
        readText("Email         : ", email, EMAIL_LEN);
        if (isValidEmail(email)) {
            break;
        }
        printf("  Invalid email. Example: sales@company.com.na\n");
    }
   //prompts the user for a valid phone number, ensuring it meets the required format//
    for (;;) {
        readText("Telephone     : ", phone, PHONE_LEN);
        if (isValidPhone(phone)) {
            break;
        }
        printf("  Invalid telephone. Use at least 7 digits, e.g. 061 234 5678 or +264 61 234 5678.\n");
    }
    //stores the new supplier data in the arrays and increments the supplier count//
    n = supCount;
    supId[n] = nextSupplierId++;
    strcpy(supName[n], name);          
    strcpy(supEmail[n], email);
    strcpy(supPhone[n], phone);
    readText("Town/Location : ", supTown[n], TOWN_LEN);
    supCount++;

    printf("\nSupplier registered with ID %d.\n", supId[n]);
}
 //displays all registered suppliers in a formatted table, along with the total count//
void displaySuppliers(void)
{
    printTitle(stdout, "ALL SUPPLIERS");
    printSupplierTable(stdout);
    printf("\nTotal suppliers: %d\n", totalProviders);
}

void searchSupplier(void) 
{
    int selection;
    int id;
    int index;
    int i;
    int matches = 0;
    char text[NAME_LEN];
    //displays the search menu and prompts the user to choose a search type//
    printTitle(stdout, "SEARCH SUPPLIER");
    printf("1. Search by supplier ID\n");
    printf("2. Search by name (part of a name is fine)\n");
    printf("3. Search by town\n");
    selection = readInt("Choose search type: ", 1, 3);
    
    if (selection == 1) {
        id = readInt("Enter supplier ID: ", 1, 999999);
        index = findSupplierById(id);
        
        if (index == -1) {
            printf("  No supplier with ID %d was found.\n", id);
        } else {
            drawTableHeader(stdout);
            outputProviderRecord(stdout, index);
        }
        return;
    }
    if (selection == 2) {
        readText("Enter name to search: ", text, NAME_LEN);
    } else {
        readText("Enter town: ", text, TOWN_LEN);
    }
    
    for (int idx = 0; idx < totalProviders; ++idx) {
        int isMatch = 0;
        if (selection == 2) {
            isMatch = containsIgnoreCase(supName[idx], text);
        } else {
            isMatch = equalsIgnoreCase(supTown[idx], text);
        }
        
        if (isMatch) {
            if (matches == 0) {
                drawTableHeader(stdout);
            }
            outputProviderRecord(stdout, idx);
            matches++;
        }
    }
    printf("\n%d supplier(s) found.\n", matches);
}

void compareSuppliers(void) 
{
    int idA;
    int idB;
    int a;
    int b;
    int order;
    char lowerA[NAME_LEN];
    char lowerB[NAME_LEN];
// displays the "COMPARE TWO SUPPLIERS" title and checks if there are at least two suppliers to compare//
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

    a = index1;
    b = index2;

   //converts the supplier names to lowercase for case-insensitive comparison and determines their alphabetical order//
    toLowerCopy(lowerA, supName[a], NAME_LEN);
    toLowerCopy(lowerB, supName[b], NAME_LEN);
    order = strcmp(lowerA, lowerB);
    //displays the comparison results, including alphabetical order, town location, and name lengths//
    printf("\n  A: %s (%s)\n  B: %s (%s)\n\n", supName[a], supTown[a], supName[b], supTown[b]);
    if (order < 0) {
        printf("  Alphabetically, \"%s\" comes before \"%s\".\n", supName[a], supName[b]);
    } else if (order > 0) {
        printf("  Alphabetically, \"%s\" comes before \"%s\".\n", supName[b], supName[a]);
    } else {
        printf("  The two names are identical.\n");
    }
    
    if (equalsIgnoreCase(supTown[index1], supTown[index2])) {
        printf("  Both suppliers are located in %s.\n", supTown[index1]);
    } else {
        printf("  They are in different towns (%s and %s).\n", supTown[index1], supTown[index2]);
    }
    
    printf("  Name lengths: %d and %d characters.\n",
           (int)strlen(supName[index1]), (int)strlen(supName[index2]));
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
                supId[idx], supName[idx], supEmail[idx],
                supPhone[idx], supTown[idx]);
    }
    
    fclose(filePointer);
    return totalProviders;
}

int loadSuppliers(const char *path) 
{
    FILE *fp = fopen(path, "r");

    if (fp == NULL) {
        perror(path);
        return -1;
    }

    char buffer[256];
    char tempName[NAME_LEN], tempEmail[EMAIL_LEN], tempPhone[PHONE_LEN], tempCity[TOWN_LEN];
    int tempId;
    int skippedRecords = 0;

    totalProviders = 0;
    nextSupplierId = FIRST_SUPPLIER_ID;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t length = strlen(buffer);

        while (length > 0 && (buffer[length - 1] == '\n' || buffer[length - 1] == '\r')) {
            buffer[--length] = '\0';
        }

        if (length == 0) continue;

        int parsedFields = sscanf(buffer, "%d|%49[^|]|%59[^|]|%19[^|]|%29[^|]",
                                  &tempId, tempName, tempEmail, tempPhone, tempCity);

        if (parsedFields == 5 && tempId > 0 && findSupplierById(tempId) == -1 && totalProviders < MAX_SUPPLIERS) {
            supId[totalProviders] = tempId;
            strcpy(supName[totalProviders], tempName);
            strcpy(supEmail[totalProviders], tempEmail);
            strcpy(supPhone[totalProviders], tempPhone);
            strcpy(supTown[totalProviders], tempCity);

            totalProviders++;

            if (tempId >= nextSupplierId) {
                nextSupplierId = tempId + 1;
            }
        } else {
            skippedRecords++;
        }
    }

    fclose(fp);

    if (skippedRecords > 0) {
        printf("  Warning: skipped %d invalid record(s) in %s\n", skippedRecords, path);
    }

    return totalProviders;
}
