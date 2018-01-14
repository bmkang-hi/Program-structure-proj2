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
// File:        record.h
//
// Description: This file contains the definition for the record structure used in the bank database application.
//
//*******************************/

#ifndef RECORD_H
#define RECORD_H

#include <string>
using namespace std;

struct record
{
    int                accountno;
    string             name;
    char               address[80];
    int                yearofbirth;
    struct record*     next;
};

#endif    // RECORD_H

