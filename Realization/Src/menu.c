
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "member.h"
#include <stdint.h>
#include <string.h>
#include "stdbool.h"
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


uint32_t createMemberMenu(member_t *memberPointer)
{
    char string_buffer[MAX_STRING_LENGTH];
    char userInputOk; 

    /* ToDo: Find a way to assign ID to member. */

    /* Ask user for member First Name. */

    do 
    {
        
        printf("Input Member's first Name:  "); 
        fflush(stdin); 
        scanf("%s", &string_buffer);

        printf("First name is: %s do you want to save it? Y/N: ");
        fflush(stdin);
        scanf("%c", &userInputOk); 

    } while (userInputOk != 'Y' && userInputOk != 'y');

    printf("Member first name saved."); 
    


    /* Ask user for member Last Name*/
    do 
    {
        
        printf("Input Member's last Name:  "); 
        fflush(stdin); 
        scanf("%s", &string_buffer);

        printf("First name is: %s do you want to save it? Y/N: ");
        fflush(stdin);
        scanf("%c", &userInputOk); 

    } while (userInputOk != 'Y' && userInputOk != 'y');

    printf("Member last name saved.");


    /* ToDo: Find a way to save registerDate and lastPaymentDate */

    /* Ask user for membership type */







    
}

extern uint32_t searchMemberMenu(void){} 
extern uint32_t loadMemberMenu(void){}