#include "RPNCalc.h"
//-------------------------------------------------------------------------------------------
//    Class:		CRPNCalc
//
//    File:             RPNCalc.cpp
//
//    Description:	This file contains the function definitions for CRPNCalc
//
//    Programmer:		Tabitha Roemish, Cecilia Tong, Norton Pengra, Antonio Castelli -
//		see github link for individual contributions
//   
//    Date:             June 2017
// 
//    Version:          1.0
//  
//    Environment:	Intel Xeon PC 
//                  	Software:   MS Windows 10; 
//                  	Compiles under Microsoft Visual C++.Net 2015
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
//	
//	  related functions:
//				ostream &operator <<(ostream &ostr, const CRPNCalc &calc)
//    				istream &operator >>(istream &istr, CRPNCalc &calc)
//
//    History Log:
//                 https://github.com/qwergram/CS133Assignment/pull/7          
// ----------------------------------------------------------------------------	
namespace P4_RPNCALC
{
	
	//--------------------------------------------------------------------
	// Title: CRPNCalc constructor
	// Description: constructs RPN calculator instance
	// Called By: main(), testHelper constructor
	// Calls: run()
	// Parameters: bool on - this runs the program if true.
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	//--------------------------------------------------------------------
	
	CRPNCalc::CRPNCalc(bool on) : m_on(on), m_error(false), m_helpOn(true),
		m_programRunning(false)
	{
		for (int i = 0; i < NUMREGS; i++)
			m_registers[i] = 0.0;
		if (m_on)
			run();
	}
	//--------------------------------------------------------------------
	// Title: CRPNCalc::run()
	// Description: starts the calculator running
	// Called By: CRPNCalc constructor
	// Calls: parse(), input(), print()
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	//--------------------------------------------------------------------
	
	void CRPNCalc::run()
	{
		while (m_on)
		{
			system("cls");
			print(cout);
			input(cin);
			while (!m_buffer.empty())
				parse();
		}
	}
	//--------------------------------------------------------------------
	// Title: void CRPNCalc::print(ostream& ostr)
	// Description: prints out calculator screen
	// Called By: operator <<
	// Calls:  operator <<, STl - empty(), front()
	// Parameters: ostream& ostr - outstream reference
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	//--------------------------------------------------------------------
	
	void CRPNCalc::print(ostream& ostr)
	{
		double d = 0.0;
		ostr << "[RPN Programmable Calculator] by @ctongGH, @qwergram, @TabithaRoemish & @AntonioCastelli" << endl;
		if (m_helpOn)
			ostr << helpMenu;
		ostr << line;
		if (!m_commandOutput.empty()) {
			ostr << m_commandOutput;
			m_commandOutput = "";
		} 
		else if (!m_stack.empty())
		{
			this->m_lastOutput = to_string(m_stack.front());
			ostr << m_stack.front();
		}
		ostr << endl << endl;
		if (m_error)
		{
			this->m_lastOutput = "<<error>>";
			ostr << this->m_lastOutput << endl;
			m_error = false;
		}
	}
	//--------------------------------------------------------------------
	// Title: void CRPNCalc::parse()
	// Description: parses the next command from m_instrStream
	// Called By: input(), run(), runProgram(), runParse()-(for testing)
	// Calls: all CRPNCalc methods
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	//--------------------------------------------------------------------

