#include <stdio.h>
#include "menu.h"
#include "member.h"
#include "dbmanager.h"

void displayMemberData(member_t* member_ptr)
{
    printf("id: %d\n", member_ptr->id);
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
    member_t memberBufferTest; 

    menu_options_t menuOption; 

    /*Verify that the databese file exists, and creates it if deoes not.*/
    if (-1 == createEnsureDbFile())
    {
        /* There was an error creating the file, aborting program execution*/
        return -1; 
    }

    /* Ask user for operation until a valid option is selected*/
    do
    {
        menuOption = gymControllerMenu(); 

        switch (menuOption)
        {
            case CREATE_MEMBER: 
                createMemberMenu(&memberBuffer); 
                displayMemberData(&memberBuffer); 
                break; 
            case SEARCH_MEMBER: 
                searchMemberMenu(); 
                break; 
            case LOAD_MEMBER: 
                if ( 0 == loadMemberMenu(&memberBufferTest))
                {
                    displayMemberData(&memberBufferTest);
                }
                
                break; 
            case SHOW_ALL_MEMBERS: 
                break;
            case EXIT: 
                break; 
            default: 
                /* Should not get here*/
                break; 
        }
    
    } while (menuOption != EXIT);




}