# [Virtual Inheritance](http://faculty.edcc.edu//paul.bladek/CS133/VirtualInheritance.htm)

Using the `virtual` keyword in C++ inheritance.

## Context

Imagine the [following classes](https://github.com/qwergram/CS133Assignment/blob/master/Quiz2/quiz_source.cpp) are declared:

```cpp
// Object set 1 (ABCD)
class A { /* some code here */ }
class B: public A { /* some code here */ }
class C: public A { /* some code here */ }
class D: public B, public C { /* some code here */ }

// Object set 2 (PQRS)
class P { /* some code here */ }
class Q: virtual public P { /* some code here */ }
class R: virtual public P { /* some code here */ }
class S: public Q, public R { /* some code here */ }
```

This inheritance structure is called a diamond inheritance structure.

Imagine the classes have the same methods shown in the [quiz](https://github.com/qwergram/CS133Assignment/blob/master/Quiz2/quiz_source.cpp).

## Basic Inheritance Rules (Regardless of `virtual`)

By default, all methods from the child class are **inherited** from the parent class.
The **exceptions** are:
- Constructors
- Destructors
- Friend functions
- static class functions
- static class properties
- Assignment overload operator (`operator=`)

This means that if there is behavior defined in any of the `methods` or `functions`
listed above, that method or function must be called explicitly or the behavior
expected from those methods or functions will not occur.

> **Important Note:**
> 
> For the `A` constructor behavior to happen in all children:</br>
> `B`'s constructor MUST call `A`'s constructor.<br/>
> `C`'s constructor MUST call `A`'s constructor.<br/>
> And finally, `D` MUST call the constructors `A`, `B`, `C`. <br/>
> When `D`'s constructor is called, `B` and `C` will not implicity `A`'s constructor,
> requiring `A`'s constructor be called once again in `D`'s constructor.

In addition, if a child replaces something in the parent in any way, the proper name
for that action is defined in the table below:

<table>
<tr>
    <td><b>Replacement terminology</b></td>
    <td><b>Thing being replaced</b></td>
</tr>

<tr>
    <td>Overriding</td>
    <td>Properties</td>
</tr>

<tr>
    <td>Overloading</td>
    <td>Methods (but with different parameters OR parent method is <code>virtual</code>)</td>
</tr>

<tr>
    <td>Hiding</td>
    <td>Methods (with the same parameters AND parent method is NOT <code>virtual</code>)</td>
</tr>
</table>

## Ambiguity

As shown in the [quiz](https://github.com/qwergram/CS133Assignment/blob/master/Notes/quiz2.md),


## Conversion and Casts