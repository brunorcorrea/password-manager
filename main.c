#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define LEN 1001

FILE *file;

void openPasswordFile(char *openingMode)
{
    file = fopen("password.txt", openingMode);

    if (file == NULL)
    {
        file = fopen("password.txt", "w+");
        if(file == NULL)
        {
            printf("Error opening file!");
            exit(1);
        }
    }
}

FILE *openAuxFile()
{
    FILE *auxFile = fopen("aux.txt", "w+");

    if (auxFile == NULL)
    {
        printf("Error opening file!");
        exit(1);
    }

    return auxFile;
}

void deleteFile(char *fileName)
{
    if (remove(fileName) != 0)
    {
        printf("The file was not deleted.\n\n");
    }
}

void renameFile(char *oldName, char *newName)
{
    int result = rename(oldName, newName);
    if (result != 0)
    {
        printf("The file is renamed successfully.\n\n");
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
    openPasswordFile("a");

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
    printf("Password saved!\n\n");
}

void generatePassword()
{
    openPasswordFile("a");

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

void saveNewPassword()
{
    char password[100], c;
    clearArray(password, 100);

    printf("Enter password: ");
    scanf("%s", password);

    savePassword(password);
}

void deletePassword()
{
    openPasswordFile("r+");
    FILE *aux = openAuxFile();
    int passwordCounter = 0, passwordFound = 0;

    char location[LEN], password[LEN], splittedString[LEN];
    clearArray(location, LEN);
    printf("Type location of password to delete: \n");
    scanf("%s", location);

    while (fgets(password, LEN, file) != NULL)
    {
        strcpy(splittedString, password);
        char *token = strtok(splittedString, ":");
        while (token != NULL)
            token = strtok(NULL, ":");

        if (strcmp(splittedString, location))
        {
            fputs(password, aux);
            passwordFound++;
        }
        passwordCounter++;
    }

    if (passwordCounter == passwordFound)
    {
        printf("\nPassword not found!\n\n");
    }

    fclose(file);
    deleteFile("password.txt");
    renameFile("aux.txt", "password.txt");
    fclose(aux);
}

void editPassword()
{
    openPasswordFile("r+");
    FILE *aux = openAuxFile();

    int passwordCounter = 0, passwordFound = 0;
    char location[LEN], password[LEN], splittedString[LEN], newPassword[100], data[255];
    clearArray(location, LEN);
    clearArray(data, LEN);
    printf("Type location of password to edit: \n");
    scanf("%s", location);

    while (fgets(password, LEN, file) != NULL)
    {
        strcpy(splittedString, password);
        char *token = strtok(splittedString, ":");
        while (token != NULL)
            token = strtok(NULL, ":");

        if (!strcmp(splittedString, location))
        {
            printf("Enter new password: \n");
            scanf("%s", newPassword);
            strcat(data, location);
            strcat(data, ":");
            strcat(data, newPassword);
            strcat(data, "\n");

            fputs(data, aux);
        }
        else
        {
            passwordFound++;
            fputs(password, aux);
        }

        passwordCounter++;
    }

    if (passwordCounter == passwordFound)
    {
        printf("\nPassword not found!\n\n");
    }

    fclose(file);
    deleteFile("password.txt");
    renameFile("aux.txt", "password.txt");
    fclose(aux);
}

void listPasswords()
{
    openPasswordFile("r");

    char password[LEN];
    clearArray(password, LEN);

    printf("\n--------- PASSWORDS ---------\n");
    while (fgets(password, LEN, file) != NULL)
    {
        printf("%s", password);
    }
    printf("-----------------------------\n\n");

    fclose(file);
}

void viewPassword()
{
    openPasswordFile("r");

    int passwordFound = 0;
    char location[LEN], password[LEN], splittedString[LEN];
    clearArray(location, LEN);
    printf("Type location of password to view: \n");
    scanf("%s", location);

    while (fgets(password, LEN, file) != NULL)
    {
        strcpy(splittedString, password);
        char *token = strtok(splittedString, ":");
        while (token != NULL)
            token = strtok(NULL, ":");

        if (!strcmp(splittedString, location))
        {
            printf("\n--------- PASSWORD ---------\n");
            printf("%s", password);
            printf("----------------------------\n\n");
            passwordFound++;
        }
    }

    if (!passwordFound)
    {
        printf("\nPassword not found!\n\n");
    }
}

void menu()
{
    int choice;
    do
    {
        printf("Welcome to PASSWORD MANAGER\n");
        printf("1. Save Password\n");
        printf("2. Delete Password\n");
        printf("3. Edit Password\n");
        printf("4. List Passwords\n");
        printf("5. View Password\n");
        printf("6. Generate Password\n");
        printf("7. Clear Screen\n");
        printf("0. Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            saveNewPassword();
            break;
        case 2:
            deletePassword();
            break;
        case 3:
            editPassword();
            break;
        case 4:
            listPasswords();
            break;
        case 5:
            viewPassword();
            break;
        case 6:
            generatePassword();
            break;
        case 7:
            system("clear");
            break;
        case 0:
            return;
        default:
            printf("\nInvalid choice\n\n");
            break;
        }
    } while (choice != 0);
}

int main(void)
{
    system("clear");
    menu();

    return (0);
}