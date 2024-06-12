#pragma once 

typedef enum
{
    CREATE_MEMBER = 1, 
    SEARCH_MEMBER, 
    LOAD_MEMBER, 
    SHOW_ALL_MEMBERS, 
    EXIT,
    MAX_NUMBER_OF_MENU_OPTIONS
}menu_options_t; 


extern menu_options_t gymControllerMenu (void); 