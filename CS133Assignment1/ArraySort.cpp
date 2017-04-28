#include "ArraySort.h"
namespace NP_ARRAYSORT
{
	void quickSort(Comparable ** array, int fromIndex, int toIndex)
	{
		if (fromIndex < toIndex) {
			int position = partition(array, fromIndex, toIndex);
			quickSort(array, fromIndex, position - 1);
			quickSort(array, position + 1, toIndex);
		}
	}

	int partition(Comparable ** array, int fromIndex, int toIndex)
	{
		Comparable * pivot = array[toIndex];
		int small = fromIndex - 1;
		for (int cursor = fromIndex; cursor < toIndex; cursor++)
			if (array[cursor] <= pivot)
				swap(array, small++, cursor);
		swap(array, toIndex, ++small);
		return small;
	}

	void swap(Comparable ** array, int index1, int index2)
	{
		Comparable * tmp = array[index1];
		array[index1] = array[index2];
		array[index2] = tmp;
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
		while(!sin)
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
	void printArray(ostream & sout, Comparable **a, int size)
	{
		for(int i = 0; i < size; i++)
		{
			a[i]->print(sout);
			sout << endl;
		}
		sout << endl;
	}
}

