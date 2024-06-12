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
    


}