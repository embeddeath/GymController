
#include <stdio.h>
#include "menu.h"
#include <stdint.h>
#define MAX_STRING_LENGTH 100


static char instructionToStringMap[MAX_NUMBER_OF_MENU_OPTIONS][MAX_STRING_LENGTH]= 
{
    "Create new member", 
    "Search member",
    "Load member for edition", 
    "Show all members", 
    "Exit GymController.",
}; 

static void greet()
{
    printf("Welcome to GymController software, please pick an option: \n"); 
}

static menu_options_t askUserForAction()
{
    menu_options_t menuOption;
    

    printf("1. Create new member.\n");
    printf("2. Search member.\n");
    printf("3. Load member for edition.\n");
    printf("4. Show all members.\n");
    printf("5. Exit GymController.\n");

    fflush(stdin); 
    scanf("%d", &menuOption); 

    /* Validate user input. */
    if ((uint32_t)menuOption >= MAX_NUMBER_OF_MENU_OPTIONS || menuOption < CREATE_MEMBER)
    {
        printf("%d is not a valid option, please try again. \n", menuOption);
        menuOption = MAX_NUMBER_OF_MENU_OPTIONS; 
    }
    else
    {
        printf("Option %d, %s selected", menuOption, instructionToStringMap[menuOption - 1] ); 
    }

    return menuOption; 
    
}

menu_options_t gymControllerMenu (void)
{
    menu_options_t menuOption; 

    greet();
    
    menuOption = askUserForAction(); 

    return menuOption; 


}



