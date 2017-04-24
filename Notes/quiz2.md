# Quiz 2

Turn your answers in on a separate sheet of paper or submit to Canvas/Assignments/Quiz 2 as a .txt, .rtf, .doc, .docx or .pdf file by 9:30 a.m., Monday, April 25, 2016.

Below is some C++ code. Compile and run this code, then answer the following questions:

## Would the results have been the same if show() were not a virtual function? Answer and Explain for both the calls directly from the object and the calls through the pointers.

**Yes for object calls, No for pointers.** The output below shows that. Lines 1 through 4 are from the object calls, they remain the same because the object type of the object with the `.show()` method being invoked is the child. Each type (`A`, `B`, `C` and `D` on lines 1-4 respectively) have their own defined `.show()` method and the type of the object is the same as the object instance (and not the parent of the object type), resulting in no ambiguity. These four lines will stay the same regardless of use of the `virtual` keyword.

However in lines 5 – 8, the method `->show()` is still called on objects (`a`, `b`, `c` and `d` respectively) but the object type is not the type of the object, but rather the parent/grandparent of that object, namely type `A`.  With the `virtual` keyword, it’s able to find the child class type’s `show()` method and the results are displayed correctly. 

Therefore, on the left, lines 1 through 4 and 5 through 8 are identical (except for the `si` value).  On the righthand side, the `virtual` keyword is omitted, resulting in no virtual table look up, leading to `A::show()` (the parent and original type) being called for each child and grandchild, resulting in a different output.

