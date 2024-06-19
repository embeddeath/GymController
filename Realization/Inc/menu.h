#pragma once 
#include "member.h"

typedef enum
{
    CREATE_MEMBER = 1, 
    SEARCH_MEMBER, 
    LOAD_MEMBER, 
    SHOW_ALL_MEMBERS, 
    EXIT,
    MAX_NUMBER_OF_MENU_OPTIONS
}menu_options_t; 


extern menu_options_t gymControllerMenu(void); 

extern uint32_t createMemberMenu(member_t *memberPointer); 
extern int searchMemberMenu(void); 
extern int loadMemberMenu(member_t *memberPointer);
extern int editMemberMenu(member_t *memberPointer); 
