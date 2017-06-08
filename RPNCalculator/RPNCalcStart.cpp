#include "RPNCalc.h"
//-------------------------------------------------------------------------------------------
//    Class:		CRPNCalc
//
//    File:             RPNCalc.cpp
//
//    Description:	This file contains the function definitions for CRPNCalc
//
//    Programmer:		
//   
//    Date:             
// 
//    Version:          1.0
//  
//    Environment:	Intel Xeon PC 
//                  	Software:   MS Windows 7 for execution; 
//                  	Compiles under Microsoft Visual C++.Net 2010
// 
//	  class CRPNCalc:
//
//	  Properties:
//				double m_registers[10];
//				stack<string> m_stack;
//				vector<list<string>> m_programs(NUMPROGRAMS);
//				istringstream m_inStrStream;
//	
//
//	  Non-inline Methods:
//	
//				CRPNCalc(bool on)
//				run()
//				print(ostream& ostr)
//				parse()
//				void add() -- 
//				void bin_prep(double& d1, double& d2) -- 
//				void clear() -- 
//				void clearAll() -- 
//				void divide() -- 
//				void exp() -- 
//				void getReg(int reg) -- 
//				void loadProgram() -- 
//				void mod() -- 
//				void multiply() -- 
//				void neg() -- 
//				void parse() -- 
//				void recordProgram() -- 
//				void rotateUp() -- 
//				void rotateDown() -- 
//				void runProgram() -- 
//				void saveToFile() -- 
//				void setReg(int reg) -- 
//				void subtract() -- 
//				void unary_prep(double& d) -- 
	
//	  related functions:
//				ostream &operator <<(ostream &ostr, const CRPNCalc &calc)
//    				istream &operator >>(istream &istr, CRPNCalc &calc)
//
//    History Log:
//                           
// ----------------------------------------------------------------------------	
namespace PB_CALC
{
// ----------------------------------------------------------------------------
//	constructor
// ----------------------------------------------------------------------------
	CRPNCalc::CRPNCalc(bool on): m_on(on), m_error(false), m_helpOn(true),
		m_programRunning(false)
	{
		for(int i = 0; i < NUMREGS; i++)
			m_registers[i] = 0.0;
		if(m_on)
			run();
	}

// ----------------------------------------------------------------------------
//	starts the calculator running
// ----------------------------------------------------------------------------
	void CRPNCalc::run()
	{
		do 
		{
			system("cls"); //clear the screen
			print(cout);   //display calculator
			input(cin);    //take inputs
		} while (m_on);
	} 

// ----------------------------------------------------------------------------
//	prints out calculator screen
// ----------------------------------------------------------------------------
	void CRPNCalc::print(ostream& ostr)
	{
		double d = 0.0;
		ostr << "[RPN Programmable Calculator] by Paul Bladek" << endl;
		if(m_helpOn)
			cout << helpMenu;
		else
			cout << endl << endl << endl;
		cout << line;
		if(!m_stack.empty())
		{
			d = m_stack.front();
			ostr << d;
		}
		ostr << endl << endl;
		if(m_error)
		{
			ostr << "<<error>>" << endl;
			m_error = false;
		}
	} 

// ----------------------------------------------------------------------------
//	parses the next command from m_instrStream
// ----------------------------------------------------------------------------
	void CRPNCalc::parse()
	{

	}

// ----------------------------------------------------------------------------
//	if possible, pops top 2 elements from the stack, adds them
//	  and pushes the result onto the stack
// ----------------------------------------------------------------------------	
	void CRPNCalc::add()
	{
		double d1 = 0;
		double d2 = 0;

		binary_prep(d1, d2);
		if (!m_error)
		{
			d2 += d1;
			m_stack.push_front(d2);
		}
	} 

// ----------------------------------------------------------------------------
//	sets the args to the popped values from the stack, if possible
//	  set error state otherwise
// ----------------------------------------------------------------------------

