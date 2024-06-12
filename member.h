
#pragma once

#include <stdint.h>
#include <time.h>

#define MAX_STRING_LENGTH 100


typedef enum
{
    MONTHLY_MEMBERSHIP, 
    YEARLY_MEMBERSHIP
}membership_t; 

typedef enum
{
    INACTIVE, 
    ACTIVE
}membershipStatus_t; 

typedef struct member
{
    uint32_t id; 
    char firstName[MAX_STRING_LENGTH]; 
    char lastName[MAX_STRING_LENGTH]; 
    /* registrationDate ToDo: find a way to store date in format MM/DD/YYYY*/
    membership_t membershipType; 
    /* lastPaymentDate ToDo: find a way to store date in format MM/DD/YYYY*/
    membershipStatus_t membesrhipStatus; 
} member_t; 


