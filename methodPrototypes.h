
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
// File:        methodPrototypes.h
//
// Description: This file contains the user defined prototypes for Project 2
//
//*******************************/

#ifndef METHODPROTOTYPES_H
#define METHODPROTOTYPES_H

using namespace std;

void addRecordDebug(int , string, char [],int);
void printRecordDebug(int);
void modifyRecordDebug(int, char []);
void printAllRecordsDebug();
void deleteRecordDebug(int);
void readfileDebug();
void writefileDebug();
void printContents(record);
void readAddress(char [], ifstream&);
void writeAddress(char [], ofstream&);
void getaddress(char [], int);
void emptyListPrint();
void reverseDebug();


#endif    // METHODPROTOTYPES_H

