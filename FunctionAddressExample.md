# [Address of functions](http://faculty.edcc.edu//paul.bladek/CS133/func_cpp.htm)

Refering to methods and functions with their address and calling them.

## Code Snippet: (Courtesy of Bladek)

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
#include <iostream>
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

The output of the program above looks like this:

```
f1(int)
f1(double)
f1(double)
f1(double)
```

## Explanation

In the code snippet above, one function with two signatures are 
declared and defined, namely `f1(double)` and `f1(int)`. 

Later, a pointer is declared in a strange way:
```cpp 
void (*fp)(double) = f1;
```
A pointer `fp` points to the address of `f1`, specifically
the one that takes a `double` as its parameter.

> Note that if the line pointer declaration line were replaced with:
> ```cpp 
> void (*fp)(float) = f1;
> ```
> you would recieve a compilation error that looks like:
> ```
> In function 'int main()':
> 	13:22: error: no matches converting function 'f1' to type 'void (*)(float)'
> 	6:6: note: candidates are: void f1(double)
> 	5:6: note:                 void f1(int)
> ```

Since the address of `fp` is the `f1(double)`, it doesn't matter whether you put an `int`
or a `double` into it, it will always cast the input to a double and run `f1(double)`.

Additionally, you could run any of the following lines:
```cpp
(*fp)(3.F);
(*fp)('A');
(*fp)(6L);
```

All of which would result in 
```
f1(double)
f1(double)
f1(double)
```

You'll start to run into problems when you try:
```cpp
f1("test");
```
because there's (at least no default) cast operator from `string` or `char *` to `double`.
This results in this compiler error:
```
In function 'int main()':
	17:24: error: cannot convert 'const char*' to 'double' in argument passing
```

That's it for this time,

&lt;/Pengra&gt;