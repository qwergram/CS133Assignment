//----------------------------------------------------------------------------
//    File:		RPNCalc.h
//
//    Class:	CRPNCalc
//----------------------------------------------------------------------------
#ifndef RPNCALC_H
#define RPNCALC_H

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <new>
#include <sstream>
#include <stack>
#include <vector>
//----------------------------------------------------------------------------
//
//    Title:		RPNCalc Class
//
//    Description:	This file contains the class definition for CRPNCalc
//
//    Programmer:	Paul Bladek
//   
//    Date:		5/3/11
// 
//    Version:		1.03-1
//  
//    Environment:
//       Hardware: Intel Xeon PC
//       Software: Windows 7
//       Compiles under Microsoft Visual Studio 2010
// 
//	  class CRPNCalc:
//
//	  Properties:
//		double m_registers[10] -- 
//		string m_buffer -- 
//		stack<string> m_stack -- 
//		vector<list<string>> m_programs(NUMPROGRAMS) -- 
//		istringstream m_inStrStream -- 
//		m_on -- 
//		bool m_error --
//		bool m_helpOn --  
//
//	  Methods:
//	
//		inline:	None		
//
//		non-inline:
//		public:
//			CRPNCalc(bool on);
//			void run();                                        
//			void print(ostream& ostr);
//			void input(istream& istr);
//		private:
//				
//			void add() -- 
//			void bin_prep(double& d1, double& d2) -- 
//			void clear() -- 
//			void clearAll() -- 
//			void divide() -- 
//			void exp() -- 
//			void getReg(int reg) -- 
//			void loadProgram() -- 
//			void mod() -- 
//			void multiply() -- 
//			void neg() -- 
//			void parse() -- 
//			void recordProgram() -- 
//			void rotateUp() -- 
//			void rotateDown() -- 
//			void runProgram() -- 
//			void saveToFile() -- 
//			void setReg(int reg) -- 
//			void subtract() -- 
//			void unary_prep(double& d) -- 		   
//
//    History Log:
//	4/20/03	PB  completed version 1.0
//	5/27/05	PB  minor modifications 1.01
//	5/3/11	PB  minor modifications 1.02
//	6/3/12  PB  minor modifications 1.03
//	6/11/2017 TR testhelper methods 1.03-1
// ----------------------------------------------------------------------------

using namespace std;

namespace P4_RPNCALC
{

	const char helpMenu[] = 
		"C clear stack   | CE clear entry  | D rotate down   | F save program to file\n"
		"G0-G9 get reg n | H help on/off   | L load program  | M +/-  | P program on/off\n"
		"R run program   | S0-S9 set reg n | U rotate up     | X exit | Y Heapify Stack\n"
		"W sort stack    | Q show stack    | >/< +/- 1 stack | T swap stack/reg\n";

	const char line[] = "____________________________________________________________________________\n";

	const unsigned short NUMREGS = 10;

	class CRPNCalc
	{
	public:
		CRPNCalc(bool on = true);
		void run();
		void print(ostream& ostr);  // changes m_error on error, so not const
		void input(istream& istr);

		//testing methods-will be removed for submission
		string getBuffer() const { return m_buffer; };
		void depInj_setBuffer(string input) { m_buffer = input; };
		void depInj_runParse() { parse(); };
		double getOutput() { if (!m_stack.empty()) return m_stack.front(); 
			else throw invalid_argument("empty stack"); };
		string depInj_lastOutput() 
		{
			if (m_error) { m_error = false; return "<<error>>"; }
			else { return this->m_lastOutput; }
		}

	private:
		// private methods
		void add();
		void binary_prep(double& d1, double& d2);
		void clearEntry();
		void clearAll();
		void divide();
		void exp();
		void getReg(int reg);
		void loadProgram();
		void mod();
		void multiply();
		void neg();
		void parse();
		void recordProgram();
		void rotateUp();
		void rotateDown();
		void runProgram();
		void saveToFile();
		void setReg(int reg);
		void subtract();
		void unary_prep(double& d);
		string getToken();

		void sortStack();
		void showStack();
		void swapStackReg();
		void transformStack(short direction);
		void heapifyStack(int i=-1);

		// private properties
		double m_registers[NUMREGS];
		string m_buffer;
		deque<double> m_stack;
		list<string> m_program;
		istringstream m_instrStream;
		bool m_error;
		bool m_helpOn;
		bool m_on;
		bool m_programRunning;
		string m_commandOutput;
		string m_lastOutput;
	};

	ostream &operator <<(ostream &ostr, CRPNCalc &calc);
	istream &operator >> (istream &istr, CRPNCalc &calc);

} // end namespace PB_CALC

#endif
