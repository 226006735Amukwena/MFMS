#include <stdio.h>
#include <string.h>
#include "budget.h"

#define MAX_DEPT 20
#define NAME_SIZE 50
#ifndef NAME_LEN
#define NAME_LEN 60
#endif
#ifndef DEPT_LEN
#define DEPT_LEN 30
#endif

char names[MAX_DEPT][NAME_SIZE];
float allocated[MAX_DEPT];
float spent[MAX_DEPT];
int count = 0;

void clearBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

float getAmount(char prompt[])
{
    float value;
    int result;

    while (1) {
        printf("%s", prompt);
        result = scanf("%f", &value);
        clearBuffer();

        if (result != 1) {
            printf("Error: Please enter a valid number.\n");
        } else if (value < 0) {
            printf("Error: Values cannot be negative.\n");
        } else {
            return value;
        }
    }
}

void getName(char name[])
{
    while (1) {
        printf("Enter department name: ");
        fgets(name, NAME_SIZE, stdin);

        if (strchr(name, '\n') == NULL) {
            clearBuffer();
        }
        name[strcspn(name, "\n")] = '\0';

        if (strlen(name) == 0) {
            printf("Error: Name cannot be empty.\n");
        } else {
            return;
        }
    }
}

int findDepartment(char name[])
{
    int i;

    for (i = 0; i < count; i++) {
        if (strcmp(names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

float calculateRemaining(float allocatedBudget, float expenditure)
{
    return allocatedBudget - expenditure;
}

void printDepartment(int i)
{
    float remaining = calculateRemaining(allocated[i], spent[i]);

    printf("Department: %s\n", names[i]);
    printf("Allocated Budget: N$%.2f\n", allocated[i]);
    printf("Expenditure: N$%.2f\n", spent[i]);
    printf("Remaining Budget: N$%.2f\n", remaining);

    if (spent[i] > allocated[i]) {
        printf("Status: OVER BUDGET\n");
    } else {
        printf("Status: WITHIN BUDGET\n");
    }
}

void addDepartmentBudget(void)
{
    char name[NAME_SIZE];

    if (count >= MAX_DEPT) {
        printf("Error: Department list is full.\n");
        return;
    }

    getName(name);

    if (findDepartment(name) != -1) {
        printf("Error: This department already exists.\n");
        return;
    }

    strcpy(names[count], name);
    allocated[count] = getAmount("Enter allocated budget: ");
    spent[count] = getAmount("Enter expenditure: ");
    count++;

    printf("\nBudget saved.\n");
    printDepartment(count - 1);
}

void recordExpenditure(void)
{
    char name[NAME_SIZE];
    int index;
    float amount;

    if (count == 0) {
        printf("No departments have been added yet.\n");
        return;
    }

    getName(name);
    index = findDepartment(name);

    if (index == -1) {
        printf("Department not found.\n");
        return;
    }

    amount = getAmount("Enter expenditure to add: ");
    spent[index] = spent[index] + amount;

    printf("\nExpenditure updated.\n");
    printDepartment(index);
}

void displayBudgets(void)
{
    int i;

    if (count == 0) {
        printf("No departments have been added yet.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        printf("\n");
        printDepartment(i);
    }
}

void searchDepartment(void)
{
    char name[NAME_SIZE];
    int index;

    if (count == 0) {
        printf("No departments have been added yet.\n");
        return;
    }

    getName(name);
    index = findDepartment(name);

    if (index == -1) {
        printf("Department not found.\n");
    } else {
        printf("\n");
        printDepartment(index);
    }
}

void displayOverBudgetDepartments(void)
{
    int i;
    int found = 0;

    printf("\nDepartments over budget:\n");

    for (i = 0; i < count; i++) {
        if (spent[i] > allocated[i]) {
            printf("- %s (over by N$%.2f)\n", names[i], spent[i] - allocated[i]);
            found = 1;
        }
    }

    if (found == 0) {
        printf("None\n");
    }
}

void displayBudgetReport(void)
{
    int i;
    float totalAllocated = 0;
    float totalSpent = 0;

    printf("\n===== BUDGET REPORT =====\n");

    if (count == 0) {
        printf("No departments have been added yet.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        totalAllocated = totalAllocated + allocated[i];
        totalSpent = totalSpent + spent[i];
    }

    printf("Total Allocated Budget: N$%.2f\n", totalAllocated);
    printf("Total Expenditure: N$%.2f\n", totalSpent);
    printf("Remaining Budget: N$%.2f\n", calculateRemaining(totalAllocated, totalSpent));

    displayOverBudgetDepartments();
}

void budgetMenu(void)
{
    int choice;

    do {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Add department budget\n");
        printf("2. Record expenditure\n");
        printf("3. Display all budgets\n");
        printf("4. Search for a department\n");
        printf("5. Show departments over budget\n");
        printf("6. Back to main menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            choice = 0;
        }
        clearBuffer();

        switch (choice) {
            case 1: addDepartmentBudget(); break;
            case 2: recordExpenditure(); break;
            case 3: displayBudgets(); break;
            case 4: searchDepartment(); break;
            case 5: displayOverBudgetDepartments(); break;
            case 6: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice. Please enter 1 to 6.\n");
        }
    } while (choice != 6);
}
