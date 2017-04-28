#include "ArraySort.h"
namespace NP_ARRAYSORT
{

	void strangeSort(Comparable ** array, int fromIndex, int toIndex)
	{
		if (fromIndex + 4 < toIndex) {
			int position = partition(array, fromIndex, toIndex);
			strangeSort(array, fromIndex, position - 1);
			strangeSort(array, position + 1, toIndex);
		} else if (fromIndex < toIndex) {
			insertionSort(array, fromIndex, toIndex);
		}
	}

	int partition(Comparable ** array, int fromIndex, int toIndex)
	{
		Comparable * mid = array[toIndex];
		int small = fromIndex - 1;
		for (int index = fromIndex; index < toIndex; index++) {
			if (*array[index] <= *mid) {
				small++;
				swap(array, index, small);
			}
		}
		swap(array, toIndex, small + 1);
		return small + 1;
	}

	//-----------------------------------------------------------------------------
	//    function:		SortFirstMiddleLast
	//    description:	Sort the three items
	//    
	//    Called By:	all sorting algs
	// 
	//    Parameters:	Comparable ** array, int loIndex, int midIndex, int hiIndex
	// 
	//    Returns:          void 
	//
	//    History Log:
	//			4/27/17  NP  completed version 1.0
	// ----------------------------------------------------------------------------	
	void SortFirstMiddleLast(Comparable ** array, int loIndex, int midIndex, int hiIndex)
	{
		Comparable * low = array[loIndex];
		Comparable * mid = array[midIndex];
		Comparable * hi = array[hiIndex];
		while ((low > mid) || (mid > hi)) {
			if (low > mid) 
				swap(array, loIndex, midIndex);
			if (mid > hi)
				swap(array, midIndex, hiIndex);
			if (low > hi)
				swap(array, loIndex, hiIndex);
			low = array[loIndex];
			mid = array[midIndex];
			hi = array[hiIndex];
		}
	}

	//-----------------------------------------------------------------------------
	//    function:		swap
	//    description:	swaps two items in an array
	//    
	//    Input:		Comparable ** array, int index1, int index2
	// 
	//    Called By:	all sorting algs
	// 
	//    Parameters:	Comparable ** array, int index1, int index2
	// 
	//    Returns:          void 
	//
	//    History Log:
	//			4/27/17  NP  completed version 1.0
	// ----------------------------------------------------------------------------	
	void swap(Comparable ** array, int index1, int index2) {
		Comparable * tmp = array[index1];
		array[index1] = array[index2];
		array[index2] = tmp;
	}

	void insertionSort(Comparable ** array, int fromIndex, int toIndex)
	{
		if (fromIndex < 1)
			fromIndex = 1;

		for (int outerIndex = fromIndex; outerIndex < toIndex; outerIndex++) {
			int innerIndex = outerIndex - 1;
			Comparable * temp = array[outerIndex];

			while (innerIndex >= 0 && *temp < *array[innerIndex]) {
				array[innerIndex + 1] = array[innerIndex];
				innerIndex--;
			}

			array[innerIndex + 1] = temp;
		}
	}

	//-----------------------------------------------------------------------------
	//    function:		safeRead(istream& sin, Comparable* d, const char* re)
	//    description:	safely reads in a DateTime (d) from sin.
	//				Re-prompts and re-enters if input is invalid
	//    
	//    Input:		Comparable* d from sin
	// 
	//    Called By:	main
	// 
	//    Parameters:	istream& sin  -- the input stream
	//			Comparable* d -- pointer to the object input
	//			const char* prompt  -- prompt, if necessary
	// 
	//    Returns:          void 
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------	
	void safeRead(istream& sin, Comparable* d, const char* prompt)
	{
		const int BUFFERSIZE = 256;
		d->input(sin);
		while (!sin)
		{	// read in number--enter loop if fail
			sin.clear();		// clear fail
			sin.ignore(BUFFERSIZE, '\n');	// read past newline
			cout << prompt;  // re-prompt
			d->input(sin);
		}
		// read past newline once input succeeds
		sin.ignore(BUFFERSIZE, '\n');
	}

	//-----------------------------------------------------------------------------
	///    function:	void printArray(ostream & sout, Comparable **a, int size)
	///    description:	can print out an array of DateTime *
	// 
	//    Output:		Comparable* d sout
	//
	//    Called By:	main
	// 
	//    Parameters:	ostream& sout  -- the output stream
	//			Comparable** a -- array of pointers to the objects
	//			int size  -- number of elements in the array
	// 
	//    Returns:          void 
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------	
	void printArray(ostream & sout, Comparable **array, int len)
	{
		for (int i = 0; i < len; i++)
		{
			array[i]->print(sout);
			if (i + 1 < len)
				sout << ", ";
		}

		sout << endl;
	}
}

