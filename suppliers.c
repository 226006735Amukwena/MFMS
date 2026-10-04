#include <stdio.h>
#include <string.h>
#include "config.h"
#include "utils.h"
#include "suppliers.h"

#define FIRST_SUPPLIER_ID 1001          //the first supplier ID to be assigned//

static int  supId[MAX_SUPPLIERS];
static char supName[MAX_SUPPLIERS][SUP_NAME_LEN];
static char supEmail[MAX_SUPPLIERS][SUP_EMAIL_LEN];
static char supPhone[MAX_SUPPLIERS][SUP_PHONE_LEN];
static char supTown[MAX_SUPPLIERS][SUP_TOWN_LEN];
static int  supCount = 0;
static int  nextSupplierId = FIRST_SUPPLIER_ID;

//arrays to store supplier data, and counters for the number of suppliers and the next ID to assign//
int findSupplierById(int id)
{
    int i;

    for (i = 0; i < supCount; i++) {
        if (supId[i] == id) {
            return i;
        }
    }
    return -1;
}
//returns the number of suppliers currently registered//
int getSupplierCount(void)
{
    return supCount;
}
//returns the index of a supplier with the given name, or -1 if not found//
static int findSupplierByName(const char name[])
{
    int i;

    for (i = 0; i < supCount; i++) {
        if (equalsIgnoreCase(supName[i], name)) {
            return i;
        }
    }
    return -1;
}
//prints the header row for the supplier table//
static void printSupplierHeader(FILE *out)
{
    fprintf(out, "%-6s %-28s %-32s %-14s %-12s\n",
            "ID", "Supplier name", "Email", "Telephone", "Town");
    printLine(out, '-', 96);
}
//prints a single row of supplier data for the supplier at index i//
static void printSupplierRow(FILE *out, int i)
{
    fprintf(out, "%-6d %-28.28s %-32.32s %-14.14s %-12.12s\n",
            supId[i], supName[i], supEmail[i], supPhone[i], supTown[i]);
}
//prints the entire supplier table to the given output stream//
void printSupplierTable(FILE *out)
{
    int i;
    //
    if (supCount == 0) {
        fprintf(out, "  (no suppliers registered)\n");
        return;
    }
    printSupplierHeader(out);           
    for (i = 0; i < supCount; i++) {        
        printSupplierRow(out, i);
    }
}
//adds a new supplier by prompting the user for input and storing the data in the arrays//
void addSupplier(void)
{
    char name[SUP_NAME_LEN];
    char email[SUP_EMAIL_LEN];
    char phone[SUP_PHONE_LEN];
    int n;
// displays the "ADD SUPPLIER" title and checks if the supplier table is full//
    printTitle(stdout, "ADD SUPPLIER");
    if (supCount >= MAX_SUPPLIERS) {
        printf("The supplier table is full (%d suppliers).\n", MAX_SUPPLIERS);
        return;
    }

   //prompts the user for supplier name, email, and phone number, validating each input//
    for (;;) {
        readText("Supplier name : ", name, SUP_NAME_LEN);
        if (findSupplierByName(name) != -1) {
            printf("  A supplier with that name is already registered.\n");
        } else {
            break;
        }
    }
    //
    for (;;) {
        readText("Email         : ", email, SUP_EMAIL_LEN);
        if (isValidEmail(email)) {
            break;
        }
        printf("  Invalid email. Example: sales@company.com.na\n");
    }
   //prompts the user for a valid phone number, ensuring it meets the required format//
    for (;;) {
        readText("Telephone     : ", phone, SUP_PHONE_LEN);
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
    readText("Town/Location : ", supTown[n], SUP_TOWN_LEN);
    supCount++;

    printf("\nSupplier registered with ID %d.\n", supId[n]);
}
 //displays all registered suppliers in a formatted table, along with the total count//
void displaySuppliers(void)
{
    printTitle(stdout, "ALL SUPPLIERS");
    printSupplierTable(stdout);
    printf("\nTotal suppliers: %d\n", supCount);
}
//searches for suppliers based on user input, either by ID, name, or town, and displays the results//
void searchSupplier(void)
{
    int choice;
    int id;
    int index;
    int i;
    int matches = 0;
    char text[SUP_NAME_LEN];
    //displays the search menu and prompts the user to choose a search type//
    printTitle(stdout, "SEARCH SUPPLIER");
    printf("1. Search by supplier ID\n");
    printf("2. Search by name (part of a name is fine)\n");
    printf("3. Search by town\n");
    choice = readInt("Choose search type: ", 1, 3);
    //performs the search based on the user's choice and displays matching suppliers//
    if (choice == 1) {
        id = readInt("Enter supplier ID: ", 1, 999999);
        index = findSupplierById(id);
        if (index == -1) {
            printf("  No supplier with ID %d was found.\n", id);
        } else {
            printSupplierHeader(stdout);
            printSupplierRow(stdout, index);
        }
        return;
    }
    if (choice == 2) {
        readText("Enter name to search: ", text, SUP_NAME_LEN);
    } else {
        readText("Enter town: ", text, SUP_TOWN_LEN);
    }
    for (i = 0; i < supCount; i++) {
        int hit;
        if (choice == 2) {
            hit = containsIgnoreCase(supName[i], text);
        } else {
            hit = equalsIgnoreCase(supTown[i], text);
        }
        if (hit) {
            if (matches == 0) {
                printSupplierHeader(stdout);
            }
            printSupplierRow(stdout, i);
            matches++;
        }
    }
    printf("\n%d supplier(s) found.\n", matches);
}
//compares two suppliers based on their names and towns, providing information about their alphabetical order and location//
void compareSuppliers(void)
{
    int idA;
    int idB;
    int a;
    int b;
    int order;
    char lowerA[SUP_NAME_LEN];
    char lowerB[SUP_NAME_LEN];
// displays the "COMPARE TWO SUPPLIERS" title and checks if there are at least two suppliers to compare//
    printTitle(stdout, "COMPARE TWO SUPPLIERS");
    if (supCount < 2) {
        printf("  You need at least two registered suppliers to compare.\n");
        return;
    }
    idA = readInt("First supplier ID : ", 1, 999999);
    idB = readInt("Second supplier ID: ", 1, 999999);
    a = findSupplierById(idA);
    b = findSupplierById(idB);
    if (a == -1 || b == -1) {
        printf("  One of the supplier IDs was not found.\n");
        return;
    }
    if (a == b) {
        printf("  Please choose two different suppliers.\n");
        return;
    }

   //converts the supplier names to lowercase for case-insensitive comparison and determines their alphabetical order//
    toLowerCopy(lowerA, supName[a], SUP_NAME_LEN);
    toLowerCopy(lowerB, supName[b], SUP_NAME_LEN);
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
    if (equalsIgnoreCase(supTown[a], supTown[b])) {
        printf("  Both suppliers are located in %s.\n", supTown[a]);
    } else {
        printf("  They are in different towns (%s and %s).\n", supTown[a], supTown[b]);
    }
    printf("  Name lengths: %d and %d characters.\n",
           (int)strlen(supName[a]), (int)strlen(supName[b]));
}
//displays the supplier management menu and handles user input for various supplier-related operations//
void supplierMenu(void)
{
    int choice;
    //displays the supplier management menu and handles user input for various supplier-related operations//
    do {
        printf("\n");
        printTitle(stdout, "SUPPLIER MANAGEMENT");
        printf("1. Add supplier\n");
        printf("2. Display all suppliers\n");
        printf("3. Search for a supplier\n");
        printf("4. Compare two suppliers\n");
        printf("5. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 5);
        //performs the selected operation based on the user's choice//
        switch (choice) {
            case 1: addSupplier();       
                break;
            case 2: displaySuppliers();  
                break;
            case 3: searchSupplier();    
                break;
            case 4: compareSuppliers();  
                break;
            default: break;
        }
        if (choice != 5) {
            pauseScreen();
        }
    } while (choice != 5);
}

//saves the supplier data to a file specified by the given path, returning the number of suppliers saved or -1 on error//
int saveSuppliers(const char *path)
{
    FILE *fp = fopen(path, "w");
    int i;
    //opens the specified file for writing and checks for errors//
    if (fp == NULL) {
        perror(path);
        return -1;
    }
    for (i = 0; i < supCount; i++) {
        fprintf(fp, "%d|%s|%s|%s|%s\n", supId[i], supName[i], supEmail[i],
                supPhone[i], supTown[i]);
    }
    fclose(fp);
    return supCount;
}
//loads supplier data from a file specified by the given path, returning the number of suppliers loaded or -1 on error//
int loadSuppliers(const char *path)
{
    FILE *fp = fopen(path, "r");
    char line[256];
    char name[SUP_NAME_LEN];
    char email[SUP_EMAIL_LEN];
    char phone[SUP_PHONE_LEN];
    char town[SUP_TOWN_LEN];
    int id;
    int skipped = 0;
    size_t len;
    //opens the specified file for reading and checks for errors//
    if (fp == NULL) {
        return -1;
    }
    supCount = 0;
    nextSupplierId = FIRST_SUPPLIER_ID;
    while (fgets(line, sizeof(line), fp) != NULL) {
        len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[--len] = '\0';
        }
        if (len == 0) {
            continue;
        }
        //parses the line from the file and extracts supplier data, validating the input and storing it in the arrays//
        if (sscanf(line, "%d|%49[^|]|%59[^|]|%19[^|]|%29[^|]",
                   &id, name, email, phone, town) == 5
            && id > 0 && findSupplierById(id) == -1 && supCount < MAX_SUPPLIERS) {
            supId[supCount] = id;
            strcpy(supName[supCount], name);
            strcpy(supEmail[supCount], email);
            strcpy(supPhone[supCount], phone);
            strcpy(supTown[supCount], town);
            supCount++;
            if (id >= nextSupplierId) {
                nextSupplierId = id + 1;    
            }
        } else {
            skipped++;
        }
    }
    //closes the file and displays a warning if any invalid records were skipped during loading//
    fclose(fp);
    if (skipped > 0) {
        printf("  Warning: skipped %d invalid record(s) in %s\n", skipped, path);
    }
    return supCount;
}
