#include <stdio.h>
#include <string.h>
#include "reports.h"

double calculateGross(Employee e)
{
    return e.basicSalary + e.housingAllowance + e.transportAllowance;
}

void employeeReport(const Employee employees[], int count)
{
    int i;
    double total = 0;
    double highest, lowest, salary;
    int highIndex = 0, lowIndex = 0;

    printf("\n===== EMPLOYEE REPORT =====\n");

    if (count == 0) {
        printf("No employees yet.\n");
        return;
    }

    highest = calculateGross(employees[0]);
    lowest = calculateGross(employees[0]);

    for (i = 0; i < count; i++) {
        salary = calculateGross(employees[i]);
        total = total + salary;

        if (salary > highest) {
            highest = salary;
            highIndex = i;
        }
        if (salary < lowest) {
            lowest = salary;
            lowIndex = i;
        }
    }

    printf("Total Employees: %d\n", count);
    printf("Average Salary: N$%.2f\n", total / count);
    printf("Highest Salary: N$%.2f (%s)\n", highest, employees[highIndex].name);
    printf("Lowest Salary: N$%.2f (%s)\n", lowest, employees[lowIndex].name);
}

void budgetReport(const Budget budgets[], int count)
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

void supplierReport(const Supplier suppliers[], int count)
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

void assetReport(const Asset assets[], int count)
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
        printf("Type: %s\n", assets[i].type);
        printf("Value: N$%.2f\n", assets[i].value);
        printf("Department: %s\n", assets[i].department);
        printf("Condition: %s\n", assets[i].condition);
        totalValue = totalValue + assets[i].value;
    }

    printf("\nTotal Assets: %d\n", count);
    printf("Total Value: N$%.2f\n", totalValue);
}

void displayReports(const Employee employees[], int employeeCount,
                    const Budget budgets[], int budgetCount,
                    const Supplier suppliers[], int supplierCount,
                    const Asset assets[], int assetCount)
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
                employeeReport(employees, employeeCount);
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
