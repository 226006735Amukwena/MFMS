#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "asset.h"
#include "reports.h"

void displayMenu(void);
void employeeManagement(void);
void budgetManagement(void);
void supplierManagement(void);
void assetManagement(void);
void reportsManagement(void);
void exitProgram(void);

int main(void)
{
    int choice;

    do {
        displayMenu();
        choice = readInt("Enter your choice: ", 1, 6);

        switch (choice) {
            case 1:
                employeeManagement();
                break;
            case 2:
                budgetManagement();
                break;
            case 3:
                supplierManagement();
                break;
            case 4:
                assetManagement();
                break;
            case 5:
                reportsManagement();
                break;
            case 6:
                exitProgram();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
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