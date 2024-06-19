#include <stdio.h>
#include <stdint.h>
#include "member.h"

extern int personWrite (member_t *member_ptr);
extern int personEdit (member_t *member_ptr); 
extern int personRead (member_t *member_ptr); 
extern uint32_t findLastUsedId (void); 
extern int createEnsureDbFile(void);
extern int getMemberDataById (member_t *member_ptr, uint32_t id);

/* ToDo: create an interface that retrieves member id based on first name*/
/* ToDo: create an interface that retrieves member id based on last name*/