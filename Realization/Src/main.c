#include <stdio.h>
#include "menu.h"
#include "member.h"
#include "dbmanager.h"



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
                /* Verify if member exists.*/
                if (0 == loadMemberMenu(&memberBufferTest))
                {
                    displayMemberData(&memberBufferTest);
                    editMemberMenu(&memberBufferTest); 
                }
                
                break; 
            case SHOW_ALL_MEMBERS: 
                showAllMembers(); 
                break;
            case EXIT: 
                break; 
            default: 
                /* Should not get here*/
                break; 
        }
    
    } while (menuOption != EXIT);




}