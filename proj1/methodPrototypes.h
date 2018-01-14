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
// File:        methodPrototypes.h
//
// Description: This file contains the user defined prototypes for Project 1
//
//*******************************/

void addRecordDebug(struct record **, int , char [],char [],int);
void printRecordDebug(struct record *, int);
void modifyRecordDebug(struct record *, int, char []);
void printAllRecordsDebug(struct record *);
void deleteRecordDebug(struct record **, int);
void readfileDebug();
void writefileDebug();
void printContents(struct record);
int errorHandle(FILE *);
void readAddress(char [], FILE *);
void writeAddress(char [], FILE *);
void getaddress(char [], int);

