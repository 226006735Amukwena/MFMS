/*
 * budget.h
 * Budget Management module - Municipal Financial Management System (MFMS)
 * PAP521S - Project A
 *
 * Public interface of the budget module. Budget data is stored in arrays
 * inside budget.c, so other modules (e.g. reports.c) access it only
 * through the functions declared here.
 */

#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 20   /* maximum number of departments stored   */
#define MAX_DEPT_NAME   50   /* size of a department name (incl. '\0') */

/* ---------- Menu ---------- */

/* Shows the Budget Management sub-menu and runs it until the user
   chooses to go back to the main menu. Call this from main.c. */
void budgetMenu(void);

/* ---------- Data entry ---------- */

/* Adds a department with its allocated budget and initial expenditure.
   Returns 1 if the department was added, 0 otherwise. */
int addDepartmentBudget(void);

/* Adds an expenditure amount to an existing department. */
void recordExpenditure(void);

/* ---------- Calculations ---------- */

/* Returns the remaining budget (allocated - expenditure). */
double calculateRemaining(double allocated, double expenditure);

/* Returns 1 if expenditure is within the allocated budget, 0 if over. */
int isWithinBudget(double allocated, double expenditure);

/* Searches for a department by name (exact match).
   Returns its index, or -1 if it is not found. */
int findDepartment(const char *name);

/* ---------- Display ---------- */

/* Displays the budget details of every department. */
void displayBudgets(void);

/* Asks for a department name and displays its budget details. */
void searchDepartment(void);

/* Displays all departments that exceeded their allocated budget.
   Returns how many departments are over budget. */
int displayOverBudgetDepartments(void);

/* ---------- Support for the Reports module ---------- */

/* Prints the full Budget Report (totals + departments over budget). */
void displayBudgetReport(void);

int    getDepartmentCount(void);
double getTotalAllocated(void);
double getTotalExpenditure(void);

#endif /* BUDGET_H */
