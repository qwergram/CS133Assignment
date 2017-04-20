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
	A(int a = 0, double b = 0.0) : i(a), d(b) { si++; }
	void fa() const { cout << "fa"; }
	virtual void show() const { cout << "{A:" << i << ":" << d << ":" << si << "A}"; }
	virtual ~A() { si--; }
protected:
	static int si;
	int i;
	double d;
};

//-----------------------------------------------------------------------------
// virtually inherited child 
//-----------------------------------------------------------------------------
class B : virtual public A
{
public:
	B(int a = 0, double b = 0.0) : A(a, b) {}
	void show() const { cout << "{B:"; A::show(); cout << "B}"; }
	virtual ~B() { }
};

//-----------------------------------------------------------------------------
// virtually inherited child 
//-----------------------------------------------------------------------------
class C :virtual public A
{
public:
	C(int a = 0, double b = 0.0) : A(a, b) {}
	void show() const { cout << "{C:"; A::show(); cout << "C}"; }
	virtual ~C() { }
};

//-----------------------------------------------------------------------------
// multiply inherited grandchild 
//-----------------------------------------------------------------------------
class D :public B, public C
{
public:
	D(int a = 0, double b = 0.0) : A(a, b), B(a, b), C(a, b) {}
	void show() const { cout << "{D:"; B::show(); C::show(); cout << "D}"; }
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

	A atype = a;
	atype.show();
	cout << endl;
	atype = b;
	atype.show();
	cout << endl;
	atype = c;
	atype.show();
	cout << endl;
	atype = d;
	atype.show();
	cout << endl;
	cout << endl << endl;

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
	AFP fp[2] = { &A::show, &A::fa };
	aptr = &a;
	for (int i = 0; i < 2; i++)
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
	catch (bad_cast e)
	{
		cerr << "Shutting down: " << e.what() << endl;
		cin.ignore(BUFFER_SIZE, '\n');
		return 1;
	}
	cin.ignore(BUFFER_SIZE, '\n');
	return 0;
}