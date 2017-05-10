#include "DateTime.h"
#include "ArraySort.h"
#include <iostream>
#include <string>
#include <list>
using namespace std;
using namespace NP_DATETIME;
using namespace NP_ARRAYSORT;

// .h

int main();
void showSortFunction();

// .cpp

void showSortFunction() {
	cout << "For our first act, we're going to sort some" 
		 << "times in our very own DateTime class!" << endl;
	cout << "How many DateTimes would you like to sort? ";
	
	short items;
	
	
	cin >> items;
	if (items <= 1) {
		cout << "Well it wouldn't be much of a show if I didn't sort at least 2 " 
			 << "things, right? We'll sort 2 things for now." << endl;
		items = 2;
	}
	else {
		cout << items << " DateTimes it is!" << endl;
	}

	cout << "Now if you could type these times in yourself..." << endl;

	Comparable ** timesToSort = nullptr;

	try {
		timesToSort = new Comparable *[items];
	}
	catch (bad_alloc e) {
		cout << "Oh no! something went wrong :(" << endl;
		cout << "Couldn't allocate the memory" << endl;
		return;
	}

	for (short index = 0; index < items; index++)
		timesToSort[index] = nullptr;

	for (short tIndex = 0; tIndex < items; tIndex++) {
		cout << "DateTime " << tIndex + 1 << " [dd/mm/yyyy hh:mm:ss]: ";
		DateTime thisTime;
		Comparable * thisTimeComparable = &thisTime;
		safeRead(cin, &thisTime, "");
		cout << "You entered: " << thisTime << endl;
		timesToSort[tIndex] = new DateTime(
			dynamic_cast<DateTime&>(*thisTimeComparable)
		);
	}

	cout << "Awesome! Now that we have " << items 
		 << " different DateTimes, let me present them in the" 
		 << " order you entered..." << endl << endl;
	
	printArray(cout, timesToSort, items);
	
	cout << endl << endl << " ... and that's all of them! "
		 << "Now abracadraba, quicksort away! Here's the sorted list!" 
		 << endl << endl;
	
	strangeSort(timesToSort, 0, items - 1);
	
	printArray(cout, timesToSort, items);
	cout << endl << endl;

	cout << "Now, using the same array, we will place Dates!" << endl;

	for (short tIndex = 0; tIndex < items; tIndex++) {
		cout << "Date " << tIndex + 1 << " [dd/mm/yyyy]: ";
		Date thisDate;
		Comparable * thisTimeComparable = &thisDate;
		safeRead(cin, &thisDate, "");
		cout << "You entered: " << thisDate << endl;
		timesToSort[tIndex] = new Date(dynamic_cast<Date&>(*thisTimeComparable));
	}
	
	cout << "Awesome! Now that we have " << items 
		 << " different Dates, let me present them in the order you entered..." 
		 << endl << endl;

	printArray(cout, timesToSort, items);

	cout << endl << endl 
		 << " ... and that's all of them! Now abracadraba, "
		 << "quicksort away! Here's the sorted list!" << endl << endl;

	strangeSort(timesToSort, 0, items - 1);

	printArray(cout, timesToSort, items);
	cout << endl << endl;
	cout << " ... For our last trick, we will dynamically clean your memory! " 
		 << endl << endl;
	
	// clean up memory
	for (int index = 0; index < items; index++) {
		delete timesToSort[index];
	}
	delete[] timesToSort;
	timesToSort = nullptr;
}

int main()
{
	string name;
	cout << "Hello! Welcome the magic sorting show! Please enter your name: ";
	cin >> name;
	
	if (name.length() <= 1) {
		cout << "no name, huh? I'll just call you Bill!" << endl;
		name = "Bill";
	}
	else {
		cout << "Hello, " << name << "!" << endl;
	}

	cout << "We have quite a treat for you today! "
		 << "We're going to sort things for you in C++!" << endl;

	showSortFunction();
	
	cout << "Thank you Seattle, you have been an amazing audience!" << endl;
	cout << "I have been your host, Norton Pengra and I will see you later!" 
		 << endl;
	
	char tmp;
	cin >> tmp;
}