![](http://imgur.com/fJ1Qzaq.png)

## Explain exactly--in detail--what happens in the for loop in main().

Before the `for` loop, an array of exactly two items was created, one containing the address of the `A::show` method, and the other of the `A::fa` method. In the loop, it iterates over both and `cout`s the index of the for loop and then invokes that method with `aptr` serving as “`this`”. Next it `cout`s an empty line. The iteration will happen twice.

## `A::show()` shows the value of `si`, which is the count of the number of `A` objects. Using this information, decide if there is a problem of too many `A` objects caused by the `D()` constructor calling the `A()` constructor, then calling both the `B()` constructor and the `C()` constructor, which each call the `A()` constructor. Explain.

`Si` is incremented by one every time the constructor of `A` is called and decremented by one every time the virtual destructor of `A` is called. Therefore with 4 objects in existence, `si` should only be 4. The reason why `D()` only adds one to `si` despite inheriting from `B` and `C` (which inherit from `A`) is because there is no `A` part in either `B` or `C`, so the `A` constructor in `B` or `C` is ignored when called by `D`.

## In the try block near the end of the program, the program is apparently using aptr to call the A::show() method twice. Are the results the same? Explain why or why not.

The first time it is invoked, it is explicitly stated with which class’s `show()` method to use, namely `A`. Despite being a pointer to a type `D` instance, it invokes the method on class `A` because it was the one told to run. The output is that is on line B in the output snippet above. 

However, the second time it is invoked, it is given the address of the method `A::show`. This results in the virtual table look up and instead executes `D::show`. Additionally, this is why if the `virtual` keyword is excluded, the output would look the same if `A::show` had been called.


## Remove the comment marks from the line near the end in the try block, and try to recompile. Explain: What you think the code is trying to do, why it doesn't work and would there be any need to call it, even if it did work? Why or why not?

The code is trying to cast the `D::show` method to `AFP`. This doesn’t work because during compilation the error code C2440 is raised, it states: `“reinterpret_cast cannot convert from void (__cdecl D::* ) (void) const to AFP”`. There is no need to do this even if it did work because there’s already virtual tables in play that will already lookup the correct method you’re looking for.

# Source Code

```cpp
#include <iostream>
#include <cstdlib>
const int BUFFER_SIZE = 256;
using namespace std;

//-----------------------------------------------------------------------------
// The base Class 
//-----------------------------------------------------------------------------
class A
{
public:
    A(int a = 0, double b = 0.0) : i(a), d(b) {si++;}
    void fa() const {cout << "fa";}
    virtual void show() const {cout << "{A:" << i << ":" << d << ":" << si << "A}";}
    virtual ~A() { si--;}
protected:
    static int si;
    int i;
    double d;
};

//-----------------------------------------------------------------------------
// virtually inherited child 
//-----------------------------------------------------------------------------
class B :virtual public A
{
public:
    B(int a = 0, double b = 0.0) : A(a, b){}
    void show() const {cout << "{B:"; A::show(); cout << "B}";}
    virtual ~B() { }
};

//-----------------------------------------------------------------------------
// virtually inherited child 
//-----------------------------------------------------------------------------
class C :virtual public A
{
public:
    C(int a = 0, double b = 0.0) : A(a, b){}
    void show() const {cout << "{C:"; A::show(); cout << "C}";}
    virtual ~C() { }
};

//-----------------------------------------------------------------------------
// multiply inherited grandchild 
//-----------------------------------------------------------------------------
class D :public B, public C
{
public:
    D(int a = 0, double b = 0.0) : A(a, b), B(a, b), C(a, b){}
    void show() const{cout << "{D:"; B::show(); C::show(); cout << "D}";}
    virtual ~D() { }
};

int A::si = 0; // initialize static
typedef void(A::*AFP)() const; // the AFP type is: a pointer to a const void method of class A that has no parameters

//-----------------------------------------------------------------------------
// test driver 
//-----------------------------------------------------------------------------
int main(void)
{
    A a(3, 4.4);
    a.show();
    cout << endl;
    B b(5, 6.6);
    b.show();
    cout << endl;
    C c(7, 8.8);
    c.show();
    cout << endl;
    D d(9, 2.2);
    d.show();
    cout << endl;
    A* aptr = &a;
    aptr->show();
    cout << endl;
    aptr = &b;
    aptr->show();
    cout << endl;
    aptr = &c;
    aptr->show();
    cout << endl;
    aptr = &d;
    aptr->show();
    cout << endl;
    AFP fp[2] = {&A::show, &A::fa};
    aptr = &a;
    for(int i =0; i < 2; i++)
    {
        cout << i << ") ";
        (aptr->*(fp[i]))();
        cout << endl;
    }
    try 
    {
        aptr = &d;
        aptr->A::show();
        cout << endl;
        // fp[0] = reinterpret_cast<AFP>(&D::show);
        (aptr->*(fp[0]))();
        cout << endl;
    } 
    catch(bad_cast e) 
    { 
         cerr << "Shutting down: " << e.what() << endl;
         cin.ignore(BUFFER_SIZE, '\n');
         return EXIT_FAILURE;
    }
    cin.ignore(BUFFER_SIZE, '\n');
    return EXIT_SUCCESS;
}
```

# Outputs

## With `virtual` keyword
```
{A:3:4.4:1A}
{B:{A:5:6.6:2A}B}
{C:{A:7:8.8:3A}C}
{D:{B:{A:9:2.2:4A}B}{C:{A:9:2.2:4A}C}D}
{A:3:4.4:4A}
{B:{A:5:6.6:4A}B}
{C:{A:7:8.8:4A}C}
{D:{B:{A:9:2.2:4A}B}{C:{A:9:2.2:4A}C}D}
0) {A:3:4.4:4A}
1) fa
{A:9:2.2:4A}
{D:{B:{A:9:2.2:4A}B}{C:{A:9:2.2:4A}C}D}
```

## Without `virtual` keyword
```
{A:3:4.4:1A}
{B:{A:5:6.6:2A}B}
{C:{A:7:8.8:3A}C}
{D:{B:{A:9:2.2:4A}B}{C:{A:9:2.2:4A}C}D}
{A:3:4.4:4A}
{A:5:6.6:4A}
{A:7:8.8:4A}
{A:9:2.2:4A}
0) {A:3:4.4:4A}
1) fa
{A:9:2.2:4A}
{A:9:2.2:4A}
```
