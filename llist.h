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
// File:        llist.h
//
// Description: llist header containing the class definition of the llist class.
//
//*******************************/

#ifndef LLIST_H
#define LLIST_H

#include "record.h"
using namespace std;

class llist
{
    private:
        record *    start;
        string      filename;
        int         readfile(string);
        int         writefile(string);
        record *    reverse(record *);
        void        cleanup();

    public:
        llist();
        llist(string);
        ~llist();
        int addRecord (int, string,char [ ],int);
        int printRecord (int);
        int modifyRecord ( int, char [ ]);
        void printAll();
        int deleteRecord(int);
        void reverse();
        friend ostream& operator<<(ostream&, llist&);
};


#endif    // LLIST_H

