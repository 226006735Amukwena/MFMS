#include <stdio.h>

void calculateBudget()
{
    char deptName[30];
    float allocated;
    float expenditure;
    float remaining;

    printf("Enter department name: ");
    scanf("%s", deptName);

    printf("Enter allocated budget: ");
    scanf("%f", &allocated);

    printf("Enter expenditure: ");
    scanf("%f", &expenditure);

    if (allocated < 0 || expenditure < 0) {
        printf("Error: Values cannot be negative.\n");
    } else {
        remaining = allocated - expenditure;

        printf("\nDepartment: %s\n", deptName);
        printf("Allocated Budget: %.2f\n", allocated);
        printf("Expenditure: %.2f\n", expenditure);
        printf("Remaining Budget: %.2f\n", remaining);

        if (expenditure > allocated) {
            printf("Status: OVER BUDGET\n");
        } else {
            printf("Status: WITHIN BUDGET\n");
        }
    }
}

int main()
{
    calculateBudget();
    return 0;
}