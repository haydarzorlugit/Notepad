#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "password.h"

int checkPassword(void)
{
    FILE *fp = fopen(PASSWORD_FILE, "r");
    if(fp == NULL)
    {
        printf("ERROR: %s file not found\n", PASSWORD_FILE);
        return 0;
    }

    char realPassword[50];
    fgets(realPassword, sizeof(realPassword), fp);
    realPassword[strcspn(realPassword, "\n")] = '\0';
    fclose(fp);

    char input[50];
    int attempts = 0;

    while (attempts < MAX_ATTEMPS)
    {
        printf("Enter password (%d/%d): ", attempts + 1, MAX_ATTEMPS); // Enter password (1/3);
        scanf("%s", input);

        if(strcmp(input, realPassword) == 0)
        {
            printf("Login successful... Welcome\n\n");
            return 1;
        }
        else
        {
            printf("Wrong password %d chances left.\n", MAX_ATTEMPS - attempts - 1);
            attempts++;
        }
    }


    printf("3 wrong entries were made. The program is terminating...\n");
    return 0;
}

void changePassword()
{
    FILE *fp = fopen(PASSWORD_FILE, "r");
    if(fp == NULL)
    {
        printf("Password file could not be opened\n");
        return;
    }

    char currentPassword[50];
    fgets(currentPassword, sizeof(currentPassword), fp);
    currentPassword[strcspn(currentPassword, "\n")] = '\0'; // newline sil
    fclose(fp);

    char input[50];
    printf("Enter current password: ");
    scanf("%s", input);

    if(strcmp(input, currentPassword) != 0)
    {
        printf("Incorrect password. Password could not be changed\n");
        return;
    }

    char newPassword[50];
    printf("Enter new password:");
    scanf("%s", newPassword);

    fp = fopen(PASSWORD_FILE, "w");
    if(fp == NULL)
    {
        printf("New password could not be written\n");
        return;
    }

    fprintf(fp, "%s\n", newPassword);
    fclose(fp);

    printf("Password has been changed successfully\n");
}