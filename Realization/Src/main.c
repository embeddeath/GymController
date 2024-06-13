#include <stdio.h>
#include "menu.h"
#include "member.h"


void displayMemberData(member_t* member_ptr)
{
    printf("firstName: %s\n", member_ptr->firstName);
    printf("lastName: %s\n", member_ptr->lastName);
    printf("membershipType:  %d\n", member_ptr->membershipType);   
    printf("registrationDate: %d/%d/%d \n",member_ptr->registrationDate.month, member_ptr->registrationDate.day, member_ptr->registrationDate.year); 
    printf("lastPaymentDate: %d/%d/%d \n",member_ptr->lastPaymentDate.month, member_ptr->lastPaymentDate.day, member_ptr->lastPaymentDate.year); 
    printf("membershipStatus: %d\n", member_ptr->membesrhipStatus); 
}

int main ()
{

    member_t memberBuffer; 

    menu_options_t menuOption; 

    /* Ask user for operation until a valid option is selected*/
    do
    {
        menuOption = gymControllerMenu(); 

    } while (menuOption == MAX_NUMBER_OF_MENU_OPTIONS);


    switch (menuOption)
    {
        case CREATE_MEMBER: 
            
            createMemberMenu(&memberBuffer); 
            break; 
        case SEARCH_MEMBER: 
            searchMemberMenu(); 
            break; 
        case LOAD_MEMBER: 
            loadMemberMenu(); 
            break; 
        case SHOW_ALL_MEMBERS: 
            break;
        case EXIT: 
            break; 
        default: 
            /* Should not get here*/
            break; 
    }
    
    displayMemberData(&memberBuffer); 

}