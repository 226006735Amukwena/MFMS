#ifndef REPORTS_H
#define REPORTS_H

struct Budget;
struct Employee;
struct Supplier;
struct Asset;

void displayReports(const struct Employee *employees, int employeeCount,
                    const struct Budget *budgets, int budgetCount,
                    const struct Supplier *suppliers, int supplierCount,
                    const struct Asset *assets, int assetCount);
void employeeReport(const struct Employee *employees, int count);
void budgetReport(const struct Budget *budgets, int count);
void supplierReport(const struct Supplier *suppliers, int count);
void assetReport(const struct Asset *assets, int count);

#endif