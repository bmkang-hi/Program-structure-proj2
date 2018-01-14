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
// File:        record.h
//
// Description: This file contains the definition for the record structure used in the bank database application.
//
//*******************************/

 struct record
 {
     int                accountno;
     char               name[25];
     char               address[80];
     int                yearofbirth;
     struct record*     next;
 };
