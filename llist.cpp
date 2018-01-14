
/*********************************
//
// Name:        Brandon Kang
//
// Homework:    Project 2
//
// Class:       ICS 212
//
// Instructor:  Ravi Narayan
//
// Date:        11/26/2016
//
// File:        llist.cpp
//
// Description: File containing all the function definitions for the llist class.
//
//*******************************/

#include <iostream>
#include <string.h>
#include <fstream>
#include "llist.h"
#include "record.h"
#include "methodPrototypes.h"
using namespace std;

/*********************************
//
// Function name: readfile
//
// Description:   This function reads the formatted data from a specified text file, and stores it in a linked list in accordance with the record structure definition.
//
// Parameters:    none
//
// Return values:  -1             : error occurred
//                 accountsReadIn : Number of accounts read into the list.
//
//*******************************/

int llist::readfile(string filename)
{
    char tempAddr[80];
    string tempName;
    ifstream infile;
    int errorStatus, tempAcctNo, tempYOB, accountsReadIn = 0;
 
    readfileDebug();
    
    infile.open(filename.c_str());
    if(infile.is_open())
    {
        errorStatus = 0;
    }
    else
    {
        errorStatus = -1;
    }
    
    if(errorStatus == 0)
    {
        while(errorStatus != EOF)
        {
            infile >> tempAcctNo;
            errorStatus = infile.get();
            if(errorStatus == EOF)
            {
                break;
            }
            else
            {
                std::getline(infile,tempName);
                tempName.append(1,'\n');
                readAddress(tempAddr,infile);
                infile >> tempYOB;
                addRecord(tempAcctNo,tempName,tempAddr,tempYOB);
                accountsReadIn++;
            }
        }
        infile.close();
        
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
// Parameters:    none
//
// Return values:  none
//
//*******************************/

int llist::writefile(string filename)
{
    record * currRecord;
    ofstream outfile;
    int errorStatus;
    
    currRecord = start;
    
    writefileDebug();
    
    outfile.open(filename.c_str());

    if(outfile.is_open())
    {
        errorStatus = 0;
    }
    else
    {
        errorStatus = -1;
    }
    
    if(errorStatus == 0)
    {
        while(currRecord != NULL)
        {
            outfile << (*currRecord).accountno << "\n";
            outfile << (*currRecord).name;
            writeAddress((*currRecord).address,outfile);
            outfile << "\n" << (*currRecord).yearofbirth << "\n";
            currRecord = (*currRecord).next;
        }
        outfile.close();
    }
    
}

/*********************************
//
// Function name: reverse
//
// Description:   Recursive function that reverses the ordering of the records in the llist.
//
// Parameters:    input : record * used to navigate and reorder list, initial input should be start of list.
//
// Return values:  revRecord : the reverse ordered record
//
//*******************************/

record * llist::reverse(record * input)
{   
    record * revRecord;
    
    #ifdef DEBUGMODE
        reverseDebug();
    #endif
    
    if((*input).next == NULL)
    {
        this->start = input;
    }
    
    if((*input).next != NULL)
    {
        revRecord = reverse((*input).next);
        (*revRecord).next = input;
    }
    
    (*input).next = NULL;
    
    return input;
    
    
}

/*********************************
//
// Function name: cleanup
//
// Description:   llist Cleanup function. frees all dynamically allocated memory from heap.
//
// Parameters:    none
//
// Return values:  none
//
//*******************************/

void llist::cleanup()
{
    record * prevRecord;
    record * currRecord;
    
    if(start != NULL)
    {
        currRecord = start;
        prevRecord = NULL;
    
        while((*currRecord).next != NULL)
        {
            prevRecord = currRecord;
            currRecord = (*currRecord).next;
            delete prevRecord;
        }
        
        delete currRecord;
    }
}

/*public*/

/*********************************
//
// Function name: llist()
//
// Description:   Default constructor for the llist class
//
// Parameters:    none
//
// Return values:  none
//
//*******************************/

llist::llist()
{
    filename = "bankDB.txt";
    start = NULL;
    readfile(filename);
}

/*********************************
//
// Function name: llist(string filename)
//
// Description:   Overloaded constructor for llist class, takes a string as filename to name the file
//
// Parameters:    string filename : Name of the file that will be opened or created
//
// Return values:  none
//
//*******************************/

llist::llist(string paramFilename)
{
    filename = paramFilename;
    start = NULL;
    readfile(filename);
}

/*********************************
//
// Function name: ~llist()
//
// Description:   Destructor for the llist class. Writes the list to textfile and frees the allocated heap memory.
//
// Parameters:    none
//
// Return values:  none
//
//*******************************/

llist::~llist()
{
    writefile(filename);
    cleanup();
}

/*********************************
//
// Function name: addRecord
//
// Description:   Adds a new record with the specified data. Duplicate account numbers are allowed but not recommended. Account records are organized by year of birth in descending order. 
//                New accounts with a year of birth greater than or EQUAL to the first record's year of birth go in front of that record (to the 'left' of the start). 
//                New accounts with equal years of birth that are all less than the first record of the list go after the most recent entry with the same year of birth (to the 'right' of the most recent entry with same year of birth). 
//
// Parameters:    int acctNo             : the account number, key to add to the db
//                char name[]            : the name of the associated account holder
//                char address[]         : the address of the associated account holder
//                int yearofbirth        : the year of birth of the associated account holder
//
// Return values:  0 : success
//
//*******************************/

int llist::addRecord (int acctNo, string name, char address[ ],int yearofbirth)
{
    record * currRecord;
    record * tempRecordPrev;
    int addedRecords;
 
    addRecordDebug(acctNo,name,address,yearofbirth);
 
    addedRecords = 0;
    currRecord = start;

    if(start == NULL)
    {
       start = new record;
       (*start).accountno = acctNo;
       (*start).name = name;
       strcpy((*start).address,address);
       
       (*start).yearofbirth = yearofbirth;
       (*start).next = NULL;
       addedRecords++;
    }

    else
    {
       if(yearofbirth >= (*start).yearofbirth)
       {
           start = new record;
           (*start).next = currRecord;
           (*start).accountno = acctNo;
           (*start).name = name;
           strcpy((*start).address,address);
           (*start).yearofbirth = yearofbirth;
           currRecord = start;
           addedRecords++;
       }
       
       else if(yearofbirth < (*start).yearofbirth)
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
                   (*tempRecordPrev).next = new record;
                   tempRecordPrev = (*tempRecordPrev).next;
                   (*tempRecordPrev).accountno = acctNo;
                   (*tempRecordPrev).name = name;
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
           currRecord = new record;
           (*currRecord).next = NULL;
           (*currRecord).accountno = acctNo;
           (*currRecord).name = name;
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
// Parameters:    int acctNo    : The account number, key of the record to print
//
// Return values:  recordPrints : Number of records that were printed
//                 -1           : The specified record(s) could not be found
//
//*******************************/

int llist::printRecord (int acctNo)
{
    record * currRecord;
    int recordPrints = 0;
    
    currRecord = start;
    
    printRecordDebug(acctNo);
    
    while(currRecord != NULL)
    {
        if((*currRecord).accountno == acctNo)
        {
            cout << "\n" << (*currRecord).accountno <<"\n"<< (*currRecord).name << (*currRecord).address << "\n" << (*currRecord).yearofbirth << "\n";
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
// Parameters:    int acctNo           : the account number, key of the record to modify
//                char address[]       : the new address that will replace the existing address in the record
//
// Return values:  recordsChanged : Number of records successfully changed
//                 -1             : The specified record(s) could not be found.
//
//*******************************/

int llist::modifyRecord ( int acctNo, char address[ ])
{
    record * currRecord;
    int recordsChanged = 0;
    
    currRecord = start;
    
    modifyRecordDebug(acctNo, address);
    
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
// Function name: printAll
//
// Description:   Prints all of the contents of the list, each record is printed with each data element on its own line(s). DIfferent records are seperated by an extra newline.
//
// Parameters:    none
//
// Return values:  none
//
//*******************************/

void llist::printAll()
{
    record * currRecord;
    currRecord = start;
    
    printAllRecordsDebug();
    if(currRecord != NULL)
    {
        while(currRecord != NULL)
        {
             cout << "\n" << (*currRecord).accountno << "\n" << (*currRecord).name << (*currRecord).address << "\n" << (*currRecord).yearofbirth << "\n";
             currRecord = (*currRecord).next;
        }
    }
    
    else
    {
        emptyListPrint();
    }
}
/*********************************
//
// Function name: deleteRecord
//
// Description:   Deletes the record(s) specified by acctNo. All records with specified account number are deleted, including duplicates regardless of other content.
//
// Parameters:    int acctNo      : the account number, key of record to delete
//
// Return values:  deletedRecords : The number of records that were successfully deleted
//                  -1            : The specified record could not be found
//
//*******************************/

int llist::deleteRecord(int acctNo)
{
    struct record * currRecord;
    struct record * tempRecordPrev = NULL;
    int deletedRecords;
    
    deleteRecordDebug(acctNo);
    
    deletedRecords = 0;
    currRecord = start;
    
    while(currRecord != NULL)
    {
        if((*currRecord).accountno == acctNo)
        {
            if(tempRecordPrev == NULL)
            {
                currRecord = (*start).next;
                delete start;
                start = currRecord;
            }
            else
            {
                (*tempRecordPrev).next = (*currRecord).next;
                delete currRecord;
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


//new features
/*********************************
//
// Function name: reverse
//
// Description:   Wrapper metohd for the private reverse method
//
// Parameters:    none
//
// Return values:  none
//
//*******************************/

void llist::reverse()
{
    if(start != NULL)
    {
        reverse(start);
    }
    else
    {
        emptyListPrint();
    }
}

/*********************************
//
// Function name: operator<<
//
// Description:   Overloaded << operator. Functions same as printAll method.
//
// Parameters:    ostream&
//                  llist&
//
// Return values: ostream&
//
//*******************************/

ostream& operator<<(ostream&, llist& l2)
{
    record * currRecord;
    currRecord = l2.start;
    
    printAllRecordsDebug();
    if(currRecord != NULL)
    {
        while(currRecord != NULL)
        {
            cout << "\n" << (*currRecord).accountno << "\n" << (*currRecord).name << (*currRecord).address << "\n" << (*currRecord).yearofbirth << "\n";
            currRecord = (*currRecord).next;
        }
    }
    
    else
    {
        emptyListPrint();
    }
}
