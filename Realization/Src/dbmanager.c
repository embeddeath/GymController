
#include <stdlib.h>
#include <stdbool.h>
#include "dbmanager.h"
#include <stdint.h>

static bool isDbFileNew (void); 


int personWrite (member_t *member_ptr)
{
    FILE* file; 
    /* If we are writing the first member to the database, clear the uninit pattern, else append to the file.*/
    if (true == isDbFileNew())
    {
        file = fopen("gymcontrollerdata.dat", "wb");
    }
    else
    {
        file = fopen("gymcontrollerdata.dat", "ab");
    }
    

    if (file == NULL) 
    {
        printf("Unable to open file.\n"); 
        return -1;
    }
 
    // Write the struct data to the file
    size_t num_written = fwrite(member_ptr, sizeof(member_t), 1, file);
    if (num_written != 1) { 
        perror("Error writing to file");
        fclose(file);
        return 1;
    }

    fclose(file);

    return 0; 
}

int personEdit (member_t *member_ptr)
{
    FILE* file; 
    member_t memberBuffer; 
    memberBuffer.id = 0;
    long savedFilePointerAddress; 
    bool personFound = false; 


    printf("member_ptr.id = %d\n",member_ptr->id); 

    /* Open file in read mode*/
    file = fopen("gymcontrollerdata.dat", "rb");
    

    if (file == NULL) 
    {
        printf("Unable to open file.\n"); 
        return -1;
    }
 
    
    /* Position the file pointer to the proper index we want to edit. */
    while (false == personFound && feof(file) == 0)
    {

         
        size_t num_read = fread(&memberBuffer, sizeof(member_t), 1, file);

        /* Abort read operation if it fails. */
        if (num_read != 1) { 
            fclose(file);
            return -1;
        }
        
        /* Signal that we found a match */
        if (memberBuffer.id == member_ptr->id)
        {
            personFound = true;
            
            printf("PersonFound\n"); 
        }
        printf("member_ptr->id = %d | memberBuffer.id = %d\n",member_ptr->id, memberBuffer.id);
    }
    
    if (true == personFound)
    {
        
        /* ToDo: Ask teacher if this is the proper way to index a binary file. */

        /* We have found the person, save current */
        savedFilePointerAddress = ftell(file);
        fclose(file);
        fopen("gymcontrollerdata.dat", "r+b");
        fseek(file, savedFilePointerAddress - sizeof(member_t), SEEK_SET); 

        

        size_t num_written = fwrite(member_ptr, sizeof(member_t), 1, file);

        if (num_written != 1) { 
            fclose(file);
            return 1;
        }
        else
        {
            printf("Information was updated successfully.\n"); 
            fclose(file); 
        }

    }
    else
    {
        printf("Error, person id not found. ");
        fclose(file); 
        return -1; 
    }
                
    

    return 0; 
}

int personRead (member_t *member_ptr)
{

    // Open a file in binary write mode
    FILE* file = fopen("gymcontrollerdata.dat", "rb");

    rewind(file);

    if (file == NULL) 
    {
        printf("Unable to open file.\n"); 
        return -1;
    }
 
    // Write the struct data to the file
    size_t num_written = fread(member_ptr, sizeof(member_t), 1, file);

    fclose(file);

    return 0; 
}

uint32_t findLastUsedId (void)
{


    /* If db file is new default to id 0*/
    if (true == isDbFileNew())
    {
        printf("New db file defaulting to member id 0\n"); 
        return 0; 
    }

    // Open a file in binary write mode
    FILE* file = fopen("gymcontrollerdata.dat", "rb");
    member_t member; 


    if (file == NULL) 
    {
        printf("Unable to open file.\n");
        fclose(file);
        return -1;
        
    }
    
    /* Do a linear search on the file */
    while (false == feof(file))
    {
        size_t numberOfStructsRead = fread(&member, sizeof(member_t), 1, file);
    }

    /* Return last valid member id*/ 
    return member.id; 

    fclose(file); 

 
}

/* ToDo: Improve readability of this function. */
int createEnsureDbFile(void)
{
    /* Attempt to open db file. */
    FILE* file = fopen("gymcontrollerdata.dat", "rb");
    
    /* If file does not exist create it*/
    if (file == NULL) 
    {
        printf("Db file was not found, creating new db file.\n"); 
        file = fopen("gymcontrollerdata.dat", "wb");


        
        if (file == NULL)
        {
            printf("Unable to create db file\n"); 
            return -1; 
        }
        else
        {
            /* Write dummy struct id to signal that the db is virgin. */
            printf("Initializing db file\n"); 
            member_t dummyMember; 
            dummyMember.id = DUMMY_STRUCT_ID_PATTERN; 
            dummyMember.membershipType = 1;
            fwrite(&dummyMember, sizeof(member_t), 1, file);
            fclose(file); 
            return 0; 
        }
        
        

    }
    else
    {
        printf("gymcontrollerdata.dat exists. \n");
        fclose(file); 
        
        return 0;
    }

     
}


static bool isDbFileNew (void)
{
    /* Attempt to open db file. */
    FILE* file = fopen("gymcontrollerdata.dat", "rb");

    /* Read first struct member and find a pattern match. */
    member_t member; 
    fread(&member, sizeof(member_t), 1, file);
    fclose(file); 

    if (member.id == DUMMY_STRUCT_ID_PATTERN)
    {
        
        return true; 
    }
    else
    {
        return false; 
    }
    
}



int getMemberDataById (member_t* member_ptr, uint32_t id)
{
    // Open a file in binary read mode
    FILE* file = fopen("gymcontrollerdata.dat", "rb");
    member_t member;
    bool match = false; 


    if (file == NULL) 
    {
        printf("Unable to open file.\n");
        fclose(file);
        return -1;
        
    }
    
    /* Do a linear search on the file and copy over struct data if ids match.*/
    while (false == feof(file) && false == match)
    {
        fread(&member, sizeof(member_t), 1, file);


        if ( id == member.id )
        {
            match = true;
            *member_ptr = member; 
        }

    }

    fclose(file);

    return match; 
}

int searchMemberByFirstName(char* buffer) 
{
    FILE* file; 
    member_t member; 
    bool matchFound = false; 

 /* Open file in read mode*/
    file = fopen("gymcontrollerdata.dat", "rb");

    if (file == NULL) 
    {
        printf("Unable to open file.\n"); 
        return -1;
    }

    /* Read whole file and search for matches in first name*/
    while (feof(file) == 0 && false == matchFound )
    {
        fread(&member, sizeof(member_t), 1, file);

        /* Compare input string with db entry*/
        if (strcmp(member.firstName, buffer) == 0)
        {
            matchFound = true; 
        }
    }

    if (true == matchFound)
    {
        printf("Member %s %s found with id %d\n", member.firstName, member.lastName, member.id); 
        return 0; 
    }
    else
    {
        printf("No matches found with first name %s\n", buffer);
        return -1; 
    }

    fclose(file); 
}