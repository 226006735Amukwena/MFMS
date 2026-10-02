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

void AddEmployee(void)
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
        printf("Employee with ID %d already exists.\n", id);
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

void displayEmployees(void)
{
    int i;

    printf("\n--- EMPLOYEE LIST ---\n");
    if (empCount == 0) {
        printf("No employees registered.\n");
        return;
    }

    printf("%-6s %-30s %-20s %-20s %-10s %-10s %-10s %-10s %-10s\n",
           "ID", "Name", "Department", "Position", "Basic", "Housing", "Transport", "Other", "Gross");
    printf("------------------------------------------------------------------------------------------------------\n");       
    for (i = 0; i < empCount; i++) {
        double grossSalary = empBasic[i] + empHousing[i] + empTransport[i] + empOther[i];
        printf("%-6d %-30.30s %-20.20s %-20.20s %10.2f %10.2f %10.2f %10.2f %10.2f\n",
               empId[i], empName[i], empDept[i], empPosition[i],
               empBasic[i], empHousing[i], empTransport[i], empOther[i], grossSalary);
    }
    printf("\nTotal employees: %d\n", empCount);
}

void employeeMenu(void)
{
    int choice;

    do {
        printf("\n--- EMPLOYEE MANAGEMENT ---\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Return to Main Menu\n");
        choice = readInt("Enter your choice: ", 1, 3);

        switch (choice) {
            case 1:
                AddEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                printf("Returning to main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}