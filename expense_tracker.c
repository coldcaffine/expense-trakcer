
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPENSES 1000
#define FILE_NAME "expenses.txt"

typedef struct
{
    int id;
    char category[30];
    char description[100];
    double amount;
} Expense;

Expense expenses[MAX_EXPENSES];
int expenseCount = 0;

// Function to read a line of text
void readLine(char text[], int size)
{
    if (fgets(text, size, stdin) != NULL)
    {
        size_t len = strcspn(text, "\n");

        if (text[len] == '\n')
        {
            text[len] = '\0';
        }
        else
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
                /* Clear remaining input */
            }
        }
    }
    else
    {
        text[0] = '\0';
    }
}

// Function to read an integer safely
int readInt(void)
{
    char input[100];
    char *end;
    long value;

    while (1)
    {
        readLine(input, sizeof(input));
        value = strtol(input, &end, 10);

        while (isspace((unsigned char)*end))
        {
            end++;
        }

        if (end != input && *end == '\0' &&
            value >= -2147483647L - 1 &&
            value <= 2147483647L)
        {
            return (int)value;
        }

        printf("Invalid input! Enter an integer: ");
    }
}

// Function to read a positive amount
double readAmount(void)
{
    char input[100];
    char *end;
    double value;

    while (1)
    {
        readLine(input, sizeof(input));
        value = strtod(input, &end);

        while (isspace((unsigned char)*end))
        {
            end++;
        }

        if (end != input && *end == '\0' &&
            value > 0)
        {
            return value;
        }

        printf("Enter a valid positive amount: ");
    }
}

// Function to save expenses in a file
void saveExpenses(void)
{
    FILE *file = fopen(FILE_NAME, "w");

    if (file == NULL)
    {
        printf("Error opening file for saving!\n");
        return;
    }

    for (int i = 0; i < expenseCount; i++)
    {
        fprintf(file, "%d|%.2f|%s|%s\n",
                expenses[i].id,
                expenses[i].amount,
                expenses[i].category,
                expenses[i].description);
    }

    if (fclose(file) != 0)
    {
        printf("Error closing the file!\n");
    }
}

// Function to load expenses from a file
void loadExpenses(void)
{
    FILE *file = fopen(FILE_NAME, "r");
    char line[256];

    if (file == NULL)
    {
        return;
    }

    while (expenseCount < MAX_EXPENSES &&
           fgets(line, sizeof(line), file) != NULL)
    {

        Expense e;

        if (sscanf(line, "%d|%lf|%29[^|]|%99[^\n]",
                   &e.id,
                   &e.amount,
                   e.category,
                   e.description) == 4 &&
            e.id > 0 &&
            e.amount > 0)
        {

            expenses[expenseCount] = e;
            expenseCount++;
        }
    }

    fclose(file);
}

// Function to add an expense
void addExpense(void)
{
    if (expenseCount >= MAX_EXPENSES)
    {
        printf("Expense storage is full!\n");
        return;
    }

    Expense e;

    e.id = 1;

    for (int i = 0; i < expenseCount; i++)
    {
        if (expenses[i].id >= e.id)
        {
            e.id = expenses[i].id + 1;
        }
    }

    printf("\nEnter expense amount: ");
    e.amount = readAmount();

    printf("Enter category (Food/Travel/Study/Other): ");
    readLine(e.category, sizeof(e.category));

    printf("Enter description: ");
    readLine(e.description, sizeof(e.description));

    if (e.category[0] == '\0' ||
        e.description[0] == '\0')
    {
        printf("Category and description cannot be empty!\n");
        return;
    }

    // Replace the separator character
    for (int i = 0; e.category[i] != '\0'; i++)
    {
        if (e.category[i] == '|')
        {
            e.category[i] = '/';
        }
    }

    for (int i = 0; e.description[i] != '\0'; i++)
    {
        if (e.description[i] == '|')
        {
            e.description[i] = '/';
        }
    }

    expenses[expenseCount] = e;
    expenseCount++;

    saveExpenses();

    printf("\nExpense added successfully!\n");
}

// Function to display all expenses
void viewExpenses(void)
{
    if (expenseCount == 0)
    {
        printf("\nNo expenses recorded yet.\n");
        return;
    }

    printf("\n%-5s %-12s %-15s %s\n",
           "ID", "Amount", "Category", "Description");

    printf("--------------------------------------------------------\n");

    for (int i = 0; i < expenseCount; i++)
    {
        printf("%-5d %-12.2f %-15s %s\n",
               expenses[i].id,
               expenses[i].amount,
               expenses[i].category,
               expenses[i].description);
    }
}

// Function to calculate total expenses
void showTotal(void)
{
    double total = 0;

    for (int i = 0; i < expenseCount; i++)
    {
        total += expenses[i].amount;
    }

    printf("\nTotal expenses: %.2f\n", total);
}

// Function to search expenses by category
void searchCategory(void)
{
    char category[30];
    int found = 0;

    printf("\nEnter category to search: ");
    readLine(category, sizeof(category));

    for (int i = 0; i < expenseCount; i++)
    {
        if (strcmp(expenses[i].category, category) == 0)
        {
            printf("\nID: %d\n", expenses[i].id);
            printf("Amount: %.2f\n", expenses[i].amount);
            printf("Category: %s\n", expenses[i].category);
            printf("Description: %s\n", expenses[i].description);

            found = 1;
        }
    }

    if (!found)
    {
        printf("No expenses found in this category.\n");
    }
}

// Main function
int main(void)
{
    int choice;

    loadExpenses();

    printf("=================================\n");
    printf("     PERSONAL EXPENSE TRACKER\n");
    printf("=================================\n");

    do
    {
        printf("\n1. Add Expense\n");
        printf("2. View All Expenses\n");
        printf("3. Show Total Expenses\n");
        printf("4. Search by Category\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        choice = readInt();

        switch (choice)
        {
        case 1:
            addExpense();
            break;

        case 2:
            viewExpenses();
            break;

        case 3:
            showTotal();
            break;

        case 4:
            searchCategory();
            break;

        case 5:
            printf("\nThank you for using Expense Tracker!\n");
            break;

        default:
            printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}