	void CRPNCalc::parse()
	{
		string token = getToken();
		if (token.empty())
			return;
		double temp = 0.0;
		if (istringstream(token) >> temp)
			m_stack.push_front(temp);
		else
		{
			if ((token.size() != 1 && toupper(token.front()) != 'C'
				&& toupper(token.front()) != 'G' &&
				toupper(token.front()) != 'S') || token.size() > 2)
				token.front() = '#'; // triggers default
			switch (toupper(token.front()))
			{
			case '+':
				add();
				break;
			case '-':
				subtract();
				break;
			case '*':
				multiply();
				break;
			case '/':
				divide();
				break;
			case '^':
				exp();
				break;
			case '%':
				mod();
				break;
			case 'D':
				rotateDown();
				break;
			case 'F':
				saveToFile();
				break;
			case 'H':
				m_helpOn = !m_helpOn;
				break;
			case 'L':
				loadProgram();
				break;
			case 'M':
				neg();
				break;
			case 'P':
				recordProgram();
				break;
			case 'R':
				runProgram();
				break;
			case 'U':
				rotateUp();
				break;
			case 'X':
				m_on = false;
				break;
			case 'C':
				if (token.size() == 1)
					clearAll();
				else if (toupper(token.back()) == 'E')
					clearEntry();
				else
					m_error = true;
				break;
			case 'G':
				if (token.back() >= '0' && token.back() < '0' + NUMREGS)
					getReg(token.back() - '0');
				else
					m_error = true;
				break;
			case 'S':
				if (token.back() >= '0' && token.back() < '0' + NUMREGS)
					setReg(token.back() - '0');
				else
					m_error = true;
				break;
			case 'Q':
				this->showStack();
				break;
			case 'W':
				this->sortStack();
				break;
			case '>':
				this->transformStack(1);
				break;
			case '<':
				this->transformStack(-1);
				break;
			case 'T':
				this->swapStackReg();
				break;
			default:
				m_error = true;
			}
		}
	}
	//--------------------------------------------------------------------
	// Title: void CRPNCalc::add()
	// Description: if possible, pops top 2 elements from the stack, adds them
	//	  and pushes the result onto the stack
	// Called By: main(), testhelper
	// Calls: STL -push_front()
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan:  https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::add()
	{
		double num1 = 0.0;
		double num2 = 0.0;
		binary_prep(num1, num2);
		if (!m_error)
			m_stack.push_front(num1 + num2);
	}
	//--------------------------------------------------------------------
	// Title: void CRPNCalc::subtract()
	// Description: if possible, pops top 2 elements from the stack, subtracts them
	//	  and pushes the result onto the stack
	// Called By: main(), testhelper
	// Calls: STL -push_front()
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan:  https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::subtract()
	{
		double num1 = 0.0;
		double num2 = 0.0;
		binary_prep(num1, num2);
		if (!m_error)
			m_stack.push_front(num1 - num2);
	}
	//--------------------------------------------------------------------
	// Title: void CRPNCalc::multiply()
	// Description: if possible, pops top 2 elements from the stack, multiplies them
	//	  and pushes the result onto the stack
	// Called By: main(), testhelper
	// Calls: STL -push_front()
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan:  https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::multiply()
	{
		double num1 = 0.0;
		double num2 = 0.0;
		binary_prep(num1, num2);
		if (!m_error)
			m_stack.push_front(num1 * num2);
	}
	
	// --------------------------------------------------------------------
	// Title: void CRPNCalc::divide()
	// Description: if possible, pops top 2 elements from the stack, divides them
	//	  and pushes the result onto the stack
	// Called By: main(), testhelper
	// Calls: STL -push_front()
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan:  https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::divide()
	{
		double num1 = 0.0;
		double num2 = 0.0;
		binary_prep(num1, num2);
		if (!m_error)
			m_stack.push_front(num1 / num2);
	}
	//--------------------------------------------------------------------
	// Title: void CRPNCalc::exp()
	// Description: if possible, pops top 2 elements from the stack,
	//	  raises one element to the other power
	//	  and pushes the result onto the stack
	// Called By: main(), testhelper
	// Calls: STL -push_front()
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan:  https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------

	void CRPNCalc::exp()
	{
		double num1 = 0.0;
		double num2 = 0.0;
		binary_prep(num1, num2);
		if (!m_error)
			m_stack.push_front(pow(num1, num2));
	}
	//--------------------------------------------------------------------
	// Title: void CRPNCalc::mod()
	// Description: if possible, pops top 2 elements from the stack, mods them
	//	  and pushes the result onto the stack
	// Called By: main(), testhelper
	// Calls: STL -push_front()
	// Parameters: none
	// Returns: none 
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan:  https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::mod()
	{
		double num1 = 0.0;
		double num2 = 0.0;
		binary_prep(num1, num2);
		if (!m_error)
			m_stack.push_front(fmod(num1, num2));
	}
	//--------------------------------------------------------------------
	// Title: void CRPNCalc::binary_prep(double& d1, double& d2)
	// Description: sets the args to the popped values from the stack, if possible
	//	  set error state otherwise
	// Called By: main(), testhelper
	// Calls: STL -push_front(), pop_front();
	// Parameters: double& d1, double& d2 - values from the stack
	// Returns: none 
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------


