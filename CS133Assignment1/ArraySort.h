#ifndef ARRAYSORT_H
#define ARRAYSORT_H
#include <iostream>
#include "DateTime.h"
using namespace std;
using namespace NP_DATETIME;
//-----------------------------------------------------------------------------
//    Title:            Array Sort Functions
//
//    Description:		This file contains the function declarations for sorting related things
//
//    Programmer:		Paul Bladek && Norton Pengra
//   
//    Date:             4/28/2017	
// 
//    Version:          1.0
//  
//    Environment:   Hardware: IBM Pentium  
//                   Software:  WinXP or later or .NET for execution;
//
//    Compiles under Microsoft C++ 2005
// 
//		void strangeSort
//		int partition
//		void SortFirstMiddleLast
//		void swap
//		void insertionSort
//		void safeRead
//		void printArray
//
//    History Log:
//      4/7/08  PB  completed version 1.0
//		4/28/17	NP	appended to version 1.0
//-----------------------------------------------------------------------------
namespace NP_ARRAYSORT
{
	void strangeSort(Comparable** array, int fromIndex, int toIndex);
	int partition(Comparable** array, int fromIndex, int toIndex);
	void SortFirstMiddleLast(Comparable** array, int fromIndex,
		int midIndex, int toIndex);
	void swap(Comparable ** array, int index1, int index2);
	void insertionSort(Comparable** array, int fromIndex, int toIndex);
	void safeRead(istream& sin, Comparable* d, const char* prompt);
	void printArray(ostream & sout, Comparable **array, int size);
}
#endif