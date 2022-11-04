#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    
FILE *file;

void openPasswordFile() {
    file = fopen("password.txt", "a");

    if (file == NULL) {
        printf("Error opening file!");
        exit(1);
    }
}

void clearArray(char *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = '\0';
    }
}

int savePassword() {

    openPasswordFile();

    char password[100], location[100], data[255], c;
    clearArray(password, 255);
    clearArray(location, 255);
    clearArray(data, 255);

    printf("Enter location of password: ");
    scanf("%s", location);

    printf("Enter password: ");
    scanf("%s", password);

    strcat(data, location);
    strcat(data, ":");
    strcat(data, password);
    strcat(data, "\n");

    fprintf(file, "%s", data);
    printf("\n%s", data);

    fclose(file);
    return 0;
}

void menu() {
    int choice;
    printf("Welcome to PASSWORD MANAGER\n");
    printf("1. Save Password\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            savePassword();
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
}

int main(void)
{
    menu();

    return (0);
}