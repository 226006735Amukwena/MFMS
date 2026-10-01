/*
 * suppliers.c  -  Supplier Management module (Week 7: strings)
 *
 * Every supplier has: ID, name, email, telephone and town, stored in
 * parallel arrays.  Supplier IDs are generated automatically.
 */
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "utilities.h"
#include "suppliers.h"

#define FIRST_SUPPLIER_ID 1001

static int  supId[MAX_SUPPLIERS];
static char supName[MAX_SUPPLIERS][NAME_LEN];
static char supEmail[MAX_SUPPLIERS][EMAIL_LEN];
static char supPhone[MAX_SUPPLIERS][PHONE_LEN];
static char supTown[MAX_SUPPLIERS][TOWN_LEN];
static int  supCount = 0;
static int  nextSupplierId = FIRST_SUPPLIER_ID;

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

int getSupplierCount(void)
{
    return supCount;
}

/* Index of a supplier with exactly this name (any letter case), or -1. */
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

/* ------------------------------------------------------------------ */
/*  Display helpers                                                    */
/* ------------------------------------------------------------------ */

static void printSupplierHeader(FILE *out)
{
    fprintf(out, "%-6s %-28s %-32s %-14s %-12s\n",
            "ID", "Supplier name", "Email", "Telephone", "Town");
    printLine(out, '-', 96);
}

static void printSupplierRow(FILE *out, int i)
{
    fprintf(out, "%-6d %-28.28s %-32.32s %-14.14s %-12.12s\n",
            supId[i], supName[i], supEmail[i], supPhone[i], supTown[i]);
}

void printSupplierTable(FILE *out)
{
    int i;

    if (supCount == 0) {
        fprintf(out, "  (no suppliers registered)\n");
        return;
    }
    printSupplierHeader(out);
    for (i = 0; i < supCount; i++) {
        printSupplierRow(out, i);
    }
}

/* ------------------------------------------------------------------ */
/*  User-facing operations                                             */
/* ------------------------------------------------------------------ */

void addSupplier(void)
{
    char name[NAME_LEN];
    char email[EMAIL_LEN];
    char phone[PHONE_LEN];
    int n;

    printTitle(stdout, "ADD SUPPLIER");
    if (supCount >= MAX_SUPPLIERS) {
        printf("The supplier table is full (%d suppliers).\n", MAX_SUPPLIERS);
        return;
    }

    /* Supplier name: not empty and not already registered (strcmp). */
    for (;;) {
        readText("Supplier name : ", name, NAME_LEN);
        if (findSupplierByName(name) != -1) {
            printf("  A supplier with that name is already registered.\n");
        } else {
            break;
        }
    }
    /* Email: must look like name@domain.xx */
    for (;;) {
        readText("Email         : ", email, EMAIL_LEN);
        if (isValidEmail(email)) {
            break;
        }
        printf("  Invalid email. Example: sales@company.com.na\n");
    }
    /* Telephone: at least 7 digits; digits, spaces, '-' and a leading '+' */
    for (;;) {
        readText("Telephone     : ", phone, PHONE_LEN);
        if (isValidPhone(phone)) {
            break;
        }
        printf("  Invalid telephone. Use at least 7 digits, e.g. 061 234 5678 or +264 61 234 5678.\n");
    }

    n = supCount;
    supId[n] = nextSupplierId++;
    strcpy(supName[n], name);           /* strcpy: copy validated text into the table */
    strcpy(supEmail[n], email);
    strcpy(supPhone[n], phone);
    readText("Town/Location : ", supTown[n], TOWN_LEN);
    supCount++;

    printf("\nSupplier registered with ID %d.\n", supId[n]);
}

void displaySuppliers(void)
{
    printTitle(stdout, "ALL SUPPLIERS");
    printSupplierTable(stdout);
    printf("\nTotal suppliers: %d\n", supCount);
}

void searchSupplier(void)
{
    int choice;
    int id;
    int index;
    int i;
    int matches = 0;
    char text[NAME_LEN];

    printTitle(stdout, "SEARCH SUPPLIER");
    printf("1. Search by supplier ID\n");
    printf("2. Search by name (part of a name is fine)\n");
    printf("3. Search by town\n");
    choice = readInt("Choose search type: ", 1, 3);

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
        readText("Enter name to search: ", text, NAME_LEN);
    } else {
        readText("Enter town: ", text, TOWN_LEN);
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

/* Compare two suppliers: alphabetical order, same town?, name lengths. */
void compareSuppliers(void)
{
    int idA;
    int idB;
    int a;
    int b;
    int order;
    char lowerA[NAME_LEN];
    char lowerB[NAME_LEN];

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

    /* strcmp returns <0, 0 or >0 depending on alphabetical order (Week 7). */
    toLowerCopy(lowerA, supName[a], NAME_LEN);
    toLowerCopy(lowerB, supName[b], NAME_LEN);
    order = strcmp(lowerA, lowerB);

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

void supplierMenu(void)
{
    int choice;

    do {
        printf("\n");
        printTitle(stdout, "SUPPLIER MANAGEMENT");
        printf("1. Add supplier\n");
        printf("2. Display all suppliers\n");
        printf("3. Search for a supplier\n");
        printf("4. Compare two suppliers\n");
        printf("5. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

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

/* ------------------------------------------------------------------ */
/*  Persistence (Week 10)                                              */
/* ------------------------------------------------------------------ */

int saveSuppliers(const char *path)
{
    FILE *fp = fopen(path, "w");
    int i;

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

int loadSuppliers(const char *path)
{
    FILE *fp = fopen(path, "r");
    char line[256];
    char name[NAME_LEN];
    char email[EMAIL_LEN];
    char phone[PHONE_LEN];
    char town[TOWN_LEN];
    int id;
    int skipped = 0;
    size_t len;

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
        /* widths: NAME_LEN-1=49, EMAIL_LEN-1=59, PHONE_LEN-1=19, TOWN_LEN-1=29 */
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
                nextSupplierId = id + 1;    /* keep future IDs unique */
            }
        } else {
            skipped++;
        }
    }
    fclose(fp);
    if (skipped > 0) {
        printf("  Warning: skipped %d invalid record(s) in %s\n", skipped, path);
    }
    return supCount;
}
