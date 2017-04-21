# [Address of functions](http://faculty.edcc.edu//paul.bladek/CS133/func_cpp.htm)

```cpp
//-------------------------------------------------------------
// Pointer Problems v1.0
// file: func.cpp
// by Paul Bladek
// April 4, 2002
// compiled under MS Visual C++ 6.0
// A sample program illustrating the problem of
// taking the address of an overloaded function
//-------------------------------------------------------------
#include 
using namespace std;

// two versions of the same function
void f1(int x);
void f1(double x);

int main(void)
{
	f1(3);		// call the int version
	f1(3.2);	// call the double version
//	cout << f1 << endl;		// can't differentiate
	void (*fp)(double) = f1;// assign fp to the double version
	(*fp)(1.2);	// call the double version with a double
	(*fp)(2);	// call the double version with an int
	cin.get();
	return 0;
}

//-------------------------------------------------------------
//  sample function taking in an int
//-------------------------------------------------------------
void f1(int x)
{
	cout << "f1(int)" << endl;
} 

//-------------------------------------------------------------
//  overloaded version taking in a double
//-------------------------------------------------------------
void f1(double x)
{
	cout << "f1(double)" << endl;
} 
```
