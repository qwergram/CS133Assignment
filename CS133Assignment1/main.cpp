#include "DateTime.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
using namespace std;
using namespace std;
using namespace NP_DATETIME;

int main(void)
{
	// Declarations
	string stringInstance = "this is a string";
	const char* charArray = "a c-type string";

	// Pointer Declaration
	const char* charArrayPointer;

	// Iteration Declarations
	list<char> character_vector;
	string::const_iterator string_iterator;
	list<char>::const_iterator charlist_iterator;
	list<char>::reverse_iterator reverse_charlist_iterator;

	// First for loop
	for (
		string_iterator = stringInstance.begin();
		string_iterator != stringInstance.end();
		string_iterator++
		) {
		character_vector.push_back(*string_iterator);
	}

	// Second for loop
	for (
		charlist_iterator = character_vector.begin();
		charlist_iterator != character_vector.end();
		charlist_iterator++
		) {
		cout.put(*charlist_iterator);
	}

	cout << endl;
	character_vector.clear();

	// Third for loop
	for (
		charArrayPointer = charArray;
		*charArrayPointer != '\0';
		charArrayPointer++
		) {
		character_vector.push_back(*charArrayPointer);
	}

	// Fourth for loop
	for (
		charlist_iterator = character_vector.begin();
		charlist_iterator != character_vector.end();
		charlist_iterator++
		) {
		cout.put(*charlist_iterator);
	}

	cout << endl;

	// Fifth for loop
	for (
		string_iterator = stringInstance.begin();
		string_iterator != stringInstance.end() && !isspace(*string_iterator);
		string_iterator++
		) {
		cout.put(*string_iterator);
	}

	cout << endl;

	// Last for loop
	for (
		reverse_charlist_iterator = character_vector.rbegin();
		reverse_charlist_iterator != character_vector.rend();
		reverse_charlist_iterator++
		) {
		cout.put(*reverse_charlist_iterator);
	}

	cout << endl;

	cin.ignore(FILENAME_MAX, '\n');
	return EXIT_SUCCESS;
}