#include "DateTime.h"
#include <iostream>
#include <string>
using namespace std;
using namespace NP_DATETIME;

int main(void)
{
	// Remember Date is 0 based!
	Date date1;
	CTime time1;
	
	cout << "date: ";
	cin >> date1;
	cout << endl << date1 << endl;
	date1;

	cout << "time: ";
	cin >> time1;
	cout << endl << time1 << endl;
	time1;
}