	void CRPNCalc::binary_prep(double& d1, double& d2)
	{
		if (m_stack.size() < 2)
			m_error = true;
		else
		{
			d2 = m_stack.front();
			m_stack.pop_front();
			d1 = m_stack.front();
			m_stack.pop_front();
		}
	}
	//--------------------------------------------------------------------
	// Title: void CRPNCalc::unary_prep(double& d)
	// Description: sets the arg to the popped value from the stack, if possible
	//	  sets error state otherwise
	// Called By: main(), testhelper
	// Calls: STL -push_front(), pop_front();
	// Parameters: double& d1 - value from the stack
	// Returns: none 
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------

	void CRPNCalc::unary_prep(double& d)
	{
		if (m_stack.empty())
			m_error = true;
		else
		{
			d = m_stack.front();
			m_stack.pop_front();
		}
	}
	//--------------------------------------------------------------------
	// Title: void CRPNCalc::clearEntry()
	// Description: removes the top element from the stack
	// Called By: main(), testhelper
	// Calls: unary_prep()
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::clearEntry()
	{
		double temp = 0.0;
		unary_prep(temp);
	}

	//--------------------------------------------------------------------
	// Title: void CRPNCalc::clearAll()
	// Description: empties the stack
	// Called By: main(), testhelper
	// Calls: STL -pop_front(), empty()
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::clearAll()
	{
		while (!m_stack.empty())
			m_stack.pop_front();
	}

	//--------------------------------------------------------------------
	// Title: void CRPNCalc::getReg(int reg)
	// Description: pushes the given register's value onto the stack
	// Called By: main(), testhelper
	// Calls: STL -push_front()
	// Parameters: int reg - register number
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::getReg(int reg)
	{
		m_stack.push_front(m_registers[reg]);
	}

