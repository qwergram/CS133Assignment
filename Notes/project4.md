# Group Project: "RPN Programmable Calculator"

# Members

<table>
<tr>
<th>Member</th>
<th>Duties</th>
</tr>
<tr>
<td>Tabitha Roemish</td>
<td>QA Development, RPN Programmer Tester &amp; Documentation Lead</td>
</tr>
<tr>
<td>Cecilia Tong</td>
<td>QA Development Lead</td>
</tr>
<tr>
<td>Antonio Castelli</td>
<td>Team Mascot, Lead Developer</td>
</tr>
<tr>
<td>Norton Pengra</td>
<td>Testing, Project Scaffolding, House Cleaning</td>
</tr>
</table>

# Files

<table>
<tr>
    <th>File Name</th>
    <th>Source</th>
</tr>
<tr>
    <td><code>CalcDriver.cpp</code></td>
    <td><a href="https://github.com/qwergram/CS133Assignment/blob/Tabitha/RPNCalculator/CalcDriver.cpp">Source</a></td>
</tr>
<tr>
    <td><code>RPNCalc.h</code></td>
    <td><a href="https://github.com/qwergram/CS133Assignment/blob/Tabitha/RPNCalculator/RPNCalc.h">Source</a></td>
</tr>
<tr>
    <td><code>RPNCalcStart.cpp</code></td>
    <td><a href="https://github.com/qwergram/CS133Assignment/blob/Tabitha/RPNCalculator/RPNCalcStart.cpp">Source</a></td>
</tr>
<tr>
    <td><code>catch.hpp</code> [Testing Framework]</td>
    <td><a href="https://github.com/qwergram/CS133Assignment/blob/Tabitha/RPNCalculator/catch.hpp">Source</a></td>
</tr>
<tr>
    <td><code>RPN_UnitTests.cpp</code></td>
    <td><a href="https://github.com/qwergram/CS133Assignment/blob/Tabitha/RPNCalculator/RPN_UnitTests.cpp">Source</a></td>
</tr>
<tr>
    <td><code>RPNTestHelper.h</code></td>
    <td><a href="https://github.com/qwergram/CS133Assignment/blob/Tabitha/RPNCalculator/RPNTestHelper.h">Source</a></td>
</tr>
<tr>
    <td><code>Project Directory</code></td>
    <td><a href="https://github.com/qwergram/CS133Assignment/tree/Tabitha/RPNCalculator">Source</a></td>
</tr>
<tr>
    <td>Project Executable</td>
    <td><a href="https://github.com/qwergram/CS133Assignment/raw/Tabitha/RPNCalculator/RPNCalculator.exe">Source</a></td>
</tr>
<tr>
    <td>Standard Deviation Script</td>
    <td><a href="#">Source</a></td>
</tr>
</table>

# Testing

