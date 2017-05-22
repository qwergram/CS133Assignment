# [Circular Doubly Linked List](http://faculty.edcc.edu//paul.bladek/CS133/p2.htm)

(scroll down to see submission)

Created by [Paul Bladek]()

In class, you were given an implementation of a linked list. Your task is to now modify that code to turn it into a doubly-linked circular list, and to test your new creation. A doubly-linked list is made up of nodes that contain a reference to the previous node as well as the next node--allowing for traversal in either direction.

A circular doubly-linked list has the next reference of the last node refer to the first node (instead of null), and has the previous reference of the first node refer to the last node (instead of null)--thus making a circle (you will need to make your own design decisions about what to do with a list with only one node).


Your first step should be to make sure that the starting code (the Simple Doubly-linked list Class) works, and that all declared methods are implemented as described on the given web page. You should also make this be a Template class, (CircularDoublyLinkedList<T>) instead of having just a typedef for datatype. Note: the compiler might complain when you are using templates with nested class. You can inform the compiler of what you are trying to do by using the keyword typename, as in 
```cpp
  template<class T>
  typename list<T>::iterator listt<T>::iterator::operator++(int)
```
This new class should contain all of the same public methods as in the given class, but should be re-written to take advantage of the capabilities of the new construction. Also, since you will now be using this as a base class, you will need to determine which methods should be virtual.

Many methods will require only minor modification. Others will require more thinking. You may wish to draw diagrams to help you through the planning process.

When this class is fully tested, you will need to write the definition for a new queue<T> class which protectedly inherits from your Circular Doubly-Linked List class.  It should contain only:

constructors to match up with all of the constructors in the Circular Doubly-Linked List class.
  - a destructor (`~CDLL`)
  - `getSize()`
  - `begin()`
  - `end()`
  - `empty()`
  - `release()`
  - `void push(T& element)`
  - `T pop()`
 
The structure of the underlying list must stay the same (a circular doubly-linked list). An iterator should still work exactly the same way. If methods act the same as the parent-class method, they should merely call the parent-class method (for constructors, use the initialization list).

You will also need to write a program which is a test driver for the classes--that is, a main that tests the methods of both classes. It should contain appropriate try/catch blocks and test all of the methods of both classes, either directly or indirectly. Protected or private inheritance makes it hard to test virtual functions, so you do not need to worry about this here. You may use any class you choose that makes sense as the data implementation (`string` is an easy choice).

# Work

Files can be downloaded as a zip [here](https://github.com/qwergram/CS133Assignment/archive/master.zip).
Project two can be found under a folder called `Project2`. The tests for project 2 can be found under a 
folder named `Project2Tests`. Opening up `CS133Assignment1.sln` will automatically load the correct projects
in a debugging environment.

## Files

<table>
<tr>
<th>Title</th>
<th>Raw</th>
<th>Source</th>
<th>Description</th>
</tr>

<tr>
<td>Sample Executable</td>
<td><a href="https://github.com/qwergram/CS133Assignment/raw/master/Project2/sample.exe">Raw</a></td>
<td><a href="https://github.com/qwergram/CS133Assignment/blob/master/Project2/sample.exe">Source</td>
<td>Sample executable with <code>main.cpp</code> as the driver</td>
</tr>

<tr>
<td><code>main.cpp</code></td>
<td><a href="https://github.com/qwergram/CS133Assignment/blob/master/Project2/main.cpp">Raw</a></td>
<td><a href="https://raw.githubusercontent.com/qwergram/CS133Assignment/master/Project2/main.cpp">Source</td>
<td>The driver showcasing some abilities of <code>Queue</code> and <code>CDLL</code></td>
</tr>

<tr>
<td><code>list.h</code></td>
<td><a href="https://raw.githubusercontent.com/qwergram/CS133Assignment/master/Project2/list.h">Raw</a></td>
<td><a href="https://github.com/qwergram/CS133Assignment/blob/master/Project2/list.h">Source</td>
<td>Header containing all declarations for <code>CDLL</code></td>
</tr>

<tr>
<td><code>list.cpp</code></td>
<td><a href="https://raw.githubusercontent.com/qwergram/CS133Assignment/master/Project2/list.cpp">Raw</a></td>
<td><a href="https://github.com/qwergram/CS133Assignment/blob/master/Project2/list.cpp">Source</td>
<td>Source file containing non-inline definitions for <code>CDLL</code></td>
</tr>

<tr>
<td><code>queue.h</code></td>
<td><a href="https://raw.githubusercontent.com/qwergram/CS133Assignment/master/Project2/queue.h">Raw</a></td>
<td><a href="https://github.com/qwergram/CS133Assignment/blob/master/Project2/queue.h">Source</td>
<td>Header containing all declarations and definitions for <code>Queue</code></td>
</tr>

<tr>
<td><code>queue.cpp</code></td>
<td><a href="https://raw.githubusercontent.com/qwergram/CS133Assignment/master/Project2/queue.cpp">Raw</a></td>
<td><a href="https://github.com/qwergram/CS133Assignment/blob/master/Project2/queue.cpp">Source</td>
<td>Source file containing non-inline definitions for <code>Queue</code></td>
</tr>

<tr>
<td><code>public_queue.h</code></td>
<td><a href="https://raw.githubusercontent.com/qwergram/CS133Assignment/master/Project2/public_queue.h">Raw</a></td>
<td><a href="https://github.com/qwergram/CS133Assignment/blob/master/Project2/public_queue.h">Source</td>
<td>Header containing all declarations for <code>Queue</code> with <code>public</code> inheritance from <code>CDLL</code></td>
</tr>

<tr>
<td><code>listTests.cpp</code></td>
<td><a href="https://raw.githubusercontent.com/qwergram/CS133Assignment/master/Project2Tests/listTests.cpp">Raw</a></td>
<td><a href="https://github.com/qwergram/CS133Assignment/blob/master/Project2Tests/listTests.cpp">Source</td>
<td>Source file containing comprehensive tests for both <code>Queue</code> and <code>CDLL</code></td>
</tr>

</table>

## Approved Design Changes

- `tail()` and `Head()` are methods
- `front()` and `back()` will throw `runtime` exceptions
- `begin()` and `end()` will never throw `runtime` exceptions
- Copy Constructor will never throw exceptions
- Iterator constructors are inclusive bounds in same order

## Sample Output
`Sample.exe` will return the following:

```
mylist: [X, X, X]
mylist2: []
mylist3: [X, X, X]
mylist4: [X, X, X]
Z
mylist: [Y, X, X, X]
Y X
mylist: Y X X X
mylist[1] = 'N';
mylist: [Y, N, X, X]
mylist: []
mylist2: [Y, X, X, X]
myqueue: [X, X, X]
myqueue2: []
myqueue3: [X, X, X]
myqueue4: [X, X, X]
X
myqueue: [X, X, Y, Z]
X X
myqueue: []
myqueue2: [X, X, Y, Z]
```
Note that mentions of all `myqueue`s are publicly inherited from `CDLL`. 

## Test Plan

### Driver tests
The driver currently shows behavior and implementation of either `Queue` and `CDLL`.

### Unit Tests
Additional `unittests` can be found [here](https://github.com/qwergram/CS133Assignment/blob/master/Project2Tests/listTests.cpp).
There are a total of `123` unit tests which all pass.

![](https://github.com/qwergram/CS133Assignment/blob/master/Project2Tests/tests.png?raw=true)