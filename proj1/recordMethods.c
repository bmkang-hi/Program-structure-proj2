/*********************************
//
// Name:        Brandon Kang
//
// Homework:    Project 1
//
// Class:       ICS 212
//
// Instructor:  Ravi Narayan
//
// Date:        10/18/2016
//
// File:        recordMethods.c
//
// Description: This file contains the methods for the bank database application, these methods are called in the main file , project1.c. 
//
//*******************************/
#include <stdio.h>
#include <string.h>
#include "record.h"
#include "methodPrototypes.h"

extern int debugmode;


/*********************************
//
// Function name: addRecord
//
// Description:   Adds a new record with the specified data. Duplicate account numbers are allowed but not recommended. Account records are organized by year of birth in descending order. 
//                New accounts with a year of birth greater than or EQUAL to the first record's year of birth go in front of that record (to the 'left' of the start). 
//                New accounts with equal years of birth that are all less than the first record of the list go after the most recent entry with the same year of birth (to the 'right' of the most recent entry with same year of birth). 
//
// Parameters:    struct record ** startAddr : the address pointing to the address holding the start address point of the database structure
//                int acctNo             : the account number, key to add to the db
//                char name[]            : the name of the associated account holder
//                char address[]         : the address of the associated account holder
//                int yearofbirth        : the year of birth of the associated account holder
//
// Return values:  0 : success
//
//*******************************/

int addRecord(struct record **startAddr, int acctNo, char name[],char address[],int yearofbirth)
{
    struct record * currRecord;
    struct record * tempRecordPrev;
    int addedRecords;
 
    addRecordDebug(startAddr,acctNo,name,address,yearofbirth);
 
    addedRecords = 0;
    currRecord = *startAddr;

    if(*startAddr == NULL)
    {
       *startAddr = (struct record *) malloc(sizeof(struct record));
       (**startAddr).accountno = acctNo;
       strcpy((**startAddr).name,name);
       strcpy((**startAddr).address,address);
       (**startAddr).yearofbirth = yearofbirth;
       (**startAddr).next = NULL;
       addedRecords++;
    }

    else
    {
       if(yearofbirth >= (**startAddr).yearofbirth)
       {
           *startAddr = (struct record *) malloc(sizeof(struct record));
           (**startAddr).next = currRecord;
           (**startAddr).accountno = acctNo;
           strcpy((**startAddr).name,name);
           strcpy((**startAddr).address,address);
           (**startAddr).yearofbirth = yearofbirth;
           currRecord = *startAddr;
           addedRecords++;
       }
       
       else if(yearofbirth < (**startAddr).yearofbirth)
       {
           while(currRecord != NULL)
           {
               if(yearofbirth <= (*currRecord).yearofbirth)
               {
                   tempRecordPrev = currRecord;
                   currRecord = (*currRecord).next;
               }
               
               else
               {
                   (*tempRecordPrev).next = (struct record *) malloc(sizeof(struct record));
                   tempRecordPrev = (*tempRecordPrev).next;
                   (*tempRecordPrev).accountno = acctNo;
                   strcpy((*tempRecordPrev).name,name);
                   strcpy((*tempRecordPrev).address,address);
                   (*tempRecordPrev).yearofbirth = yearofbirth;
                   (*tempRecordPrev).next = currRecord;
                   addedRecords++;
                   break;
               }
           }
       }
       
       if(addedRecords == 0)
       {
           currRecord = (struct record *) malloc(sizeof(struct record));
           (*currRecord).next = NULL;
           (*currRecord).accountno = acctNo;
           strcpy((*currRecord).name,name);
           strcpy((*currRecord).address,address);
           (*currRecord).yearofbirth = yearofbirth;
           (*tempRecordPrev).next = currRecord;
       }
    }



    return 0;
}




/*********************************
//
// Function name: printRecord
//
// Description:   Prints record(s) with the specified account number. If there are duplicate records, they are all printed.
//
// Parameters:    struct record *head : the start point of the database structure
//                int acctNo           : The account number, key of the record to print
//
// Return values:  recordPrints : Number of records that were printed
//                 -1           : The specified record(s) could not be found
//
//*******************************/

int printRecord(struct record *head, int acctNo)
{
    struct record * currRecord;
    int recordPrints = 0;
    
    currRecord = head;
    
    printRecordDebug(head,acctNo);
    
    while(currRecord != NULL)
    {
        if((*currRecord).accountno == acctNo)
        {
            printf("\n%d\n%s%s\n%d\n", (*currRecord).accountno, (*currRecord).name, (*currRecord).address, (*currRecord).yearofbirth);
            currRecord = (*currRecord).next;
            recordPrints++;
        }
        else
        {
            currRecord = (*currRecord).next;
        }
    }
    
    if(recordPrints == 0)
    {
        return -1;
    }
    else
    {
        return recordPrints;
    }
}




/*********************************
//
// Function name: modifyRecord
//
// Description:   Modifies the address of the record(s) with the specified account number. Duplicate account numbers will all have their addresses changed
//
// Parameters:    struct record *head : the start point of the database structure
//                int acctNo           : the account number, key of the record to modify
//                char address[]       : the new address that will replace the existing address in the record
//
// Return values:  recordsChanged : Number of records successfully changed
//                 -1             : The specified record(s) could not be found.
//
//*******************************/

