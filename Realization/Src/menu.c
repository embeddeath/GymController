
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
        printf("Option %d, %s selected\n", menuOption, instructionToStringMap[menuOption - 1] ); 
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
    char userInput;
    bool userInputOk; 
    
    if (memberPointer == NULL)
    {
        /* Pointer is invalid*/
        return -1; 
    }

    /* ToDo: Find a way to assign ID to member. */

    /* Ask user for member First Name. */
    do 
    {
        
        userInputOk = false; 

        printf("Input Member's first Name:  "); 
        fflush(stdin); 
        scanf("%s", &string_buffer);

        printf("First name is: %s do you want to save it? Y/N: ");

        fflush(stdin);
        scanf("%c", &userInput); 

        if (userInput == 'Y' || userInput == 'y') 
        {
            userInputOk = true; 
            strcpy(memberPointer->firstName, string_buffer);
            printf("Member first name saved.\n");  
        }

    } while (false == userInputOk);

  

    /* Ask user for member Last Name*/
    do 
    {
        userInputOk = false;

        printf("Input Member's last Name:  "); 
        fflush(stdin); 
        scanf("%s", &string_buffer);

        printf("Last name is: %s do you want to save it? Y/N: ");
        fflush(stdin);
        scanf("%c", &userInput); 

        if (userInput == 'Y' || userInput == 'y') 
        {
            userInputOk = true;
            strcpy(memberPointer->lastName, string_buffer); 
            printf("Member last name saved.\n");
        }

    } while (false == userInputOk);


    
    /* Ask user for membership type */
    do 
    {
        userInputOk = false; 

        printf("Select membership payment plan: Y - Yearly, M - Monthly: "); 
        fflush(stdin); 
        scanf("%c", &userInput); 


        if (userInput == 'Y' || userInput == 'y') 
        {
            memberPointer->membershipType = YEARLY_MEMBERSHIP;
            userInputOk = true; 
        }
        else if (userInput == 'M' || userInput == 'm')
        {
            memberPointer->membershipType = MONTHLY_MEMBERSHIP;
            userInputOk = true; 
        }
        else
        {
           printf("Invalid selection, please try again \n"); 
           userInputOk = false; 
        }   

        if (true == userInputOk)
        {
            printf("Membership type is %c do you want to save it? Y/N: ", userInput);
            fflush(stdin);
            scanf("%c", &userInput); 

            if (userInput == 'Y' || userInput == 'y') 
            {
                userInputOk = true; 
            }
            else
            {
                userInputOk = false; 
            }
        }


    } while (false == userInputOk); 



    /* Save registration and last payment date to current time. */
    getDate(&(memberPointer->registrationDate));
    getDate(&(memberPointer->lastPaymentDate));    

    printf("New member registered: %d/%d/%d/ \n", memberPointer->registrationDate.month, memberPointer->registrationDate.day, memberPointer->registrationDate.year); 

    /* Activate membership*/
    memberPointer->membesrhipStatus = ACTIVE; 

    return 0; 
}

extern uint32_t searchMemberMenu(void){} 
extern uint32_t loadMemberMenu(void){}