#include "ArraySort.h"
namespace NP_ARRAYSORT
{
	//-------------------------------------------------------------------------
	//    function:		strangeSort(Comparable ** array, int fromIndex, int toIndex)
	//    description:	Uses quicksort if it's more than 4 items and insertion sort
	//					otherwise.
	//    
	//    Input:		
	// 
	//    Called By:	strangesort
	// 
	//    Parameters:	Comparable ** array, int fromIndex, int toIndex
	//    Returns:      int
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	//			4/28/17	NP	Appended to version 1.0
	// ------------------------------------------------------------------------
	void strangeSort(Comparable ** arr, int fromIndex, int toIndex) {
		if (fromIndex < toIndex) {
			// SortFirstMiddleLast(arr, fromIndex, (fromIndex + toIndex) / 2, toIndex);
			int position = partition(arr, fromIndex, toIndex);
			strangeSort(arr, fromIndex, position - 1);
			strangeSort(arr, position + 1, toIndex);
		}
		// else if (fromIndex < toIndex) {
			// insertionSort(arr, fromIndex, toIndex);
		//}
	}

 // ------------------------------------------------------------------------
	//    function:		partition(Comparable ** array, int fromIndex, int toIndex)
	//    description:	partitions and partially sorts things for quicksort.
	//    
	//    Input:		
	// 
	//    Called By:	strangesort
	// 
	//    Parameters:	Comparable ** array, int fromIndex, int toIndex
	//    Returns:      int
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	//			4/28/17	NP	Appended to version 1.0
	// ------------------------------------------------------------------------	
	int partition(Comparable ** array, int fromIndex, int toIndex) {

		int smallIndex = fromIndex - 1;

		Comparable * pivot = array[toIndex];

		for (int k = fromIndex; k < toIndex; k++) {
			if (*array[k] <= *pivot) {
				smallIndex++;
				indexSwap(array, k, smallIndex);
			}
		}

		indexSwap(array, toIndex, smallIndex + 1);
		return smallIndex + 1;
	}

 // ------------------------------------------------------------------------
	//    function:		SortFirstMiddleLast
	//    description:	Sort the three items
	//    
	//    Called By:	all sorting algs
	// 
	//    Parameters:	Comparable ** array, int loIndex, int midIndex, 
	//					int hiIndex
	// 
	//    Returns:          void 
	//
	//    History Log:
	//			4/27/17  NP  completed version 1.0
	// ------------------------------------------------------------------------	
	void SortFirstMiddleLast(
		Comparable ** array,
		int loIndex, int midIndex,
		int hiIndex
	)
	{
		Comparable * low = array[loIndex];
		Comparable * mid = array[midIndex];
		Comparable * hi = array[hiIndex];

		while ((*low > *mid) || (*mid > *hi)) {
			if (*low > *mid)
				indexSwap(array, loIndex, midIndex);
			else if (*mid > *hi)
				indexSwap(array, midIndex, hiIndex);
			else if (*low > *hi)
				indexSwap(array, loIndex, hiIndex);
			low = array[loIndex];
			mid = array[midIndex];
			hi = array[hiIndex];
		}
	}

 // ------------------------------------------------------------------------
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
	// ------------------------------------------------------------------------	
	void indexSwap(Comparable ** array, int index1, int index2) {
		Comparable * tmp = array[index1];
		array[index1] = array[index2];
		array[index2] = tmp;
	}

 // ------------------------------------------------------------------------
	//    function:		insertionSort(Comparable ** array, int fromIndex, 
	//					int toIndex)
	//    description:	sorts a list of comparables using 
	//					insertion sort algorithm
	//    
	//    Input:		
	// 
	//    Called By:	strangesort
	// 
	//    Parameters:	Comparable ** array, int fromIndex, int toInde
	//    Returns:      void 
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	//			4/28/17	NP	Appended to version 1.0
	// ------------------------------------------------------------------------	
	void insertionSort(Comparable ** array, int fromIndex, int toIndex)
	{
		for (int cursor = fromIndex; cursor < toIndex; cursor++) {
			int secondCursor = cursor - 1;
			Comparable * temp = array[cursor];

			while (secondCursor >= 0 && *temp < *array[secondCursor]) {
				*array[secondCursor + 1] = *array[secondCursor];
				secondCursor--;
			}

			*array[secondCursor + 1] = *temp;
		}
	}

 // ------------------------------------------------------------------------
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
	// ------------------------------------------------------------------------	
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

 // ------------------------------------------------------------------------
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
	// ------------------------------------------------------------------------	
	void printArray(ostream & sout, Comparable **array, int len)
	{
		for (int i = 0; i < len; i++)
		{
			array[i]->print(sout);
			if (i + 1 < len)
				sout << ",\n";
		}

		sout << endl;
	}
}

