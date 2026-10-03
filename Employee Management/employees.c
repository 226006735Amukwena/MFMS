#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "utils.h"

int   empId[MAX_EMPLOYEES];
char  empName[MAX_EMPLOYEES][NAME_LEN];
char  empDept[MAX_EMPLOYEES][DEPT_LEN];
char  empPosition[MAX_EMPLOYEES][POSITION_LEN];
double empBasic[MAX_EMPLOYEES];
double empHousing[MAX_EMPLOYEES];
double empTransport[MAX_EMPLOYEES];
double empOther[MAX_EMPLOYEES];
int  empCount = 0;

static int findEmployeeByID(int id) {
    int i;
    for (i = 0; i < empCount; i++) {
        if (empId[i] == id) {
            return i;
        }
    }
    return -1;
}

void addEmployee(void)
{
    int id, i;
    char first[25];
    char surname[30];

    printf("\n--- ADD EMPLOYEE ---\n");
    if (empCount >= MAX_EMPLOYEES) {
        printf("Employee list is full (%d employees).\n", MAX_EMPLOYEES);
        return;
    }

    for (;;) {
        id = readInt("Employee ID (1-99999): ", 1, 99999);
        if (findEmployeeByID(id) == -1) {
            break;
        }
        puts("An employee with this ID already exists.");
    }

    i = empCount;
    empId[i] = id;

    readNonEmpty("First name: ", first, sizeof(first));
    readNonEmpty("Surname: ", surname, sizeof(surname));
    strcpy(empName[i], first);
    strcat(empName[i], " ");
    strcat(empName[i], surname);

    readNonEmpty("Department: ", empDept[i], DEPT_LEN);
    readNonEmpty("Position/Job title: ", empPosition[i], POSITION_LEN);

    empBasic[i]     = readDouble("Basic salary (N$ per month): ", 1.0, 999999.99);
    empHousing[i]   = readDouble("Housing allowance (N$): ", 0.0, 999999.99);
    empTransport[i] = readDouble("Transport allowance (N$): ", 0.0, 999999.99);
    empOther[i]     = readDouble("Other allowances (N$, 0 if none): ", 0.0, 999999.99);

    empCount++;
    printf("\nEmployee '%s' added (%d registered).\n", empName[i], empCount);
}

static void printEmployeeHeader(void)
{
    printf("\n%-6s %-22s %-14s %-14s %11s\n", "ID", "Name", "Department", "Position", "Gross (N$)");
    printf("------------------------------------------------------------------------\n");
}

static void printEmployeeRow(int i)
{
    double gross = calculateGross(empBasic[i], empHousing[i], empTransport[i], empOther[i]);
    printf("%-6d %-22.22s %-14.14s %-14.14s %11.2f\n",
           empId[i], empName[i], empDept[i], empPosition[i], gross);
}

void displayEmployees(void)
{
    int i;

    printf("\n--- EMPLOYEE LIST ---\n");
    if (empCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }

    printEmployeeHeader();
    for (i = 0; i < empCount; i++) {
        printEmployeeRow(i);
    }
    printf("\nTotal employees: %d\n", empCount);
}

void searchEmployee(void)
{
    int choice, i, id;
    int found = 0;
    char term[NAME_LEN];

    printf("\n--- SEARCH EMPLOYEE ---\n");
    if (empCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }

    printf("Search by:\n  1. Employee ID\n  2. Name (full or partial)\n  3. Department\n");
    choice = readInt("Enter your choice (1-3): ", 1, 3);

    switch (choice) {
    case 1:
        id = readInt("Enter employee ID: ", 1, 99999);
        i = findEmployeeByID(id);
        if (i != -1) {
            printEmployeeHeader();
            printEmployeeRow(i);
            found = 1;
        }
        break;
    case 2:
        readNonEmpty("Enter name or part of name: ", term, sizeof term);
        for (i = 0; i < empCount; i++) {
            if (containsIgnoreCase(empName[i], term)) {
                if (found == 0) {
                    printEmployeeHeader();
                }
                printEmployeeRow(i);
                found++;
            }
        }
        break;
    case 3:
        readNonEmpty("Enter department: ", term, sizeof term);
        for (i = 0; i < empCount; i++) {
            if (equalsIgnoreCase(empDept[i], term)) {
                if (found == 0) {
                    printEmployeeHeader();
                }
                printEmployeeRow(i);
                found++;
            }
        }
        break;
    }

    if (found == 0) {
        printf("\nNo matching employee found.\n");
    } else {
        printf("\n%d employee(s) found.\n", found);
    }
}

