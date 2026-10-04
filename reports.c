#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "reports.h"
#include "config.h"
#include "utils.h"
#include "suppliers.h"
#include "asset.h"
#include "budget.h"

#ifndef MFMS_EMPLOYEE_DEFINED
#define MFMS_EMPLOYEE_DEFINED
struct Employee {
    char name[100];
    double basicSalary;
    double housingAllowance;
    double transportAllowance;
};
#endif

#ifndef MFMS_BUDGET_DEFINED
#define MFMS_BUDGET_DEFINED
struct Budget {
    char department[100];
    double allocated;
    double expenditure;
};
#endif

#ifndef MFMS_SUPPLIER_DEFINED
#define MFMS_SUPPLIER_DEFINED
struct Supplier {
    char id[50];
    char name[100];
    char email[100];
    char phone[50];
    char town[100];
};
#endif

#ifndef MFMS_ASSET_DEFINED
#define MFMS_ASSET_DEFINED
struct Asset {
    char id[50];
    char name[100];
    int type;
    double value;
    char department[100];
    char condition[100];
};
#endif

double calculateGross(const struct Employee e)
{
    return e.basicSalary + e.housingAllowance + e.transportAllowance;
}

void employeeReport(void)
{
    printf("\n===== EMPLOYEE REPORT =====\n");
    printf("Employee data is unavailable.\n");
}

void budgetReport(const struct Budget budgets[], int count)
{
    int i;
    int exceeded = 0;
    double totalBudget = 0;
    double totalSpent = 0;

    printf("\n===== BUDGET REPORT =====\n");

    if (count == 0) {
        printf("No budgets yet.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        totalBudget = totalBudget + budgets[i].allocated;
        totalSpent = totalSpent + budgets[i].expenditure;
    }

    printf("Total Allocated Budget: N$%.2f\n", totalBudget);
    printf("Total Expenditure: N$%.2f\n", totalSpent);
    printf("Remaining Budget: N$%.2f\n", totalBudget - totalSpent);

    printf("\nDepartments exceeding budget:\n");
    for (i = 0; i < count; i++) {
        if (budgets[i].expenditure > budgets[i].allocated) {
            printf("- %s\n", budgets[i].department);
            exceeded++;
        }
    }

    if (exceeded == 0) {
        printf("None\n");
    }
}

void supplierReport(const struct Supplier suppliers[], int count)
{
    int i;

    printf("\n===== SUPPLIER REPORT =====\n");

    if (count == 0) {
        printf("No suppliers yet.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        printf("\nSupplier %d\n", i + 1);
        printf("ID: %s\n", suppliers[i].id);
        printf("Name: %s\n", suppliers[i].name);
        printf("Email: %s\n", suppliers[i].email);
        printf("Phone: %s\n", suppliers[i].phone);
        printf("Town: %s\n", suppliers[i].town);
    }

    printf("\nTotal Suppliers: %d\n", count);
}

void assetReport(const struct Asset assets[], int count)
{
    int i;
    double totalValue = 0;

    printf("\n===== ASSET REPORT =====\n");

    if (count == 0) {
        printf("No assets yet.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        printf("\nAsset %d\n", i + 1);
        printf("ID: %s\n", assets[i].id);
        printf("Name: %s\n", assets[i].name);
        printf("Type: %d\n", assets[i].type);
        printf("Value: N$%.2f\n", assets[i].value);
        printf("Department: %s\n", assets[i].department);
        printf("Condition: %s\n", assets[i].condition);
        totalValue += assets[i].value;
    }

    printf("\nTotal Assets: %d\n", count);
    printf("Total Value: N$%.2f\n", totalValue);
}

void displayReports(const struct Employee employees[], int employeeCount,
                    const struct Budget budgets[], int budgetCount,
                    const struct Supplier suppliers[], int supplierCount,
                    const struct Asset assets[], int assetCount)
{
    int choice;

    do {
        printf("\n===== REPORTS =====\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            choice = 0;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                employeeReport();
                break;
            case 2:
                budgetReport(budgets, budgetCount);
                break;
            case 3:
                supplierReport(suppliers, supplierCount);
                break;
            case 4:
                assetReport(assets, assetCount);
                break;
            case 5:
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    } while (choice != 5);
}

void assetReport(void)
{
}
