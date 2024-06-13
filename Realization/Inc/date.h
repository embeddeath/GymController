#pragma once
#include <stdint.h>

typedef enum 
{
    JANUARY = 1, 
    FEBRUARY, 
    MARCH, 
    APRIL, 
    MAY, 
    JUNE, 
    JULY, 
    AUGUST,
    SEPTEMBER, 
    OCTOBER, 
    NOVEMBER, 
    DECEMBER, 
    MAX_NUMBER_OF_MONTS, 
}months_t; 

typedef struct 
{
    months_t month; 
    uint8_t day; 
    uint16_t year; 
}date_t;


void getDate (date_t *date_pointer); 