/* ---------- salary calculations: values go in, one result comes back ---------- */

double calculateGross(double basic, double housing, double transport, double other)
{
    return basic + housing + transport + other;
}

/* Pension contribution: 5% of the basic salary. */
double calculatePension(double basic)
{
    return basic * 0.05;
}

/* Simplified monthly tax (illustration only, NOT the official PAYE table). */
double calculateTax(double taxable)
{
    double rate;

    if (taxable <= 4000.0) {
        rate = 0.0;
    } else if (taxable <= 8000.0) {
        rate = 0.10;
    } else if (taxable <= 15000.0) {
        rate = 0.18;
    } else if (taxable <= 25000.0) {
        rate = 0.25;
    } else {
        rate = 0.32;
    }
    return taxable * rate;
}

double calculateNet(double gross, double pension, double tax)
{
    return gross - pension - tax;
}

void displayPayslip(int i)
{
    double gross   = calculateGross(empBasic[i], empHousing[i], empTransport[i], empOther[i]);
    double pension = calculatePension(empBasic[i]);
    double tax     = calculateTax(gross - pension);
    double net     = calculateNet(gross, pension, tax);

    printf("\n--- Salary information: %s (ID %d) ---\n", empName[i], empId[i]);
    printf("Department        : %s\n", empDept[i]);
    printf("Position          : %s\n", empPosition[i]);
    printf("Basic salary      : N$ %10.2f\n", empBasic[i]);
    printf("Housing allowance : N$ %10.2f\n", empHousing[i]);
    printf("Transport allow.  : N$ %10.2f\n", empTransport[i]);
    printf("Other allowances  : N$ %10.2f\n", empOther[i]);
    printf("Gross salary      : N$ %10.2f\n", gross);
    printf("Pension (5%%)      : N$ %10.2f\n", pension);
    printf("Income tax        : N$ %10.2f\n", tax);
    printf("NET SALARY        : N$ %10.2f\n", net);
}

void calculateSalary(void)
{
    int id, i;

    printf("\n--- CALCULATE SALARY ---\n");
    if (empCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }
    id = readInt("Enter employee ID: ", 1, 99999);
    i = findEmployeeByID(id);
    if (i == -1) {
        printf("No employee with ID %d.\n", id);
        return;
    }
    displayPayslip(i);
}

void employeeMenu(void)
{
    int choice;

    do {
        printf("\n========== EMPLOYEE MANAGEMENT ==========");
        printf("\n1. Add employee\n2. Display employees\n3. Search employee\n");
        printf("4. Calculate salary\n5. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice) {
        case 1: addEmployee(); break;
        case 2: displayEmployees(); break;
        case 3: searchEmployee(); break;
        case 4: calculateSalary(); break;
        case 5: break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 5);
}

/* Stores one employee directly (used for sample data). */
static void storeEmployee(int id, const char *name, const char *dept,
                          const char *position, double basic, double housing,
                          double transport, double other)
{
    int i = empCount;

    empId[i] = id;
    strcpy(empName[i], name);
    strcpy(empDept[i], dept);
    strcpy(empPosition[i], position);
    empBasic[i] = basic;
    empHousing[i] = housing;
    empTransport[i] = transport;
    empOther[i] = other;
    empCount++;
}

void seedEmployees(void)
{
    storeEmployee(1001, "Anna Shikongo",    "Finance", "Accountant",   18000, 3000, 1500, 0);
    storeEmployee(1002, "Petrus Nghidinwa", "Finance", "Clerk",         9500, 1500,  800, 0);
    storeEmployee(1003, "Maria Amupolo",    "Health",  "Nurse",        14000, 2500, 1200, 500);
    storeEmployee(1004, "Johannes Kavari",  "Roads",   "Engineer",     32000, 5000, 2500, 0);
    storeEmployee(1005, "Selma Iipinge",    "Admin",   "Receptionist",  8500, 1200,  600, 0);
}