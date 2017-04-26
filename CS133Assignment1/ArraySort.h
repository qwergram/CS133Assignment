#ifndef ARRAYSORT_H
#define ARRAYSORT_H
#include <iostream>
#include "DateTime.h"
using namespace std;
using namespace NP_DATETIME;
//----------------------------------------------------------------------------
// One of two choices for format of these function
// This set uses pointers in the way that the STL uses iterators
//----------------------------------------------------------------------------
namespace NP_ARRAYSORT
{
	void quickSort(Comparable** array, int fromIndex, int toIndex);
	int partition(Comparable** array, int fromIndex, int toIndex);
	void SortFirstMiddleLast(Comparable** array, int fromIndex,
		int midIndex, int toIndex);
	void swap(Comparable ** array, int index1, int index2);
	void insertionSort(Comparable** array, int fromIndex, int toIndex);
	void safeRead(istream& sin, Comparable* d, const char* prompt);
	void printArray(ostream & sout, Comparable **array, int size);
}
#endif