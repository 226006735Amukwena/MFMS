/*
 * budget.c
 * Budget Management module - Municipal Financial Management System (MFMS)
 * PAP521S - Project A
 *
 * Department budgets are stored in parallel arrays: the same index in
 * deptNames[], allocatedBudgets[] and expenditures[] refers to the
 * same department.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "budget.h"

#define INPUT_SIZE  64          /* buffer size for numbers / menu choices */
#define MAX_AMOUNT  1000000000000.0   /* upper limit for any money value  */

/* Result codes for readLine() */
#define INPUT_OK       1
#define INPUT_EOF      0
#define INPUT_TOO_LONG -1

/* ---------- Data storage (private to this module) ---------- */

static char   deptNames[MAX_DEPARTMENTS][MAX_DEPT_NAME];
static double allocatedBudgets[MAX_DEPARTMENTS];
static double expenditures[MAX_DEPARTMENTS];
static int    departmentCount = 0;

/* ================================================================
 *  INPUT HELPERS (private)
 * ================================================================ */

/* Reads one line from the keyboard into buffer and removes the '\n'.
   Any characters that do not fit are discarded. */
static int readLine(char *buffer, int size)
{
    size_t len;
    int ch;

    if (fgets(buffer, size, stdin) == NULL) {
        return INPUT_EOF;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        return INPUT_OK;
    }

    if (feof(stdin)) {              /* last line without a newline */
        return INPUT_OK;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* throw away the rest of the long line */
    }
    return INPUT_TOO_LONG;
}

/* Removes leading and trailing spaces/tabs from a string. */
static void trimWhitespace(char *text)
{
    size_t start = 0;
    size_t len;

    while (text[start] != '\0' && isspace((unsigned char)text[start])) {
        start++;
    }
    if (start > 0) {
        memmove(text, text + start, strlen(text + start) + 1);
    }

    len = strlen(text);
    while (len > 0 && isspace((unsigned char)text[len - 1])) {
        text[--len] = '\0';
    }
}

/* Keeps asking until the user enters a valid department name.
   Returns 1 on success, 0 if input ended (EOF). */
static int readDepartmentName(const char *prompt, char *name)
{
    char buffer[MAX_DEPT_NAME + 1];
    int status;

    while (1) {
        printf("%s", prompt);
        status = readLine(buffer, (int)sizeof(buffer));

        if (status == INPUT_EOF) {
            return 0;
        }
        if (status == INPUT_TOO_LONG) {
            printf("Error: Name is too long (maximum %d characters).\n",
                   MAX_DEPT_NAME - 1);
            continue;
        }

        trimWhitespace(buffer);
        if (strlen(buffer) == 0) {
            printf("Error: Department name cannot be empty.\n");
            continue;
        }

        strcpy(name, buffer);
        return 1;
    }
}

/* Keeps asking until the user enters a valid, non-negative amount.
   If allowZero is 0, the amount must be greater than zero.
   Returns 1 on success, 0 if input ended (EOF). */
static int readAmount(const char *prompt, double *value, int allowZero)
{
    char buffer[INPUT_SIZE];
    char *end;
    double number;
    int status;

    while (1) {
        printf("%s", prompt);
        status = readLine(buffer, (int)sizeof(buffer));

        if (status == INPUT_EOF) {
            return 0;
        }
        if (status == INPUT_TOO_LONG) {
            printf("Error: Input is too long.\n");
            continue;
        }

        trimWhitespace(buffer);
        if (strlen(buffer) == 0) {
            printf("Error: Input cannot be empty.\n");
            continue;
        }

        number = strtod(buffer, &end);
        if (*end != '\0') {
            printf("Error: Please enter a valid number.\n");
        } else if (!(number <= MAX_AMOUNT)) {      /* also catches nan/inf */
            printf("Error: Value is too large.\n");
        } else if (number < 0) {
            printf("Error: Values cannot be negative.\n");
        } else if (!allowZero && number == 0) {
            printf("Error: Value must be greater than zero.\n");
        } else {
            *value = number;
            return 1;
        }
    }
}