	void CRPNCalc::binary_prep(double& d1, double& d2)
	{
		if (!m_stack.empty())
		{
			d1 = m_stack.front();
			m_stack.pop_front();
			if (!m_stack.empty())
			{
				d2 = m_stack.front();
				m_stack.pop_front();
			}
			else
			{
				m_error = true;
				m_stack.push_front(d1);
			}
		}
		else
			m_error = true;
	} 

// ----------------------------------------------------------------------------
//	removes the top element from the stack
// ----------------------------------------------------------------------------
	void CRPNCalc::clearEntry()
	{
		if (!m_stack.empty())
			m_stack.pop_front();
	} 

// ----------------------------------------------------------------------------
//	empties the stack
// ----------------------------------------------------------------------------
	void CRPNCalc::clearAll()
	{
		while(!m_stack.empty())	
			m_stack.pop_front();
	} 

// ----------------------------------------------------------------------------
//	if possible, pops top 2 elements from the stack, divides them
//	  and pushes the result onto the stack
// ----------------------------------------------------------------------------
   void CRPNCalc::divide()
   {
	   double d1 = 0;
	   double d2 = 0;
	   
	   binary_prep(d1, d2);
	   if (!m_error)
	   {
		   d2 /= d1;
		   m_stack.push_front(d2);
	   }
   } 

// ----------------------------------------------------------------------------
//	if possible, pops top 2 elements from the stack,
//	  raises one element to the other power
//	  and pushes the result onto the stack
// ----------------------------------------------------------------------------
   void CRPNCalc::exp()
   {
	   double d1 = 0;
	   double d2 = 0;

	   binary_prep(d1, d2);
	   if (!m_error)
	   {
		   d1 = pow(d2, d1);
		   m_stack.push_front(d1);
	   }
   }  

// ----------------------------------------------------------------------------
//	pushes the given register's value onto the stack
// ----------------------------------------------------------------------------
	void CRPNCalc::getReg(int reg)
	{
		double tempReg = m_registers[reg];
		m_stack.push_front(tempReg);
	}  

// ----------------------------------------------------------------------------
//	retrieves the filename from the user and loads it into m_program
// ----------------------------------------------------------------------------
	void CRPNCalc::loadProgram()
	{
	
	}  

// ----------------------------------------------------------------------------
//	if possible, pops top 2 elements from the stack, mods them
//	  and pushes the result onto the stack
// ----------------------------------------------------------------------------
   void CRPNCalc::mod()
   {
	   double d1 = 0;
	   double d2 = 0;
	   
	   binary_prep(d1, d2);
	   if (!m_error)
	   {
		   d1 = fmod(d2, d1);
		   m_stack.push_front(d1);
	   }
   } 

// ----------------------------------------------------------------------------
//	if possible, pops top 2 elements from the stack, multiplies them
//	  and pushes the result onto the stack
// ----------------------------------------------------------------------------
   void CRPNCalc::multiply()
   {
	   double d1 = 0;
	   double d2 = 0;
	   
	   binary_prep(d1, d2);
	   if (!m_error)
	   {
		   d1 *= d2;
		   m_stack.push_front(d1);
	   }
   }  

// ----------------------------------------------------------------------------
//	resets the top element of the stack to it's negative
// ----------------------------------------------------------------------------
	void CRPNCalc::neg()
	{
		double tempNeg;
		unary_prep(tempNeg);
		tempNeg *= -1;
		m_stack.push_front(tempNeg);
	}  

// ----------------------------------------------------------------------------
//	sets the arg to the popped value from the stack, if possible
//	  sets error state otherwise
// ----------------------------------------------------------------------------
	void CRPNCalc::unary_prep(double& d)
	{
		if (!m_stack.empty())
		{
			d = m_stack.front();
			m_stack.pop_front();
		}
		else
			m_error = true;
	}  

// ----------------------------------------------------------------------------
//	takes command-line input and loads it into m_program 
// ----------------------------------------------------------------------------
	void CRPNCalc::recordProgram()
	{

	} 

// ----------------------------------------------------------------------------
//	removes the bottom of the stack and adds it to the top
// ----------------------------------------------------------------------------
	void CRPNCalc::rotateDown()
	{
	
	} 

// ----------------------------------------------------------------------------
//	removes the top of the stack and adds it to the bottom
// ----------------------------------------------------------------------------
	void CRPNCalc::rotateUp()
	{
	
	} 

// ----------------------------------------------------------------------------
//	runs the program in m_program 
// ----------------------------------------------------------------------------
	void CRPNCalc::runProgram()
	{
		
	} 

// ----------------------------------------------------------------------------
//	asks the user for a filename and saves m_program to that file
// ----------------------------------------------------------------------------
	void CRPNCalc::saveToFile()
	{
			
	}  

// ----------------------------------------------------------------------------
//	gets the value from the top of the stack
//	  and places it into the given register
// ----------------------------------------------------------------------------
	void CRPNCalc::setReg(int reg)
	{
			
	} 

// ----------------------------------------------------------------------------
//	if possible, pops top 2 elements from the stack, subtracts them
//	  and pushes the result onto the stack
// ----------------------------------------------------------------------------
   void CRPNCalc::subtract()
   {
	   double d1 = 0;
	   double d2 = 0;
	   
	   binary_prep(d1, d2);
	   if (!m_error)
	   {
		   double diff = d2 - d1;
		   m_stack.push_front(diff);
	   }
   } 

// ----------------------------------------------------------------------------
//	inputs a line from the given stream
// ----------------------------------------------------------------------------
	void CRPNCalc::input(istream &istr)
	{
		getline(istr, m_buffer); //get input lines
		istringstream temp(m_buffer);
		m_instrStream.swap(temp);
		if (m_programRunning)
			m_program.push_back(m_instrStream.str());
		this->parse();
	} 

// ----------------------------------------------------------------------------
//	ostream's << defined for CRPNCalc
// ----------------------------------------------------------------------------
   ostream &operator <<(ostream &ostr, CRPNCalc &calc)
	{
		calc.print(ostr);
		return ostr;
	} 
	
// ----------------------------------------------------------------------------
//	istream's >> defined for CRPNCalc
// ----------------------------------------------------------------------------
	istream &operator >>(istream &istr, CRPNCalc &calc)
	{
		calc.input(istr);
		return istr;
	} 
} // end namespace PB_CALC
