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
// File:        project1.c
//
// Description: This file contains the main function and getaddress function for the simulated bank application, It also provides the user interface functions and debugmode flag.
//
//*******************************/

#include <stdio.h>
#include <string.h>
#include "record.h"
#include "methodPrototypes.h"

int debugmode;

int addRecord(struct record **, int, char[], char[],int);
int modifyRecord(struct record *, int, char[]);
int printRecord(struct record *,int);
void printAllRecords(struct record *);
int deleteRecord(struct record **,int);
int writefile(struct record *, char []);
void readfile(struct record **, char []);

/*********************************
//
// Function name: main
//
// Description:   main function and user interface for HW3b program. displays menu as list numbered on left side from 1-6, and prompts user for command to execute. Checks for commandline arguments. if none, runs as normal, if includes debug flag, enables debug mode.
//                exits on invalid command line arguments.
//
// Parameters:    argc : indicates number of command line arguments passed
//                argv : contains command line arguments passed
//
// Return values:  0 : success
//
//*******************************/

int main(int argc, char * argv[])
{
    int acctnum, yearofbirth, menuSelection, errorCode, returnVals, addrSize = 80, quitInput = 0;
    char acctName[25], address[80], clearBuffer[100], debugStr[] = "debug";
    struct record * start = NULL;
    
    
    if(argc == 2 && strcmp(argv[1], debugStr) == 0)
    {
        debugmode = 1;
    }
    else if(argc > 1)
    {
        printf("hw3b: Incorrect arguments\nUsage: hw3b\n       hw3b [debug]\n");
        exit(0);
    }
    else
    {
        debugmode = 0;
    }
    
    
    if(debugmode == 1)
    {
        printf("\n\n***DEBUG***\n    Function name: main\n    parameters passed:\nint argc: %4d\nchar *argv[]: %4p\n***********\n\n",argc,argv);
    }
    
    
    readfile(&start, address);
    do
    {
        printf("\n(1) Add a new record in the database\n(2) Modify a record in the database using the accountno as the key\n(3) Print information about a record using the accountno as the key\n(4) Print all information in the database\n(5) Delete an existing record from the database using the accountno as a key\n(6) Quit the program\n\nPlease enter the number of the menu item to run: ");
        errorCode = scanf("%d", &menuSelection);
        if(errorCode != 1 || menuSelection < 1 || menuSelection > 6)
        {
            printf("\nInvalid input, please enter the number to the left of the menu item you want to run:\n");
            fgets(clearBuffer,100,stdin);
        }
        
        switch (menuSelection)
        {
            case 1:
                printf("\nAdding a new record...\n\nPlease enter the account number to add: ");
                scanf("%d", &acctnum);
                fgets(clearBuffer,100,stdin);
                
                printf("\nPlease enter the name of the account holder under 25 characters: ");
                fgets(acctName,25,stdin);
                getaddress(address,addrSize);
                fgets(clearBuffer,100,stdin);
                
                printf("\nPlease enter the account holders year of birth (between 1800 and 2016): ");
                scanf("%d", &yearofbirth);
                fgets(clearBuffer,100,stdin);
                while(yearofbirth < 1800 || yearofbirth > 2016)
                    {
                        printf("\nPlease enter a valid year of birth (between 1800 and 2016 inclusive: ");
                        scanf("%d", &yearofbirth);
                        fgets(clearBuffer,100,stdin);
                    }
                    
                returnVals = addRecord(&start,acctnum,acctName,address,yearofbirth);
                if(returnVals == 0)
                {
                    printf("\nRecord added successfully.");
                }
                
                
                menuSelection = 0;
                break;
                
                
            case 2:
                if(start != NULL)
                {
                    printf("\nModifying existing records address...\n\nPlease enter the account number whose address you want to change: ");
                    scanf("%d",&acctnum);
                    fgets(clearBuffer,100,stdin);
                    getaddress(address,addrSize);
                    fgets(clearBuffer,100,stdin);
                    returnVals = modifyRecord(start,acctnum,address);
                    if(returnVals != -1)
                    {
                        printf("\n%d record(s) modified successfully.",returnVals);
                    }
                    else
                    {
                        printf("Specified record doesn't exist.\n");
                    }
                    menuSelection = 0;
                }
                
                else
                {
                    printf("\nThe list is empty.\n");
                }
                break;
                
                
            case 3:
                if(start != NULL)
                {
                    printf("\nPrinting record information...\n\nPlease enter the account number to print information from: ");
                    scanf("%d",&acctnum);
                    fgets(clearBuffer,100,stdin);
                    returnVals = printRecord(start,acctnum);
                    menuSelection = 0;
                   
                   if(returnVals == -1) 
                    {
                        printf("Specified record doesn't exist.\n");
                    }
                }
               
                else
                {
                    printf("\nThe list is empty.\n");
                }
                break;
                
                
            case 4:
                if(start != NULL)
                {
                    printf("\nPrinting all record information...\n");
                    printAllRecords(start);
                    menuSelection = 0;
                }
                
                else
                {
                    printf("\nThe list is empty.\n");
                }
                break;
                
                
            case 5:
                printf("\nDeleting existing record...\n\nPlease enter the account number to delete: ");
                scanf("%d",&acctnum);
                fgets(clearBuffer,100,stdin);
                returnVals = deleteRecord(&start,acctnum);
                if(returnVals != -1)
                {
                    printf("\n%d record(s) deleted successfully.\n",returnVals);
                }
               
                else
                {
                    printf("The entered account number doesn't exist or the list is empty.\n");
                }
                menuSelection = 0;

                break;

                
            case 6:
                printf("\nQuitting program...\n");
                quitInput = 1;
                menuSelection = 0;
                writefile(start, address);
                break;
        }
        
    }
    while(quitInput == 0);
    
return 0;
}