[![Build Status](https://travis-ci.org/qwergram/CS133Assignment.svg?branch=Tabitha)](https://travis-ci.org/qwergram/CS133Assignment)
[![Build status](https://ci.appveyor.com/api/projects/status/o3eopf6bs2o12t3c?svg=true)](https://ci.appveyor.com/project/qwergram/cs133assignment)

- [Pull Request](https://github.com/qwergram/CS133Assignment/pull/7)
- [Travis Test Results](https://travis-ci.org/qwergram/CS133Assignment/)
- [App Veyor Test Results](https://ci.appveyor.com/project/qwergram/cs133assignment)

# $10: Spot the bug

![](http://imgur.com/a8JgMuy.png)

# Instructions

*Stolen from [Paul Bladek](http://faculty.edcc.edu//paul.bladek/CS133/p4.htm) of EDCC*

RPN stands for ["Reverse Polish Notation."](http://www.hpmuseum.org/rpn.htm)  
This type of calculator works very well for computer science and engineering problems. 
It uses **post-fix** notation instead of **in-fix** notation -- that is, operations are written after the numbers operated on.  
For example, in **in-fix** notation, adding two numbers, then subtracting a third number might be written as `4 + 5 - 6`.  
In **post-fix** notation, the same expression could be written as `4 5 + 6 -`  or `4 5  6 - +`. 


Your assignment is to write an Object-oriented program in C++ to run an RPN calculator simulator. 
To do this, you should form a team of three-to-five members. 
You will need to turn in only one copy of the project for you group. 
Your group will need to define the following class with these minimum requirements:


- `class CRPNCalc` should at least have the following `private` or `protected` properties: 
    - `double m_registers[NUMREGS]` -- Numregs should be 10 -- the calculator's storage registers
    - `string m_buffer` -- a buffer for input
    - `deque<double> m_stack` -- the input stack. Represented as a deque to allow stack rotation.
    - `list<string> m_program` -- a list of program instructions for the one current program.  Programs can be entered directly in program mode or loaded from file.
    - `istringstream m_instrStream` -- stream for inputting. Can be set from console input or from  `m_program` elements.
    - `bool m_error` -- set when an error occurs. Cleared in `print()` after the `<error>` message is printed.
    - `bool m_helpOn` -- toggled on or off by the `"H"` key.  When on, print displays a menu of key strokes.
    - `bool m_on` -- whether the calculator is turned on or not. `run()` exits when this is `false`.

- `class CRPNCalc` should at least have the following methods: 
    - a constructor -- has one `bool` parameter for whether or not the calculator is turned on (defaults to `true`). 
      - Initializes properties that need initializing, sets all of the registers to `0.0`, and if `m_on`, calls `run()`.
    - `void run()` -- sets the calculator running. Loops while `m_on`.
    - `void print(ostream& ostr)` -- prints identifying line, the help menu if `m_helpOn`, the element at the top of the stack if it is not empty, and `<error>` if `m_error` (then sets `m_error` off).
    - `void input(istream& istr)` -- copies input into `m_buffer`, sets up `m_instrStream` with it, and calls `parse()`
    - `void parse()` -- extracts and executes the commands that are in `m_instrStream`.  
      - **note**: The sample executable allows more than one "token" (number or operator) in a line.  
      While this is nice for the user, it makes coding the parse method much more difficult.  
      You may code the parse method so that only one token per line is allowed 
      (therefore, the user would need to type in `2<cr>3<cr>+<cr>` in order to add `2` and `3`, rather than just `"2  3+<cr>"`).  
      If you wish to try to allow for multiple tokens, **five points of extra credit is available**.
    - `+`  -- addition
    - `-`  -- subtraction -- not to be confused with negation, as in `-3`
    - `*`  -- multiplication
    - `/`  -- division
    - `^`  -- exponentiation -- e.g. `4 5^` would be 4 to the 5th power (45).
    - `%`  -- mod  -- since the data type is double, this is fmod()
    - `C`  -- Clear --  removes all elements from the stack
    - `CE`  -- Clear Entry --  removes the top element from the stack
    - `D`  -- rotate the stack Down -- remove the top element and place it at the bottom.
    - `F`  -- save program to File --  asks the user for a file name and saves the program list string-by string to the file.
    - `G0` - `G9`  -- Gets the  value from `m_registers[n]` and places it at the top of the stack
    - `H`  -- toggles on/off `m_helpOn` 
    - `L`  -- Load program from file --  asks the user for a file name and loads the program list string-by string from the file.
    - `M`  -- Multiplies the top element of the stack by `-1`.
    - `P`  -- starts recording a Program after clearing any existing program. A "P" typed in during this process stops the recording. Each line is inserted as an element into `m_program`.
    - `R`  -- Runs the program stored in m_program.
    - `S0` - `S9`  -- Sets the value in `m_registers[n]` to the value at the top of the stack
    - `U`  -- rotate the stack Up -- remove the bottom element and place it at the top.
    - `X`  -- Exit run(), setting m_on to false.

> Any method encountering an error (such as trying to do a binary operation without having at least two elements in the stack) should make sure the program state is the way it was before starting the attempt and should set `m_error` to `true`.
Also, since all binary operations will need to get two numbers from the stack, all unary operations will need to get 1 number off the stack, etc, it would be wise to have methods like `binary_prep(double& d1, double& d2)` and `unary_prep(double& d)` to avoid re-writing code over and over again.

You will also need to define:
- `ostream &operator <<(ostream &ostr, const CRPNCalc &calc);`
- `istream &operator >>(istream &istr, CRPNCalc &calc);`

Once your calculator is working, use it to write, run and save an RPN program which goes through the numbers in registers `0` - `6`, 
puts the sum in register `7`, the mean (average) in register `8`, and the standard deviation in register `9`.

Standard deviation is defined as the square root of the variance of a set of data, where  the variance is: 
`(sum_of_the_squares -  (sum2 / number_of_elements)) / ( number_of_elements - 1)`.
(as a quick test, if the data are `[5 | 7 | 3 | 6 | 6 | 2 | 5]`, the standard deviation should be `1.772810520855837`).
**Include this saved program file with your project.**

