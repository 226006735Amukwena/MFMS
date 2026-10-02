#ifndef EMPLOYEES_H
#define EMPLOYEES_H
#define MAX_EMPLOYEES 100
#define NAME_LEN      60
#define DEPT_LEN      30
#define POSITION_LEN  30

extern int empId[MAX_EMPLOYEES];
extern char empName[MAX_EMPLOYEES][NAME_LEN];
extern char empDept[MAX_EMPLOYEES][DEPT_LEN];
extern char empPosition[MAX_EMPLOYEES][POSITION_LEN];
extern double empBasic[MAX_EMPLOYEES];
extern double empHousing[MAX_EMPLOYEES];
extern double empTransport[MAX_EMPLOYEES];
extern int empCount;

void employeeMenu();
void addEmployee();
void displayEmployees();

void searchEmployee(void);
void calculateSalary(void);
void displayPayslip(int index);

double calculateGross(double basic, double housing, double transport, double other);
double calculatePension(double basic);
double calculateTax(double taxable);
double calculateNet(double gross, double pension, double tax);

#endif