/*********************************
//
// Function name: getaddress
//
// Description:   Takes two parameters, a character array for the address data and the size of that array. Clears any data left in the address array, then prompts user for address input that is terminated with $ character. 
//                stores that input in the empty address array
//
// Parameters:    char address[] : The array that will hold the address information.
//                int size : The size of the character array, address.
//
// Return values:  none
//
//*******************************/

void getaddress(char address[], int size)
{
    int addressCharVal, i;
    char addressChar;
    
    if(debugmode == 1)
    {
        printf("\n\n***DEBUG***\n    Function name: getaddress\n    parameters passed:\nchar Address[]: %1p\nint Size: %d\n***********\n\n", address, size);
    }
    
    
    i=0;
    printf("\nPlease enter the address of the account holder (fewer than 80 characters)\nType '$' (US dollar sign, no quotes) to complete address entry\n");
    do
    {
        addressCharVal = fgetc(stdin);
        addressChar = (char) addressCharVal;
        address[i] = addressChar;
        i++;
        
    }
    while(addressChar != '$' && i < (size - 1));
    if(i >= (size - 1))
    {
        address[i] = '\0';
    }
    else
    {
        address[i - 1] = '\0';
    }
}


/*********************************
//
// Function name: addRecordDebug
//
// Description:   checks debugmode state, prints debug messages if appropriate for addRecord method
//
// Parameters:    struct record ** startAddr : the address pointing to the addressing holding the start point of the database structure
//                int acctNo             : the account number, key to add to the db
//                char name[]            : the name of the associated account holder
//                char address[]         : the address of the associated account holder
//                int yearofbirth        : the year of birth of the associated account holder
//
// Return values:  none
//
//*******************************/

void addRecordDebug(struct record **startAddr, int acctNo, char name[],char address[],int yearofbirth)
{
        if(debugmode == 1)
    {
           printf("\n\n***DEBUG***\n    Function name: addRecord\n    parameters passed:\n List address: %p\n Name: %s Account number: %d\n Address: %s\n Year of Birth: %d\n***********\n\n",startAddr, name, acctNo, address, yearofbirth);
    }
}

/*********************************
//
// Function name: printRecordDebug
//
// Description:   checks debugmode state, prints debug messages if appropriate for printRecord method
//
// Parameters:    struct record *head : the start point of the database structure
//                int acctNo           : The account number, key of the record to print
//
// Return values:  none
//
//*******************************/

void printRecordDebug(struct record *head, int acctNo)
{
        if(debugmode == 1)
    { 
        printf("\n\n***DEBUG***\n    Function name: printRecord\n    parameters passed:\n List start address: %p\n Account number: %d\n***********\n\n",head, acctNo);
    }
}

/*********************************
//
// Function name: modifyRecordDebug
//
// Description:   checks debugmode state, prints debug messages if appropriate for modifyRecord method
//
// Parameters:    struct record *head : the start point of the database structure
//                int acctNo           : the account number, key of the record to modify
//                char address[]       : the new address that will replace the existing address in the record
//
// Return values:  none
//
//*******************************/

void modifyRecordDebug(struct record *head, int acctNo, char address[])
{
        if(debugmode == 1)
    {
        printf("\n\n***DEBUG***\n    Function name: modifyRecord \n    parameters passed:\n List start address: %p\n Account number: %d\n Address: %s\n***********\n\n", head, acctNo, address);
    }
}

