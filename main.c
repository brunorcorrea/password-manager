#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define LEN 1001

FILE *file;

void openPasswordFileAppend()
{
    file = fopen("password.txt", "a");

    if (file == NULL)
    {
        printf("Error opening file!");
        exit(1);
    }
}

void openPasswordFileReadAndWrite()
{
    file = fopen("password.txt", "r+");

    if (file == NULL)
    {
        printf("Error opening file!");
        exit(1);
    }
}

void clearArray(char *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = '\0';
    }
}

void savePassword(char *password)
{
    openPasswordFileAppend();

    char data[255], location[100];
    clearArray(data, 255);
    clearArray(location, 100);

    printf("Enter location of password: ");
    scanf("%s", location);

    strcat(data, location);
    strcat(data, ":");
    strcat(data, password);
    strcat(data, "\n");

    fprintf(file, "%s", data);
    printf("\n%s", data);

    fclose(file);
}

void generatePassword()
{
    openPasswordFileAppend();

    char letters[] = "abcdefghijklmnopqrstuvwxyz";
    char capitalLetters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char numbers[] = "0123456789";
    char simbols[] = "?!@#$%%&/+-";
    char password[13];

    clearArray(password, 13);

    srand(time(NULL));

    for (int i = 0; i < 12; i++)
    {
        int random = rand() % 4;
        switch (random)
        {
        case 0:
            password[i] = letters[rand() % 26];
            break;
        case 1:
            password[i] = capitalLetters[rand() % 26];
            break;
        case 2:
            password[i] = numbers[rand() % 10];
            break;
        case 3:
            password[i] = simbols[rand() % 10];
            break;
        }
    }

    savePassword(password);
}

void createNewPassword()
{
    char password[100], c;
    clearArray(password, 100);

    printf("Enter password: ");
    scanf("%s", password);

    savePassword(password); // TODO show message confirming password saved
}

void deletePassword()
{
    openPasswordFileReadAndWrite();

    int line = 0;
    printf("Choose the line of your password to delete: \n");
    scanf("%d",&line);
    char password[LEN];
    unsigned int linha_atual = 1;

    while (fgets(password, LEN, file) != NULL)
    {
        if (linha_atual != line)
        {
            printf("Linha: %d, Senha: %s\n", line, password);
            fputs(password, file);
        }
        linha_atual++;
    }

    fclose(file);
}

void menu()
{
    int choice;
    printf("Welcome to PASSWORD MANAGER\n");
    printf("1. Save Password\n");
    printf("2. Delete Password\n");
    printf("6. Generate Password\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        createNewPassword();
        break;
    case 2:
        deletePassword();
        break;
    case 6:
        generatePassword();
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
    // TODO run menu again until user exits
}

int main(void)
{
    menu();

    return (0);
}