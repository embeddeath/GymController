#include <date.h>
#include <time.h>

void getDate (date_t *date_pointer)
{
    struct tm *time_ptr;
    time_t rawtime; 

    time(&rawtime); 
    time_ptr = localtime(&rawtime); 

    

    date_pointer->month = time_ptr->tm_mon + 1;
    date_pointer->day = time_ptr->tm_mday; 
    date_pointer->year = time_ptr->tm_year + 1900;  
     
    
}