/*********************************
//
// Function name: printAllRecordsDebug
//
// Description:   checks debugmode state, prints debug messages if appropriate for printAllRecords method
//
// Parameters:    struct record *head : the start point of the database structure
//
// Return values:  none
//
//*******************************/

void printAllRecordsDebug(struct record *head)
{
        if(debugmode == 1)
    {
        printf("\n\n***DEBUG***\n    Function name: printAllRecords\n    parameters passed:\n List start address: %p\n***********\n\n", head);
    }
}

/*********************************
//
// Function name: deleteRecordDebug
//
// Description:   checks debugmode state, prints debug messages if appropriate for deleteRecord method
//
// Parameters:    struct record **startAddr : the address pointing to the address holding start point of the database structure
//                int acctNo            : the account number, key of record to delete
//
// Return values:  none
//
//*******************************/

void deleteRecordDebug(struct record **startAddr, int acctNo)
{
        if(debugmode == 1)
    {
        printf("\n\n***DEBUG***\n    Function name:deleteRecord\n    parameters passed:\n List address: %p\n Account number: %d\n***********\n\n", startAddr, acctNo);
    }
}


/*********************************
//
// Function name: readAddress
//
// Description:   This function is used to read the address text from the specified buffer and stores the address as a string in the specified account structure variable
//
// Parameters:    char address [] : This is the char pointer to the array intended to contain the address data in the account structure
//                FILE * buffer   : This is the buffer to read the address data from
//
// Return values:  none
//
//*******************************/

void readAddress(char address [], FILE * buffer)
{
    int addressCharVal, i=0, size = 80;
    char addressChar;

    if(debugmode ==1)
    {
        printf("\n\n***DEBUG***\n    Function name:readAddress\nParameters:\nchar address[]\nFILE * buffer\n***********\n\n");
    }
 
    do
    {
        addressCharVal = fgetc(buffer);
        addressChar = (char) addressCharVal;
        address[i] = addressChar;
        i++;
    }
    while(addressChar != '$' && i < (size - 1));
    if(i >= (size - 1))
    {
        address[i] = '\0';
    }
    
    else
    {
        address[i - 1] = '\0';
    }
}

/*********************************
//
// Function name: writeAddress
//
// Description:   This function is used to write the address text from the records in the array into the text file in the appropriate format.
//
// Parameters:    char address [] : This is the char pointer to the array containing the address data in the account structure
//                FILE * buffer   : This is the buffer to write the address data to
//
// Return values:  none
//
//*******************************/

void writeAddress(char address [], FILE * buffer)
{
    int terminateCharVal, charWrittenVal, i = 0;
    char charWritten, terminateChar = '$';
    
    terminateCharVal = (int) terminateChar;
    
        if(debugmode ==1)
    {
        printf("\n\n***DEBUG***\n    Function name:writeAddress\nParameters:\nchar address[]\nFILE * buffer\n***********\n\n");
    }
    
    do
    {
        charWrittenVal = fputc(address[i], buffer);
        charWritten = (char) charWrittenVal;
        i++;
    }
    while(charWritten != '\0' && i < 79);
    fputc(terminateCharVal,buffer);
}


/*********************************
//
// Function name: errorHandle
//
// Description:   This function checks for errors in opening the specified file and returns a value indicating status
//
// Parameters:    FILE * status : The buffer that intended to be linked to the specified file
//
// Return values:  -1 : Error occurred in opening or creating file.
//                  0 : Successfully opened or created file.
//
//*******************************/

int errorHandle(FILE * status)
{
        if(debugmode ==1)
    {
        printf("\n\n***DEBUG***\n    Function name:errorHandle\nParameters:\nFILE * status\n***********\n\n");
    }
    
    if(status == NULL)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/*********************************
//
// Function name: readfileDebug
//
// Description:   Checks debugmode state, prints appropriate debug messages
//
// Parameters:    none
//
// Return values: none
//
//*******************************/

void readfileDebug()
{
    if(debugmode == 1)
    {
        printf("\n\n***DEBUG***\n    Function name:readfile\nParameters:\nstruct record ** startAddr\nchar addr[]\n***********\n\n");
    }
}

/*********************************
//
// Function name: writefileDebug
//
// Description:   Checks debugmode state, prints appropriate debug messages.
//
// Parameters:    none
//
// Return values:  none
//
//*******************************/

void writefileDebug()
{
    if(debugmode == 1)
    {
        printf("\n\n***DEBUG***\n    Function name:writefile\nParameters:\nstruct record * head\nchar addr[]\n***********\n\n");
    }
}

