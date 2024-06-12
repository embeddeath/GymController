#include <stdio.h>
#include "menu.h"
#include "member.h"

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
    


}