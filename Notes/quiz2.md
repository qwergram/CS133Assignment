# Quiz 2

Turn your answers in on a separate sheet of paper or submit to Canvas/Assignments/Quiz 2 as a .txt, .rtf, .doc, .docx or .pdf file by 9:30 a.m., Monday, April 25, 2016.

Below is some C++ code. Compile and run this code, then answer the following questions:

## Would the results have been the same if show() were not a virtual function? Answer and Explain for both the calls directly from the object and the calls through the pointers.

## Explain exactly--in detail--what happens in the for loop in main().
## A::show() shows the value of si, which is the count of the number of A objects. Using this information, decide if there is a problem of too many A objects caused by the D( ) constructor calling the A( ) constructor, then calling both the B( ) constructor and the C( ) constructor, which each call the A( ) constructor. Explain.
## In the try block near the end of the program, the program is apparently using aptr to call the A::show() method twice. Are the results the same? Explain why or why not.
## Remove the comment marks from the line near the end in the try block, and try to recompile. Explain: What you think the code is trying to do, why it doesn't work and would there be any need to call it, even if it did work? Why or why not?

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
}```

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

## without `virtual` keyword
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
