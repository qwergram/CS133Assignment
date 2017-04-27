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