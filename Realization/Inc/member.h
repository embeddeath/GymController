
#pragma once

#include <stdint.h>
#include "date.h"

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
    date_t registrationDate; 
    membership_t membershipType; 
    date_t lastPaymentDate; 
    membershipStatus_t membesrhipStatus; 
} member_t; 