int modifyRecord(struct record *head, int acctNo, char address[])
{
    struct record * currRecord;
    int recordsChanged = 0;
    
    currRecord = head;
    
    modifyRecordDebug(head, acctNo, address);
    
    while(currRecord != NULL)
    {
        if((*currRecord).accountno == acctNo)
        {
            strcpy((*currRecord).address,address);
            currRecord = (*currRecord).next;
            recordsChanged++;
        }
        else
        {
            currRecord = (*currRecord).next;
        }
    }
    if(recordsChanged == 0)
    {
        return -1;
    }
    else
    {
        return recordsChanged;
    }
}



/*********************************
//
// Function name: printAllRecords
//
// Description:   Prints all of the contents of the list, each record is printed with each data element on its own line(s). DIfferent records are seprated by an extra newline.
//
// Parameters:    struct record *head : the start point of the database structure
//
// Return values:  none
//
//*******************************/

void printAllRecords(struct record *head)
{
    struct record * currRecord;
    currRecord = head;
    
    printAllRecordsDebug(head);
    if(currRecord != NULL)
    {
        while(currRecord != NULL)
        {
             printf("\n%d\n%s%s\n%d\n", (*currRecord).accountno, (*currRecord).name, (*currRecord).address, (*currRecord).yearofbirth);
             currRecord = (*currRecord).next;
        }
    }
}




/*********************************
//
// Function name: deleteRecord
//
// Description:   Deletes the record(s) specified by acctNo. All records with specified account number are deleted, including duplicates regardless of other content.
//
// Parameters:    struct record **startAddr : the address pointing to the address holding the start point of the database structure
//                int acctNo            : the account number, key of record to delete
//
// Return values:  deletedRecords : The number of records that were successfully deleted
//                  -1            : The specified record could not be found
//
//*******************************/

int deleteRecord(struct record **startAddr, int acctNo)
{
    struct record * currRecord;
    struct record * tempRecordPrev = NULL;
    int deletedRecords;
    
    deleteRecordDebug(startAddr, acctNo);
    
    deletedRecords = 0;
    currRecord = *startAddr;
    
    while(currRecord != NULL)
    {
        if((*currRecord).accountno == acctNo)
        {
            if(tempRecordPrev == NULL)
            {
                currRecord = (**startAddr).next;
                free(*startAddr);
                *startAddr = currRecord;
            }
            else
            {
                (*tempRecordPrev).next = (*currRecord).next;
                free(currRecord);
                currRecord = tempRecordPrev;
            }
            deletedRecords++;
        }
        else
        {
            tempRecordPrev = currRecord;
            currRecord = (*currRecord).next;
        }
    }
    if(deletedRecords == 0)
    {
        return -1;
    }
    else
    {
        return deletedRecords;
    }
}




/*********************************
//
// Function name: readfile
//
// Description:   This function reads the formatted data from a specified text file, and stores it in a linked list in accordance with the record structure definition.
//
// Parameters:    struct record ** startAddr : The address of the start of the list to be populated by reading in the bankDB.txt file and passing to the addRecord function.
//
// Return values:  -1             : error occurred
//                 accountsReadIn : Number of accounts read into the list.
//
//*******************************/

int readfile(struct record ** startAddr, char addr[])
{
    char tempAddr[80], tempName[25];
    FILE * infile;
    int errorStatus, tempAcctNo, tempYOB, accountsReadIn = 0;
 
     readfileDebug();
 
    infile = fopen("bankDB.txt","r");
    errorStatus = errorHandle(infile);
    if(errorStatus == 0)
    {
        while(errorStatus != EOF)
        {
            errorStatus = fscanf(infile,"%d",&tempAcctNo);
            fgetc(infile);
            if(errorStatus == EOF)
            {
                break;
            }
            else
            {
                fgets(tempName,25,infile);
                readAddress(tempAddr,infile);
                fscanf(infile,"%d",&tempYOB);
                addRecord(startAddr,tempAcctNo,tempName,tempAddr,tempYOB);
                accountsReadIn++;
            }
        }
        fclose(infile);
        
    }
    
    else
    {
        return -1;
    }
    return accountsReadIn;

}


/*********************************
//
// Function name: writefile
//
// Description:   This function writes the contents of the accounts array into the specified file with appropriate formatting.
//
// Parameters:    struct record * head : The start of the list containing the records to be read and written to the bankDB.txt file.
//
// Return values:  none
//
//*******************************/

void writefile(struct record * head, char addr[])
{
    struct record * currRecord;
    FILE * outfile;
    int errorStatus;
    
    currRecord = head;
    
    writefileDebug();
    
    outfile = fopen("bankDB.txt","w");
    errorStatus = errorHandle(outfile);
    if(errorStatus == 0)
    {
        while(currRecord != NULL)
        {
            fprintf(outfile,"%d\n",(*currRecord).accountno);
            fprintf(outfile,"%s",(*currRecord).name);
            writeAddress((*currRecord).address,outfile);
            fprintf(outfile,"\n%d\n",(*currRecord).yearofbirth);
            currRecord = (*currRecord).next;
        }
        fclose(outfile);
    }
    
}




