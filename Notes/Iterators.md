# Iterators
Code stolen from [Paul Bladek](http://faculty.edcc.edu//paul.bladek/CS133/it_cpp.htm).

# Modified Example

## Code

Modified to use more explicit variable names. Also includes explanations in comments.

```cpp
#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
using namespace std;

//-----------------------------------------------------------------------------
// Using Iterators
//-----------------------------------------------------------------------------
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

// Thank you Mr. Bladek!
```

## Output

```
this is a string
a c-type string
this
gnirts epyt-c a
```

# Explanation

## First For Loop

Let's look at the first for loop:

```cpp
for (
	string_iterator = stringInstance.begin(); 
	string_iterator != stringInstance.end(); 
	string_iterator++
) {
	character_vector.push_back(*string_iterator);
}
```

Here, we use a string iterator to go through our string.
We assign the string iterator to be the string object's `.begin()`
method, which puts us in the beginning.

Rather than iterate until `stringInstance.length - 1`, we iterate until
the iterator reaches `stringInstance.end()`. The `iterator++` operator
has been overloaded, which allows us to call it, making the for loop
very simple.

Inside the for loop, we call the [`list::push_back`](http://www.cplusplus.com/reference/list/list/push_back/)
method, which simply appends something to the end of the list.

## Second For Loop

In the last loop, we just added to our list of `char`s using `iterator pointers`.

```cpp
for (
	charlist_iterator = character_vector.begin(); 
	charlist_iterator != character_vector.end(); 
	charlist_iterator++
) {
	cout.put(*charlist_iterator);
}
```

Similiarly to how we iterated through our `string` object, we can iterate through our `character_vector`
using our `charlist_iterator`. This time, instead of `push_back`ing to a list or vector, we're just asking
`cout` to `put` the `char` stored in the list onto the terminal.

## Third For Loop

Instead of using iterators, we're going to use a pointer.

```cpp
for (
	charArrayPointer = charArray; 
	*charArrayPointer != '\0'; 
	charArrayPointer++
) {
	character_vector.push_back(*charArrayPointer);
}
```

This pointer starts at the address of our `charArray`, but like our iterators, we don't iterate to the 
length of the string; we iterate until the `char` pointed at with `charArrayPointer` is `'\0'`.
Like the first for loop, we just `push_back` to our `character_vector`.

## Fifth For Loop

This is much like our first loop, the only difference is when it stops.

```cpp
for (
	string_iterator = stringInstance.begin(); 
	string_iterator != stringInstance.end() && !isspace(*string_iterator); 
	string_iterator++
) {
	cout.put(*string_iterator);
}
```

In our first for loop, the condition for stopping was if the iterator reached the end (`string_iterator != stringInstance.end()`).
This time, we're also checking if the char _is not_ a space (`!isspace(*string_iterator)`) and terminate the loop
only if both (`&&`) evaluate to true. This statement can be also thought as:
> Terminate the loop if we reach a space OR we reach the end of `string`.

## Last For Loop

```cpp
for (
	reverse_charlist_iterator = character_vector.rbegin(); 
	reverse_charlist_iterator != character_vector.rend(); 
	reverse_charlist_iterator++
) {
	cout.put(*reverse_charlist_iterator);
}
```

This time, we use a `list<char>::reverse_iterator` called `reverse_charlist_iterator`. It has all the
same properties as the iterator, but this time it iterates through our `character_vector` in reverse
order.