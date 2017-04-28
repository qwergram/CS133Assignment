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
void sortCTimesShow();
void sortDatesShow();
void sortDateTimesShow();

// .cpp

void sortCTimesShow() {
	cout << "For our first act, we're going to sort some times in our very own CTime class!" << endl;
	cout << "How many CTimes would you like to sort? ";
	
	short items;
	
	
	cin >> items;
	if (items <= 1) {
		cout << "Well it wouldn't be much of a show if I didn't sort at least 2 things, right? We'll sort 2 things for now." << endl;
		items = 2;
	}
	else {
		cout << items << " CTimes it is!" << endl;
	}

	cout << "Now if you could type these times in yourself..." << endl;

	Comparable ** timesToSort = nullptr;
	* timesToSort = new CTime[items];

	for (short tIndex = 0; tIndex < items; tIndex++) {
		cout << "CTime " << tIndex + 1 << " [hh:mm:ss]: ";
		CTime thisTime;
		cin >> thisTime;
		cout << "You entered: " << thisTime << endl;
		timesToSort[tIndex] = &thisTime;
	}

	cout << "Awesome! Now that we have " << items << " different CTimes, let me present them in the order you entered..." << endl;
	for (short tIndex = 0; tIndex < items; tIndex++) {
		cout << dynamic_cast<CTime&>(*timesToSort[tIndex]) << ", ";
	}
	cout << " ... and that's all of them! Now abracadraba, quicksort away! Here's the sorted list!" << endl;

	quickSort(timesToSort, 0, items);
	for (short tIndex = 0; tIndex < items; tIndex++) {
		cout << dynamic_cast<CTime&>(*timesToSort[tIndex]) << ", ";
	}
	char ignoreme;
	cin >> ignoreme;
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

	cout << "We have quite a treat for you today! We're going to sort things for you in C++!" << endl;

	sortCTimesShow();
	
	Date date1;
	CTime time1;
	DateTime datetime1;

	/*
	cout << "date [dd/mm/yyyy]: ";
	cin >> date1;
	cout << endl << date1 << endl;

	cout << "time [hh:mm:ss]: ";
	cin >> time1;
	cout << endl << time1 << endl;
	//*/

	cout << "datetime [dd/mm/yyyy hh:mm:ss]: ";
	cin >> datetime1;
	cout << endl << datetime1 << endl;
	datetime1;
}