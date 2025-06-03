#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "notepad.h"

const char *categories[] = {"personal", "work", "school"};

void addNote(void)
{
    FILE *fp = fopen(FILENAME, "a"); // open the file as append mode / "r" --> read, "w" --> write, "a" --> append
    if(fp == NULL)
    {
        printf("Dosya acilamadi!\n");
        return;
    }


    time_t now;
    time(&now);
    struct tm *t = localtime(&now);

    const char *category;
    int selection;

    printf("Choose category:\n");
    for(int i = 0; i < CATEGORY_COUNT; i++)
    {
        printf("%d. %s\n", i + 1, categories[i]);
    }
    printf("Your choice:\n: ");
    scanf("%d", &selection);

    if(selection < 1 || selection > CATEGORY_COUNT)
    {
        printf("Invalid category selection\n\n");
        fclose(fp);
        return;
    }

    category = categories[selection - 1];

    char note[MAX_NOTE_LENGTH];
    getchar();
    printf("Enter your new note: ");
    fgets(note, MAX_NOTE_LENGTH, stdin);
    note[strcspn(note, "\n")] = '\0';


    fprintf(fp, "[%s] [%02d-%02d-%d %02d:%02d] %s\n", category, t->tm_mday, t->tm_mon + 1, t->tm_year + 1900, t->tm_hour, t->tm_min, note);
    fclose(fp);
    printf("Note saved with timestamp and category\n\n");
}

void viewNotes(void)
{
    FILE *fp = fopen(FILENAME, "r");
    if(fp == NULL)
    {
        printf("Could not open file\n");
        return;
    }

    char line[MAX_NOTE_LENGTH];
    printf("\n--- Your notes ---\n");

    while(fgets(line, sizeof(line), fp))
    {
        printf("- %s", line);
    }

    printf("\n------------------\n\n");
    fclose(fp);
}

void searchNotes(void)
{
    FILE *fp = fopen(FILENAME, "r");
    if(fp == NULL)
    {
        printf("Could not open file\n");
        return;
    }

    char query[100];
    char line[MAX_NOTE_LENGTH];
    int found = 0;

    printf("Enter the word you want to search: ");
    getchar();
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';

    printf("\n--- Search Results ---\n");

    while (fgets(line, sizeof(line), fp))
    {
        if(strstr(line, query) != NULL)
        {
            printf("- %s", line);
            found = 1;
        }
    }

    if(!found)
    {
        printf("No notes found\n");
    }

    printf("\n------------------\n\n");
    fclose(fp);
}

void deleteNote()
{
    FILE *fp = fopen(FILENAME, "r");
    if(fp == NULL)
    {
        printf("Note file not found\n");
        return;
    }


    char lines[100][MAX_NOTE_LENGTH];
    int count = 0;

    while (fgets(lines[count], MAX_NOTE_LENGTH, fp))
    {
        printf("%d. %s", count + 1, lines[count]);
        count++;
    }
    fclose(fp);

    if(count == 0)
    {
        printf("No notes found to delete\n\n");
    }


    int choice;
    printf("\nEnter the note number you want to delete: ");
    scanf("%d", &choice);

    if(choice < 1 || choice > count)
    {
        printf("Invalid selection\n\n");
        return;
    }


    FILE *fp2 = fopen("temp.txt", "w");
    if(fp2 == NULL)
    {
        printf("Failed to create temporary file\n");
        return;
    }

    for(int i = 0; i < count; i++)
    {
        if( i != choice - 1)
        {
            fputs(lines[i], fp2);
        }
    }

    fclose(fp2);

    // temp.tx --> notes.txt
    remove(FILENAME);
    rename("temp.txt", FILENAME);

    printf("The note was deleted\n\n");
}

void viewNotesByCategory(void)
{
    int selection;
    char line[MAX_NOTE_LENGTH];
    int found = 0;

    FILE *fp = fopen(FILENAME, "r");
    if(fp == NULL)
    {
        printf("Note file not found\n");
        return;
    }

    printf("Select Category:\n");
    for(int i = 0; i < CATEGORY_COUNT; i++)
    {
        printf("%d. %s\n", i + 1, categories[i]);
    }
    printf("Your choice: ");
    scanf("%d", &selection);

    if(selection < 1 || selection > CATEGORY_COUNT)
    {
        printf("Invalid category selection\n\n");
        fclose(fp);
        return;
    }

    const char *category = categories[selection - 1];

    printf("\n-- [%s] Notes in Category --\n", category);

    while(fgets(line, sizeof(line), fp))
    {
        if(strstr(line, category) == line + 1)
        {
            printf("- %s", line);
            found = 1;
        }
    }

    if(!found)
    {
        printf("No notes found for this category\n");
    }

    printf("\n------------------------------------------\n\n");
    fclose(fp);
}