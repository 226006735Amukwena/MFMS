#ifndef REPORTS_H
#define REPORTS_H

#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

/* Reports menu: lets the user pick which report to view.
   Called from main() when the user chooses "5. Reports". */
void displayReports(const Employee employees[], int employeeCount,
                    const Budget budgets[], int budgetCount,
                    const Supplier suppliers[], int supplierCount,
                    const Asset assets[], int assetCount);

/* Individual reports (can also be called directly) */
double calculateGross(Employee e);
void employeeReport(const Employee employees[], int count);
void budgetReport(const Budget budgets[], int count);
void supplierReport(const Supplier suppliers[], int count);
void assetReport(const Asset assets[], int count);

#endif