	//--------------------------------------------------------------------
	// Title: void CRPNCalc::loadProgram()
	// Description: retrieves the filename from the user and loads it into m_program
	// Called By: main()
	// Calls: STL - push_back(), ignore(), clear(), close();
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::loadProgram()
	{
		string filename = "";
		if (m_buffer.empty())
		{
			cout << "Enter File Name of Saved Program:\n";
			cin >> filename;
			cin.ignore(FILENAME_MAX, '\n');
		}
		else
			filename = getToken();
		fstream fstr(filename, fstream::in);
		if (fstr)
		{
			string temp = m_buffer;
			m_program.clear();
			while (!fstr.eof())
			{
				getline(fstr, m_buffer);
				while (!m_buffer.empty())
				{
					string token = getToken();
					m_program.push_back(token);
				}
			}
			m_buffer = temp;
		}
		else
			m_error = true;
		fstr.close();
	}
	//--------------------------------------------------------------------
	// Title: void CRPNCalc::saveToFile()
	// Description: asks the user for a filename and saves m_program to that file
	// Called By: main()
	// Calls: STL - .empty(), .close(), .end(), begin();
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	//--------------------------------------------------------------------
	void CRPNCalc::saveToFile()
	{
		if (this->m_program.empty()) {
			m_error = true;
		}
		else {
			string filename = "";
			fstream fstr;
			if (m_buffer.empty())
			{
				cout << "Enter a filename:\n";
				cin >> filename;
				cin.ignore(FILENAME_MAX, '\n');
			}
			else
				filename = getToken();
			fstr = fstream(filename, fstream::out);
			if (fstr)
			{
				list<string>::iterator it = m_program.begin();
				while (it != m_program.end())
					fstr << *it++ << endl;
			}
			else
				m_error = true;
			fstr.close();
		}
	}
	//--------------------------------------------------------------------
	// Title: void CRPNCalc::recordProgram()
	// Description: takes command-line input and loads it into m_program 
	// Called By: main()
	// Calls: STL - toupper(), getline(), push_back(), front(), empty()
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::recordProgram()
	{
		string token = "hello world";
		m_program.clear();
		unsigned macro_size = 0;
		while (!(token.size() == 1 && toupper(token.front() == 'P')))
		{
			if (m_buffer.empty()) {
				cout << macro_size++ << "> ";
				getline(cin, m_buffer);
			}
			string token = getToken();
			if (token.empty())
				continue;
			double temp = 0.0;
			if (istringstream(token) >> temp)
				m_program.push_back(token);
			else
			{
				if ((token.size() != 1 && toupper(token.front()) != 'C'
					&& toupper(token.front()) != 'G' &&
					toupper(token.front()) != 'S') || token.size() > 2)
					token.front() = '#';
				switch (toupper(token.front()))
				{
				case 'P':
					return;
				case '+':
				case '-':
				case '*':
				case '/':
				case '^':
				case '%':
				case 'D':
				case 'F':
				case 'H':
				case 'L':
				case 'M':
				case 'R':
				case 'U':
				case 'X':
				case 'W':
				case '>':
				case '<':
				case 'T':
					m_program.push_back(token);
					break;
				case 'C':
					if (token.size() == 1 || toupper(token.back()) == 'E')
						m_program.push_back(token);
					else
						m_error = true;
					break;
				case 'G':
				case 'S':
					if (token.back() >= '0' && token.back() < '0' + NUMREGS)
					{
						m_program.push_back(token);
						break;
					}
				default:
					m_error = true;
				}
			}
		}
	}
	//--------------------------------------------------------------------
	// Title: void CRPNCalc::neg()
	// Description: 	resets the top element of the stack to it's negative
	// Called By: main(), testhelper
	// Calls: STL - push_front()
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::neg()
	{
		double num = 0.0;
		unary_prep(num);
		if (!m_error)
			m_stack.push_front(-num);
	}

	//--------------------------------------------------------------------
	// Title: void CRPNCalc::rotateDown()
	// Description: removes the bottom of the stack and adds it to the top
	// Called By: main(), testhelper
	// Calls: STL - empty(), back(), push_front()
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::rotateDown()
	{
		if (!m_stack.empty())
		{
			double temp = m_stack.back();
			m_stack.pop_back();
			m_stack.push_front(temp);
		}
		else
			m_error = true;
		
	}

	//--------------------------------------------------------------------
	// Title: void CRPNCalc::rotateUp()
	// Description: removes the top of the stack and adds it to the bottom
	// Called By: main(), testhelper
	// Calls: STL - front(), empty(), push_back()
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::rotateUp()
	{
		if (!m_stack.empty())
		{
			double temp = m_stack.front();
			m_stack.pop_front();
			m_stack.push_back(temp);
		}
		else
			m_error = true;
	}

	//--------------------------------------------------------------------
	// Title: void CRPNCalc::runProgram()
	// Description: runs the program in m_program 
	// Called By: parse()
	// Calls: parse(), STL - empty(), begin(), end()
	// Parameters: none
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::runProgram()
	{
		if (this->m_program.empty()) {
			m_error = true;
		}
		else {
			list<string>::iterator it = m_program.begin();
			string temp = m_buffer;
			while (it != m_program.end())
			{
				m_buffer = *it++;
				parse();
			}
			m_buffer = temp;
		}
	}

	//--------------------------------------------------------------------
	// Title: void CRPNCalc::setReg(int reg)
	// Description: gets the value from the top of the stack
	//	  and places it into the given register
	// Called By: parse()
	// Calls: unary_prep()
	// Parameters: int reg - registry number
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::setReg(int reg)
	{
		if (reg < 0 || reg > 9)
			m_error = true;
		else
		{
			double num = 0.0;
			unary_prep(num);
			m_registers[reg] = num;
		}
	}