/* Keeps asking until the user enters a whole number between min and max.
   Returns 1 on success, 0 if input ended (EOF). */
static int readMenuChoice(int min, int max, int *choice)
{
    char buffer[INPUT_SIZE];
    char *end;
    long number;
    int status;

    while (1) {
        printf("Enter your choice: ");
        status = readLine(buffer, (int)sizeof(buffer));

        if (status == INPUT_EOF) {
            return 0;
        }

        trimWhitespace(buffer);
        number = strtol(buffer, &end, 10);

        if (status == INPUT_TOO_LONG || strlen(buffer) == 0 || *end != '\0'
            || number < min || number > max) {
            printf("Invalid choice. Please enter a number from %d to %d.\n",
                   min, max);
        } else {
            *choice = (int)number;
            return 1;
        }
    }
}

/* ================================================================
 *  CALCULATIONS
 * ================================================================ */

double calculateRemaining(double allocated, double expenditure)
{
    return allocated - expenditure;
}

int isWithinBudget(double allocated, double expenditure)
{
    return expenditure <= allocated;
}

int findDepartment(const char *name)
{
    int i;

    for (i = 0; i < departmentCount; i++) {
        if (strcmp(deptNames[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

/* ================================================================
 *  DISPLAY
 * ================================================================ */

/* Prints the details of one department (private helper). */
static void printDepartment(int index)
{
    double remaining = calculateRemaining(allocatedBudgets[index],
                                          expenditures[index]);

    printf("Department: %s\n", deptNames[index]);
    printf("Allocated Budget: N$%.2f\n", allocatedBudgets[index]);
    printf("Expenditure: N$%.2f\n", expenditures[index]);
    printf("Remaining Budget: N$%.2f\n", remaining);

    if (isWithinBudget(allocatedBudgets[index], expenditures[index])) {
        printf("Status: WITHIN BUDGET\n");
    } else {
        printf("Status: OVER BUDGET\n");
    }
}

void displayBudgets(void)
{
    int i;

    if (departmentCount == 0) {
        printf("\nNo department budgets have been entered yet.\n");
        return;
    }

    printf("\n===== DEPARTMENT BUDGETS =====\n");
    for (i = 0; i < departmentCount; i++) {
        printf("\n[%d]\n", i + 1);
        printDepartment(i);
    }
}

void searchDepartment(void)
{
    char name[MAX_DEPT_NAME];
    int index;

    if (departmentCount == 0) {
        printf("\nNo department budgets have been entered yet.\n");
        return;
    }

    if (!readDepartmentName("Enter department name to search: ", name)) {
        return;
    }

    index = findDepartment(name);
    if (index == -1) {
        printf("Department \"%s\" was not found.\n", name);
    } else {
        printf("\n");
        printDepartment(index);
    }
}

int displayOverBudgetDepartments(void)
{
    int i;
    int count = 0;

    printf("\n===== DEPARTMENTS OVER BUDGET =====\n");
    for (i = 0; i < departmentCount; i++) {
        if (!isWithinBudget(allocatedBudgets[i], expenditures[i])) {
            count++;
            printf("%d. %s - exceeded by N$%.2f\n", count, deptNames[i],
                   expenditures[i] - allocatedBudgets[i]);
        }
    }

    if (count == 0) {
        printf("No department has exceeded its budget.\n");
    }
    return count;
}

/* ================================================================
 *  DATA ENTRY
 * ================================================================ */

int addDepartmentBudget(void)
{
    char name[MAX_DEPT_NAME];
    double allocated;
    double spent;

    if (departmentCount >= MAX_DEPARTMENTS) {
        printf("Error: Maximum number of departments (%d) reached.\n",
               MAX_DEPARTMENTS);
        return 0;
    }

    if (!readDepartmentName("Enter department name: ", name)) {
        return 0;
    }

    if (findDepartment(name) != -1) {
        printf("Error: \"%s\" already exists. Use 'Record expenditure' "
               "to add spending.\n", name);
        return 0;
    }

    if (!readAmount("Enter allocated budget (N$): ", &allocated, 0)) {
        return 0;
    }
    if (!readAmount("Enter expenditure so far (N$, 0 if none): ",
                    &spent, 1)) {
        return 0;
    }

    strcpy(deptNames[departmentCount], name);
    allocatedBudgets[departmentCount] = allocated;
    expenditures[departmentCount] = spent;
    departmentCount++;

    printf("\nBudget saved:\n");
    printDepartment(departmentCount - 1);
    return 1;
}

void recordExpenditure(void)
{
    char name[MAX_DEPT_NAME];
    double amount;
    int index;

    if (departmentCount == 0) {
        printf("\nNo department budgets have been entered yet.\n");
        return;
    }

    if (!readDepartmentName("Enter department name: ", name)) {
        return;
    }

    index = findDepartment(name);
    if (index == -1) {
        printf("Department \"%s\" was not found.\n", name);
        return;
    }

    if (!readAmount("Enter expenditure amount to add (N$): ", &amount, 0)) {
        return;
    }

    if (expenditures[index] + amount > MAX_AMOUNT) {
        printf("Error: Total expenditure would be too large.\n");
        return;
    }

    expenditures[index] += amount;

    printf("\nExpenditure recorded:\n");
    printDepartment(index);

    if (!isWithinBudget(allocatedBudgets[index], expenditures[index])) {
        printf("WARNING: %s has exceeded its allocated budget!\n",
               deptNames[index]);
    }
}

/* ================================================================
 *  SUPPORT FOR REPORTS MODULE
 * ================================================================ */

int getDepartmentCount(void)
{
    return departmentCount;
}

double getTotalAllocated(void)
{
    double total = 0;
    int i;

    for (i = 0; i < departmentCount; i++) {
        total += allocatedBudgets[i];
    }
    return total;
}

double getTotalExpenditure(void)
{
    double total = 0;
    int i;

    for (i = 0; i < departmentCount; i++) {
        total += expenditures[i];
    }
    return total;
}

void displayBudgetReport(void)
{
    double totalAllocated = getTotalAllocated();
    double totalSpent = getTotalExpenditure();

    printf("\n===== BUDGET REPORT =====\n");

    if (departmentCount == 0) {
        printf("No department budgets have been entered yet.\n");
        return;
    }

    printf("Departments: %d\n", departmentCount);
    printf("Total Allocated Budget: N$%.2f\n", totalAllocated);
    printf("Total Expenditure: N$%.2f\n", totalSpent);
    printf("Total Remaining Budget: N$%.2f\n",
           calculateRemaining(totalAllocated, totalSpent));

    displayOverBudgetDepartments();
}

/* ================================================================
 *  MENU
 * ================================================================ */

static void displayBudgetMenu(void)
{
    printf("\n========================================\n");
    printf("          BUDGET MANAGEMENT\n");
    printf("========================================\n");
    printf("1. Add department budget\n");
    printf("2. Record expenditure\n");
    printf("3. Display all budgets\n");
    printf("4. Search for a department\n");
    printf("5. Show departments over budget\n");
    printf("6. Back to main menu\n");
}

void budgetMenu(void)
{
    int choice = 0;

    do {
        displayBudgetMenu();

        if (!readMenuChoice(1, 6, &choice)) {
            return;                 /* input ended */
        }

        switch (choice) {
            case 1: addDepartmentBudget();          break;
            case 2: recordExpenditure();            break;
            case 3: displayBudgets();               break;
            case 4: searchDepartment();             break;
            case 5: displayOverBudgetDepartments(); break;
            case 6: printf("Returning to main menu...\n"); break;
        }
    } while (choice != 6);
}
