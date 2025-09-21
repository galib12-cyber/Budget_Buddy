///////////////////////////////////////////////////// BUDGET BUDDY ////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>

#define max_user 100
#define bank_vault 100

typedef struct // typedef means we don't have to use struct USER again and again. we can just write USER.
{
    char username[max_user];
    char password[max_user];
} USER; // we define the user structure.

typedef struct // typedef means we don't have to use struct Wallet again and again. we can just write WALLET.
{
    double income[bank_vault];
    double expense[bank_vault];
} WALLET; // we define the wallet structure.

////////////////////////////////////////////// GLOBAL VARIABLE //////////////////////////////////////////////////////////////////////////////////////////////////////////////

// USER current_user;   // current user has also used the USER STRUCTURE.
USER user[max_user]; // We need to hold the users in an array. so i took the user array. and max_user is a macro.
                     // So that i dont need to change the number again and again and i can just change it in the macro.

int total_user = 0; // Used a flag to count all the total number of users.

int option, i, j, num;
double Balance;
WALLET wallet;
USER new_user;

FILE *file1; // took file1 as global
FILE *file2; // took file2 as global
FILE *file3; // took file3 as global
FILE *file4; // took file4 as global

/////////////////////////////////////////////// SAVE USER INFO /////////////////////////////////////////////////////////////////////////////////////////////////
void save_user()
{
    file4 = fopen("User_Info.txt", "a");
    fprintf(file4, "%s\n", new_user.username);
    fprintf(file4, "%s\n", new_user.password);
    fclose(file4);
}

//////////////////////////////////// READ BALANCE /////////////////////////////////////////////////////////////////////////////////////////////
void read_Balance()
{
    double temp_balance = 0;
    file3 = fopen("Balance_Sheet.txt", "a+");     // append+ mode means  it will read the file and then append(add).
    rewind(file3);                                // rewind moves to the start of balance file to read.
    if (fscanf(file3, "%lf", &temp_balance) == 1) // if there is any value in the balance sheet then we chanage it to zero.
    {
        Balance = temp_balance; // temp_balance is initialized to zero.
    }
    else
    {
        Balance = 0; // if the file is empty then also we make it zero.
    }
    fclose(file3);
}

//////////////////////////////////// WRITE BALANCE /////////////////////////////////////////////////////////////////////////////////////////////
void write_Balance()
{
    file3 = fopen("Balance_Sheet.txt", "w"); // we still use write mode to update the balance.
    fprintf(file3, "%.2lf", Balance);
    fclose(file3);
}

//////////////////////////////////// ADD INCOME /////////////////////////////////////////////////////////////////////////////////////////////////
void add_income()
{
    read_Balance();

    for (i = 1; i <= num; i++)
    {
        printf("Deposit %d(in Taka): ", i);
        scanf("%lf", &wallet.income[i]);

        Balance += wallet.income[i];

        fprintf(file1, "%.2lf\n", wallet.income[i]);
    }

    write_Balance();
}

//////////////////////////////////// ADD EXPENSE /////////////////////////////////////////////////////////////////////////////////////////////////
void add_expense()
{
    read_Balance();

    for (i = 1; i <= num; i++)
    {
        printf("Transaction %d(in Taka): ", i);
        scanf("%lf", &wallet.expense[i]);

        Balance -= wallet.expense[i];

        fprintf(file2, "%.2lf\n", wallet.expense[i]);
    }
    write_Balance();
}

//////////////////////////////////// USER INTERFACE //////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    printf("╔══════════════════════════════════╗\n");
    printf("║     Welcome to BUDGET BUDDY      ║\n");
    printf("║ Your personal finance companion! ║\n");
    printf("╚══════════════════════════════════╝\n");
    printf("\n");
    printf("╔══════════════════════════════════╗\n");
    printf("║∘₊✧──────✧₊ Home   Menu ₊✧─────✧₊∘║\n");
    printf("║                                  ║\n");
    printf("║ Summary Cards:                   ║\n");
    printf("║                                  ║\n");
    printf("║ 1. Register User                 ║\n");
    printf("║ 2. Login User                    ║\n");
    printf("║ 3. Add Income                    ║\n");
    printf("║ 4. Add Expenses                  ║\n");
    printf("║ 5. Net Worth                     ║\n");
    printf("╚══════════════════════════════════╝\n");
    printf("\n");
    printf("Pick an option (1 - 4): ");
    scanf("%d", &option);

    /////////////////////////////////////////////// Register User //////////////////////////////////////////////////////////////////////////////////////////////////
    if (option == 1)
    {
        if (total_user >= max_user)
        {
            printf("Maximum user limit reached!\n");
            return 0;
        }
        int i;
        printf("ENTER YOUR USERNAME: ");
        scanf("%s", new_user.username);
        for (i = 0; i < total_user; i++)
        {
            if (strcmp(user[i].username, new_user.username) == 0)
            {
                printf("User Already Exists!\n");
                return 0;
            }
        }
        printf("ENTER YOUR PASSWORD: ");
        scanf("%s", new_user.password);
        user[total_user++] = new_user;
        printf("USER REGISTERED SUCCESSFULLY!\n");
        save_user();
    }
    //////////////////////////////////////////////////////// LOGIN /////////////////////////////////////////////////////////////////////////////////////////////////////
    if (option == 2)
    {
        char entered_username[max_user];
        char entered_password[max_user];

        printf("Enter Username: ");
        scanf("%s", entered_username);

        printf("Enter Password: ");
        scanf("%s", entered_password);

        int login_success = 0;
        for (i = 0; i < total_user; i++)
        {
            if (strcmp(user[i].username, entered_username) == 0 &&
                strcmp(user[i].password, entered_password) == 0)
            {
                printf("Login Successful!\n");
                login_success = 1;
            }
        }
    }
        /////////////////////////////////////////// ADD INCOME ////////////////////////////////////////////////////////////////////////////////////////////////////
        if (option == 3)
        {
            printf("How many deposits do you want to make: ");
            scanf("%d", &num);
            printf("\n");

            file1 = fopen("Income_Sheet.txt", "a"); // Opened the file at append mode.

            add_income();
            fclose(file1);
            printf("\n");
            printf("Your Deposit Has Been Recorded!");
            printf("\n");
            printf("After Deposit Your Balance : ");

            file3 = fopen("Balance.txt", "r");
            fscanf(file3, "%lf\n", &Balance);
            fclose(file3);
            printf("%.2lf Taka\n", Balance);
            printf("\n");
        }

        ////////////////////////////////////////////// ADD EXPENSE ////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (option == 4)
        {
            printf("How many transactions do you want to record: ");
            scanf("%d", &num);
            printf("\n");

            file2 = fopen("Expense_Sheet.txt", "a");

            add_expense();
            fclose(file2);
            printf("\n");
            printf("Your Transaction Has Been Recorded!");
            printf("\n");
            printf("After Transaction Your Balance : ");

            file3 = fopen("Balance.txt", "r");
            fscanf(file3, "%lf\n", &Balance);
            fclose(file3);
            printf("%.2lf Taka\n", Balance);
            printf("\n");
        }

        ///////////////////////////////////////////// NET WORTH /////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (option == 5)
        {
            printf("\n");
            read_Balance();
            printf("NET WORTH: %.2lfTaka\n", Balance);
        }

        return 0;
    }