	//--------------------------------------------------------------------
	// Title: void CRPNCalc::input(istream &istr)
	// Description: 	inputs a line from the given stream
	// Called By: run(), operator>>
	// Calls: parse(), STL - getline()
	// Parameters: istream & istr, in stream reference
	// Returns: none
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	void CRPNCalc::input(istream &istr)
	{
		getline(istr, m_buffer);
		m_instrStream.str(m_buffer);
		parse();
	}

	//--------------------------------------------------------------------
	// Title: ostream &operator <<(ostream &ostr, CRPNCalc &calc)
	// Description: ostream's << defined for CRPNCalc
	// Called By: --
	// Calls: print()
	// Parameters: ostream& ostr, CRPNCalc & calc - outstream and calculator object to print
	// Returns: ostream&
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	// ----------------------------------------------------------------------------
	//	ostream's << defined for CRPNCalc
	// ----------------------------------------------------------------------------
	ostream &operator <<(ostream &ostr, CRPNCalc &calc)
	{
		calc.print(ostr);
		return ostr;
	}

	//--------------------------------------------------------------------
	// Title: istream &operator >> (istream &istr, CRPNCalc &calc)
	// Description: istream's >> defined for CRPNCalc
	// Called By: --
	// Calls: input()
	// Parameters: istream& ostr, CRPNCalc & calc - istream and calculator object to input
	// Returns: istream&
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	istream &operator >> (istream &istr, CRPNCalc &calc)
	{
		calc.input(istr);
		return istr;
	}

	//--------------------------------------------------------------------
	// Title: string CRPNCalc::getToken()
	// Description: gets first character of buffer
	// Called By: parse(), loadprogram(), savetofile(), recordprogram()
	// Calls: STL - begin(), end(), iswspace()
	// Parameters: none
	// Returns: string
	// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNCalcStart.cpp
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment
	//--------------------------------------------------------------------
	string CRPNCalc::getToken()
	{
		string::iterator it1 = m_buffer.begin();
		string::iterator it2;
		// skip over all white space
		if (!m_buffer.empty())
			while (iswspace(*it1))
			{
				it1++;
				if (it1 == m_buffer.end())
					break;
			}
		// process string
		if (it1 != m_buffer.end())
		{
			bool isNegative = *it1 == '-';
			bool isNumeric = isdigit(*it1) || *it1 == '.' || isNegative;
			string::iterator it2 = it1;
			while (!iswspace(*it2) && ((
				isNumeric == bool(isdigit(*it2)) || isNumeric == (*it2 == '.' || (*it2 == '-' && isNegative))) || (isNegative && bool(isdigit(*it2)))
			)) {
				it2++;
				if (it2 == m_buffer.end())
					break;
			}
			string returnVal(it1, it2);
			if(it2 != m_buffer.end())
				while (iswspace(*it2))
				{
					it2++;
					if (it2 == m_buffer.end())
						break;
				}
			m_buffer = string(it2, m_buffer.end());
			return returnVal;
		}
		return "";
	}
	void CRPNCalc::sortStack()
	{
		if (m_stack.begin() != m_stack.end()) {
			std::sort(m_stack.begin(), m_stack.end(), [](const int &a, const int &b) -> bool { return a > b; });
			showStack();
		}
		else
			m_error = true;
	}

	void CRPNCalc::showStack()
	{
		stringstream stream;
		stream << '[';
		for_each(m_stack.begin(), m_stack.end(), [&](const int i) { stream << '(' << i << ")>"; });
		stream << ']';
		m_commandOutput = stream.str();
	}
	void CRPNCalc::swapStackReg()
	{
		if (m_stack.size() <= 10) {
			auto temp = vector<double>(10);
			copy(m_stack.begin(), m_stack.end(), temp.begin());
			copy(begin(m_registers), begin(m_registers) + m_stack.size(), m_stack.begin());
			//copy(temp.begin(), temp.begin() + m_stack.size(), begin(m_registers)); // C4996
			for (int i = 0; i < m_stack.size(); i++)
				m_registers[i] = temp[i];
		} else {
			m_error = true;
		}
	}
	void CRPNCalc::transformStack(short direction)
	{
	}
}
