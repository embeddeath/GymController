
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "member.h"
#include "dbmanager.h"
#include <stdint.h>
#include <string.h>
#include "stdbool.h"

#define MAX_STRING_LENGTH 100

typedef enum
{
    EDIT_FIRSTNAME = 1, 
    EDIT_LASTNAME, 
    EDIT_PAYMENT_PLAN, 
    REGISTER_PAYMENT, 
    CANCEL_MEMBERSHIP,
    EXIT_MENU,
    MAX_NUMBER_OF_LOAD_MENU_OPTIONS
}load_menu_options_t;

static char loadMenuInstructionToStringMap[MAX_NUMBER_OF_LOAD_MENU_OPTIONS][MAX_STRING_LENGTH]= 
{
    "Edit first name", 
    "Edit last name",
    "Edit payment plan", 
    "Register payment", 
    "Cancel membership.",
    "Exit menu",
}; 


static char instructionToStringMap[MAX_NUMBER_OF_MENU_OPTIONS][MAX_STRING_LENGTH]= 
{
    "Create new member", 
    "Search member",
    "Load member for edition", 
    "Show all members", 
    "Exit GymController.",
}; 

typedef enum
{
    FIRST_NAME, 
    LAST_NAME, 
    MAX_NUMBER_OF_NAME_TYPES
}member_name_t; 
    
static void greet()
{
    printf("Welcome to GymController software, please pick an option: \n"); 
}

/* Prompts */
static bool promptForName(member_t *memberPointer, member_name_t name_type_opt)
{
    char string_buffer[MAX_STRING_LENGTH];
    char userInput;
    bool userInputOk = false; 
    char userFdbkString[MAX_STRING_LENGTH]; 

    if ( FIRST_NAME == name_type_opt)
    {
        strcpy(userFdbkString, "first name");
    }
    else
    {
        strcpy(userFdbkString, "last name");
    }

    printf("Input Member's %s:  ", userFdbkString); 
    fflush(stdin); 
    scanf("%s", &string_buffer);

    printf("%s is: %s do you want to save it? Y/N: ", userFdbkString, string_buffer);

    fflush(stdin);
    scanf("%c", &userInput); 

    if (userInput == 'Y' || userInput == 'y') 
    {
        userInputOk = true; 
        if ( FIRST_NAME == name_type_opt)
        {
            strcpy(memberPointer->firstName, string_buffer);
        }
        else
        {
            strcpy(memberPointer->lastName, string_buffer);
        }
        
        printf("Member %s saved.\n", userFdbkString);  
    }
    
    return userInputOk; 
}

static bool promptForMembershipType (member_t *memberPointer)
{

    bool userInputOk = false; 
    char userInput;

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

    return userInputOk; 
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
    bool userInputOk; 
    
    if (memberPointer == NULL)
    {
        /* Pointer is invalid*/
        return -1; 
    }

    /* Assign unique ID to member*/
    memberPointer->id = (findLastUsedId() + 1);  

    /* Ask user for member First Name. */
    do 
    {
        userInputOk = promptForName(memberPointer, FIRST_NAME); 

    } while (false == userInputOk);

    /* Ask user for member Last Name*/
    do 
    {
        userInputOk = promptForName(memberPointer, LAST_NAME); 

    } while (false == userInputOk);

    /* Ask user for membership type */
    do 
    {
        userInputOk = promptForMembershipType(memberPointer);

    } while (false == userInputOk); 


    /* Save registration and last payment date to current time. */
    getDate(&(memberPointer->registrationDate));
    getDate(&(memberPointer->lastPaymentDate));    

    printf("New member registered: %d/%d/%d/ \n", memberPointer->registrationDate.month, memberPointer->registrationDate.day, memberPointer->registrationDate.year); 

    /* Activate membership*/
    memberPointer->membesrhipStatus = ACTIVE; 

    /* Write struct data to binary file.*/
    personWrite(memberPointer);

    return 0; 
}

int searchMemberMenu()
{
    FILE* file; 
    char buffer[MAX_STRING_LENGTH];
    member_t member; 
    bool matchFound = false; 

    printf("Enter first name to search in gym database: "); 
    fflush(stdin); 
    scanf("%s", &buffer);

    /* Open file in read mode*/
    file = fopen("gymcontrollerdata.dat", "rb");

    if (file == NULL) 
    {
        printf("Unable to open file.\n"); 
        return -1;
    }

    /* Read whole file and search for matches in first name*/
    while (feof(file) == 0 && false == matchFound )
    {
        fread(&member, sizeof(member_t), 1, file);

        /* Compare input string with db entry*/
        if (strcmp(member.firstName, buffer) == 0)
        {
            matchFound = true; 
        }
    }

    if (matchFound = true)
    {
        printf("Member %s %s found with id %d\n", member.firstName, member.lastName, member.id); 
    }
    else
    {
        printf("No matches found with first name %s\n", buffer); 
    }

    return 0; 
     
} 
int loadMemberMenu(member_t *member_ptr)
{
    uint32_t id; 
    printf("Enter member ID for edition. \n"); 
    fflush(stdin); 
    scanf("%d", &id); 

    if (true == getMemberDataById(member_ptr, id))
    {
        printf("Member %d loaded\n", id);
        return 0; 
    }
    else
    {
        printf("Member %d does not exist\n");
        return -1;  
    }
    
   
}

int editMemberMenu(member_t *memberPointer)
{
    load_menu_options_t option;
    bool userInputOk = false; 

    do 
    {    
        printf("What do you want to do with %s %s member id %d?\n", memberPointer->firstName, memberPointer->lastName, memberPointer->id);
        printf("1.  Edit member first name\n");
        printf("2.  Edit member last name\n"); 
        printf("3.  Edit member membership type\n"); 
        printf("4.  Register payment\n"); 
        printf("5.  Cancel membership \n");
        printf("6.  Go back \n");

        fflush(stdin);

        scanf("%d", &option);

        /* Validate user input. */
        if ((uint32_t)option >= MAX_NUMBER_OF_LOAD_MENU_OPTIONS || option < EDIT_FIRSTNAME)
        {
            printf("%d is not a valid option, please try again. \n", option);
            option = MAX_NUMBER_OF_LOAD_MENU_OPTIONS; 
        }
        else
        {
            printf("Option %d, %s selected\n", option, loadMenuInstructionToStringMap[option - 1] ); 
        }
        
        switch (option)
        {
            case EDIT_FIRSTNAME:
                userInputOk = promptForName(memberPointer, FIRST_NAME); 
                break;  

            case EDIT_LASTNAME:
                userInputOk = promptForName(memberPointer, LAST_NAME); 
                break;  

            case EDIT_PAYMENT_PLAN:
                userInputOk = promptForMembershipType(memberPointer); 
                break;  

            case REGISTER_PAYMENT:
                getDate(&(memberPointer->lastPaymentDate));
                /* Activate membership*/
                memberPointer->membesrhipStatus = ACTIVE; 
                userInputOk = true; 
                break;  

            case CANCEL_MEMBERSHIP:
                /* Cancel membership*/
                memberPointer->membesrhipStatus = INACTIVE;
                userInputOk = true; 
                break;  

            case EXIT_MENU:
                userInputOk = false; 
                break;  
            
            default:
                userInputOk = false;   
                break; 
        }  
    }while(false == userInputOk && option != EXIT_MENU); 

    /* If user input data correctly save struct to file. */
    if (userInputOk)
    { 
        personEdit(memberPointer);
    }
    else
    {
        printf("Edit operation aborted\n."); 
    }
    
    
    return 0; 
}