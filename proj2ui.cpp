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
// File:        proj2ui.cpp
//
// Description: Contains the UI functions and main method as well as any other helper functions that communicate wth the user such as debug output.
//
//*******************************/

#include "llist.h"
#include <iostream>
#include <fstream>
using namespace std;

void getaddress(char [], int);


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

int main()
{
    int acctnum, yearofbirth, menuSelection, errorCode, returnVals, addrSize = 80, quitInput = 0;
    char address[80];
    string acctName;

    llist bankList;
    
    #ifdef DEBUGMODE
        cout<< "\n\n***DEBUG***\n    Function name: main\n    parameters passed:\nint argc:     " << argc << "\nchar *argv[]:     " << argv << "\n***********\n\n";
    #endif
    
    do
    {
        cout << "\n(1) Add a new record in the database\n(2) Modify a record in the database using the accountno as the key\n(3) Print information about a record using the accountno as the key\n(4) Print all information in the database\n(5) Delete an existing record from the database using the accountno as a key\n(6) Reverse the list order\n(7) Quit the program\n\nPlease enter the number of the menu item to run: ";
        cin >> menuSelection;
        
        if(menuSelection < 1 || menuSelection > 7)
        {
            cout << "\nInvalid input, please enter the number to the left of the menu item you want to run:\n";
            cin.clear();
            cin.ignore(50,'\n');
        }
        
        switch (menuSelection)
        {
            case 1:
                cout << "\nAdding a new record...\n\nPlease enter the account number to add: ";
                cin >> acctnum;
                
                while(cin.fail())
                {
                    cout << "\nInvalid entry. Please enter a number.";
                    cin.clear();
                    cin.ignore(50,'\n');
                    cin >> acctnum;
                }
                cin.ignore(50,'\n');
                
                cout << "\nPlease enter the name of the account holder under 25 characters: ";
                std::getline(cin,acctName);
                acctName.append(1,'\n');
                getaddress(address,addrSize);
                cin.ignore(50,'\n');
                
                cout << "\nPlease enter the account holders year of birth (between 1800 and 2016): ";
                cin >> yearofbirth;
                cin.ignore(50,'\n');
                
                while(yearofbirth < 1800 || yearofbirth > 2016)
                    {
                        cout << "\nPlease enter a valid year of birth (between 1800 and 2016 inclusive: ";
                        cin >> yearofbirth;
                        cin.clear();
                        cin.ignore(50,'\n');
                    }
                    
                returnVals = bankList.addRecord(acctnum,acctName,address,yearofbirth);
                if(returnVals == 0)
                {
                    cout << "\nRecord added successfully.";
                }
                
                menuSelection = 0;
                break;
                
                
            case 2:

                cout << "\nModifying existing records address...\n\nPlease enter the account number whose address you want to change: ";
                cin >> acctnum;
                while(cin.fail())
                {
                    cout << "\nInvalid entry. Please enter a number.";
                    cin.clear();
                    cin.ignore(50,'\n');
                    cin >> acctnum;
                }
                cin.ignore(50,'\n');

                getaddress(address,addrSize);
                cin.ignore(50,'\n');
                returnVals = bankList.modifyRecord(acctnum,address);
                
                if(returnVals != -1)
                {
                    cout << "\n" << returnVals << " record(s) modified successfully.";
                }
                else
                {
                    cout << "Specified record doesn't exist.\n";
                }
                menuSelection = 0;
            

                break;
                
                
            case 3:
            
                cout << "\nPrinting record information...\n\nPlease enter the account number to print information from: ";
                cin >> acctnum;
                while(cin.fail())
                {
                    cout << "\nInvalid entry. Please enter a number.";
                    cin.clear();
                    cin.ignore(50,'\n');
                    cin >> acctnum;
                }
                cin.ignore(50,'\n');
                
                returnVals = bankList.printRecord(acctnum);
                menuSelection = 0;
               
               if(returnVals == -1) 
                {
                    cout << "Specified record doesn't exist.\n";
                }
            
                break;
                
                
            case 4:
                
                cout << "\nPrinting all record information...\n";
                cout << bankList;
                menuSelection = 0;
                
                break;
                
                
            case 5:
                cout << "\nDeleting existing record...\n\nPlease enter the account number to delete: ";
                cin >> acctnum;
                while(cin.fail())
                {
                    cout << "\nInvalid entry. Please enter a number.";
                    cin.clear();
                    cin.ignore(50,'\n');
                    cin >> acctnum;
                }
                cin.ignore(50,'\n');
                
                returnVals = bankList.deleteRecord(acctnum);
                if(returnVals != -1)
                {
                    cout << "\n" << returnVals << " record(s) deleted successfully.\n";
                }
               
                else
                {
                    cout << "The entered account number doesn't exist or the list is empty.\n";
                }
                
                menuSelection = 0;

                break;

            case 6:
                cout << "\nReversing list...\n";
                bankList.reverse();
                menuSelection = 0;
                
                break;
                
            case 7:
                cout << "\nQuitting program...\n";
                quitInput = 1;
                menuSelection = 0;
                
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
    
    #ifdef DEBUGMODE
        cout << "\n\n***DEBUG***\n    Function name: getaddress\n    parameters passed:\nchar Address[]: " >> address >> "\nint Size: " >> size >> "\n***********\n\n";
    #endif
    
    
    i=0;
    cout << "\nPlease enter the address of the account holder (fewer than 80 characters)\nType '$' (US dollar sign, no quotes) to complete address entry\n";
    do
    {
        addressCharVal = cin.get();
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

void readAddress(char address [], ifstream& buffer)
{
    int addressCharVal, i=0, size = 80;
    char addressChar;

    #ifdef DEBUGMODE
        cout << "\n\n***DEBUG***\n    Function name:readAddress\nParameters:\nchar address[]\nFILE * buffer\n***********\n\n";
    #endif
 
    do
    {
        addressCharVal = buffer.get();
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

void writeAddress(char address [], ofstream& buffer)
{
    int terminateCharVal, charWrittenVal, i = 0;
    char charWritten, terminateChar = '$';
    
    terminateCharVal = (int) terminateChar;
    
    #ifdef DEBUGMODE
        cout << "\n\n***DEBUG***\n    Function name:writeAddress\nParameters:\nchar address[]\nFILE * buffer\n***********\n\n";
    #endif
    
    do
    {
        charWrittenVal = address[i];
        buffer.put(address[i]);
        charWritten = (char) charWrittenVal;
        i++;
    }
    while(charWritten != '\0' && i < 79);
    buffer.put(terminateChar);
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
    #ifdef DEBUGMODE
        cout << "\n\n***DEBUG***\n    Function name:readfile\nParameters:\nstruct record ** startAddr\nchar addr[]\n***********\n\n";
    #endif
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
    #ifdef DEBUGMODE
        cout << "\n\n***DEBUG***\n    Function name:writefile\nParameters:\nstruct record * head\nchar addr[]\n***********\n\n";
    #endif
}


/*********************************
//
// Function name: addRecordDebug
//
// Description:   checks debugmode state, prints debug messages if appropriate for addRecord method
//
// Parameters:    int acctNo             : the account number, key to add to the db
//                string name            : the name of the associated account holder
//                char address[]         : the address of the associated account holder
//                int yearofbirth        : the year of birth of the associated account holder
//
// Return values:  none
//
//*******************************/

void addRecordDebug(int acctNo, string name, char address[],int yearofbirth)
{
    #ifdef DEBUGMODE
           cout << "\n\n***DEBUG***\n    Function name: addRecord\n    parameters passed:\n List address: \n Name: "<< name <<" Account number: "<< acctNo <<"\n Address: "<< address << "\n Year of Birth: "<< yearofbirth <<"\n***********\n\n";
    #endif
}

/*********************************
//
// Function name: printRecordDebug
//
// Description:   checks debugmode state, prints debug messages if appropriate for printRecord method
//
// Parameters:    int acctNo           : The account number, key of the record to print
//
// Return values:  none
//
//*******************************/

void printRecordDebug(int acctNo)
{
    #ifdef DEBUGMODE
        cout << "\n\n***DEBUG***\n    Function name: printRecord\n    parameters passed:\n List start address: \n Account number: "<< acctNo <<"\n***********\n\n";
    #endif
}

/*********************************
//
// Function name: modifyRecordDebug
//
// Description:   checks debugmode state, prints debug messages if appropriate for modifyRecord method
//
// Parameters:    int acctNo           : the account number, key of the record to modify
//                char address[]       : the new address that will replace the existing address in the record
//
// Return values:  none
//
//*******************************/

void modifyRecordDebug(int acctNo, char address[])
{
    #ifdef DEBUGMODE
        cout << "\n\n***DEBUG***\n    Function name: modifyRecord \n    parameters passed:\n List start address: \n Account number: "<< acctNo <<"\n Address: "<< address <<"\n***********\n\n";
    #endif
}

/*********************************
//
// Function name: printAllRecordsDebug
//
// Description:   checks debugmode state, prints debug messages if appropriate for printAllRecords method
//
// Parameters:    none
//
// Return values:  none
//
//*******************************/

void printAllRecordsDebug()
{
    #ifdef DEBUGMODE
        cout << "\n\n***DEBUG***\n    Function name: printAllRecords\n    parameters passed:\n List start address: \n***********\n\n";
    #endif
}

/*********************************
//
// Function name: deleteRecordDebug
//
// Description:   checks debugmode state, prints debug messages if appropriate for deleteRecord method
//
// Parameters:    int acctNo            : the account number, key of record to delete
//
// Return values:  none
//
//*******************************/

void deleteRecordDebug(int acctNo)
{
    #ifdef DEBUGMODE
        cout << "\n\n***DEBUG***\n    Function name:deleteRecord\n    parameters passed:\n List address: \n Account number: "<< acctNo <<"\n***********\n\n";
    #endif
        
}

/*********************************
//
// Function name: reverseDebug
//
// Description:   Prints the debug information for the reverse function
//
// Parameters:    none
//
// Return values:  none
//
//*******************************/
void reverseDebug()
{
    cout << "\n\n***DEBUG***\n    Function name:reverse\n    parameters passed:\n record pointer: \n\n***********\n\n";
}

/*********************************
//
// Function name: emptyListPrint
//
// Description:   Prints the empty list message to the user.
//
// Parameters:    none
//
// Return values:  none
//
//*******************************/

void emptyListPrint()
{
    #ifdef DEBUGMODE
        cout << "\n\n***DEBUG***\n    Function name:emptyListPrint\nParameters:\nNone\n***********\n\n";
    #endif

    cout << "\nThe list is empty.\n";
}
