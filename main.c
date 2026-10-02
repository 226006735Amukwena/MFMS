#include <stdio.h>
#include <stdlib.h>

void displayMenu(void);
int readInt(const char *prompt, int min, int max);

int main()
{
    int choice;

    do {
        displayMenu();
        choice = readInt("Enter your choice: ", 1, 6);

        switch (choice) {
            case 1:
                printf("Employee Management.\n");
                break;
            case 2:
                printf("Budget Management.\n");
                break;
            case 3:
                printf("Supplier Management.\n");
                break;
            case 4:
                printf("Asset Management.\n");
                break;
            case 5:
                printf("Reports.\n");
                break;
            case 6: 
                printf("Goodbye!\n");   
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void displayMenu() {
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

int readInt(const char *prompt, int min, int max) {
    int value, c;

    for (;;) {
        printf("%s", prompt);
        if (scanf("%d", &value) != 1) {
            if (feof(stdin)) {
                exit(0);
            }
            printf("Invalid input. Please enter an integer.\n");
        } else if (value < min || value > max) {
            printf("Input out of range. Please enter a value between %d and %d.\n", min, max);
        } else {
            while ((c = getchar()) != '\n' && c != EOF) { }
            return value;
        }
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
}
