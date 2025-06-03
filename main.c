#include <stdio.h>
#include "notepad.h"
#include "password.h"

/*COMMAND LIST*/

#define ADD_COMMAND             1
#define VIEW_COMMAND            2
#define SEARCH_COMMAND          3
#define DELETE_COMMAND          4
#define CHANGE_PASSWORD_COMMAND 5
#define VIEW_CATEGORIES_COMMAND 6
#define EXIT_COMMAND            7


int main() {

if(!checkPassword())

{

    return 1;

}

    int choice;

    do

    {

        printf("===Personal Notebook===\n");
        printf("%d. Add Note\n", ADD_COMMAND);
        printf("%d. View Notebook\n", VIEW_COMMAND);
        printf("%d. Search Notebook\n", SEARCH_COMMAND);
        printf("%d. Delete Notebook\n", DELETE_COMMAND);
        printf("%d. Change Password\n", CHANGE_PASSWORD_COMMAND);
        printf("%d. View Category\n", VIEW_CATEGORIES_COMMAND);
        printf("%d. Exit\n", EXIT_COMMAND);
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
            {

            case ADD_COMMAND:
                addNote();
                break;

                case VIEW_COMMAND:
                viewNotes();
                break;

                case SEARCH_COMMAND:
                searchNotes();
                break;

                case DELETE_COMMAND:
                deleteNote();
                break;

                case CHANGE_PASSWORD_COMMAND:
                changePassword();
                break;

                case VIEW_CATEGORIES_COMMAND:
                viewNotesByCategory();
                break;

                case EXIT_COMMAND:
                printf("Good Bye!\n");
                break;

                default:
                printf("Wrong Choice\n");

            }
    } while(choice != EXIT_COMMAND);

    return 0;

}





