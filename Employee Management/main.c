#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void displayMenu(void);

int main(int argc, char *argv[])
{
    int choice;

    /* Run ./mfms --demo to start with sample data. */
    if (argc > 1 && strcmp(argv[1], "--demo") == 0) {
        int seedEmployees();
        printf("Demo data loaded.\n");
    }

    do {
        displayMenu();
        choice = readInt("Enter your choice: ", 1, 6);

        switch (choice) {
            case 1:
                printf("Employee Management.\n");
                break;
            case 2:
                printf("Budget Management.\n");
                break;
            case 3:
                printf("Supplier Management.\n");
                break;
            case 4:
                printf("Asset Management.\n");
                break;
            case 5:
                printf("Reports.\n");
                break;
            case 6:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);

    return 0;
}

void displayMenu(void)
{
    printf("\n========================================\n");
    printf("MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
}