// Norton James Penrga (CS133)
// Quiz 3

#include <iostream>
#include <cstdlib>
#include <string>
#include <list>

using namespace std;

// main.h

list<string> split(const string & phrase, char delimiter = ' ');
int main();

// main.cpp

list<string> split(const string & phrase, char delimiter)
{
	list<string> toReturn;
	string thisWord;
	for (int cursor = 0; cursor < phrase.length(); cursor++) {
		if (phrase[cursor] == delimiter) {
			
			// Check if there's something in thisWord
			if (thisWord.length() > 0)
				toReturn.push_back(thisWord);
			
			// reset thisWord
			thisWord = "";
		}
		else
			thisWord.push_back(phrase[cursor]);
	}

	// Dirty solution
	if (thisWord.length() > 0)
		toReturn.push_back(thisWord);

	return toReturn;
}


int main() {
	string string1 = "Hello world";
	string string2 = "Hello     world, \t my name is          Norton       Pengra";
	string string3 = "Hello     world, my     name is          Norton       Pengra";

	// Use Breakpoints to look at contents of "test" each time.
	list<string> test = split(string1);
	cout << "ORIGINAL: " << string1 << endl;
	cout << "SPLIT: ";
	for (auto thing : test) {
		cout << '"' << thing << "\", ";
	}
	cout << endl;
	
	test = split(string2);
	cout << "ORIGINAL: " << string2 << endl;
	cout << "SPLIT: ";
	for (auto thing : test) {
		cout << '"' << thing << "\", ";
	}
	cout << endl;

	test = split(string3);
	cout << "ORIGINAL: " << string3 << endl;
	cout << "SPLIT: ";
	for (auto thing : test) {
		cout << '"' << thing << "\", ";
	}
	cout << endl;
}