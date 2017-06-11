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
//	
//	  related functions:
//				ostream &operator <<(ostream &ostr, const CRPNCalc &calc)
//    				istream &operator >>(istream &istr, CRPNCalc &calc)
//
//    History Log:
//                           
// ----------------------------------------------------------------------------	
namespace P4_RPNCALC
{
	// ----------------------------------------------------------------------------
	//	constructor
	// ----------------------------------------------------------------------------
	CRPNCalc::CRPNCalc(bool on) : m_on(on), m_error(false), m_helpOn(true),
		m_programRunning(false)
	{
		for (int i = 0; i < NUMREGS; i++)
			m_registers[i] = 0.0;
		if (m_on)
			run();
	}

	// ----------------------------------------------------------------------------
	//	starts the calculator running
	// ----------------------------------------------------------------------------
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

	// ----------------------------------------------------------------------------
	//	prints out calculator screen
	// ----------------------------------------------------------------------------
	void CRPNCalc::print(ostream& ostr)
	{
		double d = 0.0;
		ostr << "[RPN Programmable Calculator] by ctongGH, qwergram, TabithaRoemish & AntonioCastelli" << endl;
		if (m_helpOn)
			cout << helpMenu;
		else
			cout << endl << endl << endl;
		cout << line;
		if (!m_stack.empty())
		{
			this->m_lastOutput = to_string(m_stack.front());
			ostr << this->m_lastOutput;
		}
		ostr << endl << endl;
		if (m_error)
		{
			this->m_lastOutput = "<<error>>";
			ostr << this->m_lastOutput << endl;
			m_error = false;
		}
	}

	// ----------------------------------------------------------------------------
	//	parses the next command from m_instrStream
	// ----------------------------------------------------------------------------
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
				m_on = false;;
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
				if (token.back() > 47 && token.back() < 48 + NUMREGS)
					getReg(token.back() - 48);
				else
					m_error = true;
				break;
			case 'S':
				if (token.back() > 47 && token.back() < 48 + NUMREGS)
					setReg(token.back() - 48);
				else
					m_error = true;
				break;
			default:
				m_error = true;
			}
		}
	}

	// ----------------------------------------------------------------------------
	//	if possible, pops top 2 elements from the stack, adds them
	//	  and pushes the result onto the stack
	// ----------------------------------------------------------------------------	
	void CRPNCalc::add()
	{
		double num1 = 0.0;
		double num2 = 0.0;
		binary_prep(num1, num2);
		if (!m_error)
			m_stack.push_front(num1 + num2);
	}

	// ----------------------------------------------------------------------------
	//	if possible, pops top 2 elements from the stack, subtracts them
	//	  and pushes the result onto the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::subtract()
	{
		double num1 = 0.0;
		double num2 = 0.0;
		binary_prep(num1, num2);
		if (!m_error)
			m_stack.push_front(num1 - num2);
	}

	// ----------------------------------------------------------------------------
	//	if possible, pops top 2 elements from the stack, multiplies them
	//	  and pushes the result onto the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::multiply()
	{
		double num1 = 0.0;
		double num2 = 0.0;
		binary_prep(num1, num2);
		if (!m_error)
			m_stack.push_front(num1 * num2);
	}

	// ----------------------------------------------------------------------------
	//	if possible, pops top 2 elements from the stack, divides them
	//	  and pushes the result onto the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::divide()
	{
		double num1 = 0.0;
		double num2 = 0.0;
		binary_prep(num1, num2);
		if (!m_error)
			m_stack.push_front(num1 / num2);
	}

	// ----------------------------------------------------------------------------
	//	if possible, pops top 2 elements from the stack,
	//	  raises one element to the other power
	//	  and pushes the result onto the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::exp()
	{
		double num1 = 0.0;
		double num2 = 0.0;
		binary_prep(num1, num2);
		if (!m_error)
			m_stack.push_front(pow(num1, num2));
	}

	// ----------------------------------------------------------------------------
	//	if possible, pops top 2 elements from the stack, mods them
	//	  and pushes the result onto the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::mod()
	{
		double num1 = 0.0;
		double num2 = 0.0;
		binary_prep(num1, num2);
		if (!m_error)
			m_stack.push_front(fmod(num1, num2));
	}

	// ----------------------------------------------------------------------------
	//	sets the args to the popped values from the stack, if possible
	//	  set error state otherwise
	// ----------------------------------------------------------------------------

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

	// ----------------------------------------------------------------------------
	//	sets the arg to the popped value from the stack, if possible
	//	  sets error state otherwise
	// ----------------------------------------------------------------------------
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

	// ----------------------------------------------------------------------------
	//	removes the top element from the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::clearEntry()
	{
		double temp = 0.0;
		unary_prep(temp);
	}

	// ----------------------------------------------------------------------------
	//	empties the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::clearAll()
	{
		while (!m_stack.empty())
			m_stack.pop_front();
	}

	// ----------------------------------------------------------------------------
	//	pushes the given register's value onto the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::getReg(int reg)
	{
		m_stack.push_front(m_registers[reg]);
	}

	// ----------------------------------------------------------------------------
	//	retrieves the filename from the user and loads it into m_program
	// ----------------------------------------------------------------------------
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

	// ----------------------------------------------------------------------------
	//	asks the user for a filename and saves m_program to that file
	// ----------------------------------------------------------------------------
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

	// ----------------------------------------------------------------------------
	//	takes command-line input and loads it into m_program 
	// ----------------------------------------------------------------------------
	void CRPNCalc::recordProgram()
	{
		string token = "hello world";
		m_program.clear();
		unsigned macro_size = 0;
		while (!(token.size() == 1 && toupper(token.front() == 'P')))
		{
			if (m_buffer.empty())
				cout << macro_size++ << "> ";
				getline(cin, m_buffer);
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
					if (token.back() > 47 && token.back() < 48 + NUMREGS)
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

	// ----------------------------------------------------------------------------
	//	resets the top element of the stack to it's negative
	// ----------------------------------------------------------------------------
	void CRPNCalc::neg()
	{
		double num = 0.0;
		unary_prep(num);
		m_stack.push_front(-num);
	}

	// ----------------------------------------------------------------------------
	//	removes the bottom of the stack and adds it to the top
	// ----------------------------------------------------------------------------
	void CRPNCalc::rotateDown()
	{
		if (!m_stack.empty())
		{
			double temp = m_stack.back();
			m_stack.pop_back();
			m_stack.push_front(temp);
		}
	}

	// ----------------------------------------------------------------------------
	//	removes the top of the stack and adds it to the bottom
	// ----------------------------------------------------------------------------
	void CRPNCalc::rotateUp()
	{
		if (!m_stack.empty())
		{
			double temp = m_stack.front();
			m_stack.pop_front();
			m_stack.push_back(temp);
		}
	}

	// ----------------------------------------------------------------------------
	//	runs the program in m_program 
	// ----------------------------------------------------------------------------
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

	// ----------------------------------------------------------------------------
	//	gets the value from the top of the stack
	//	  and places it into the given register
	// ----------------------------------------------------------------------------
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

	// ----------------------------------------------------------------------------
	//	inputs a line from the given stream
	// ----------------------------------------------------------------------------
	void CRPNCalc::input(istream &istr)
	{
		getline(istr, m_buffer);
		m_instrStream.str(m_buffer);
		parse();
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
	istream &operator >> (istream &istr, CRPNCalc &calc)
	{
		calc.input(istr);
		return istr;
	}

	string CRPNCalc::getToken()
	{
		string::iterator it1 = m_buffer.begin();
		string::iterator it2;
		if (!m_buffer.empty())
			while (iswspace(*it1))
			{
				it1++;
				if (it1 == m_buffer.end())
					break;
			}
		if (it1 != m_buffer.end())
		{
			string::iterator it2 = it1;
			while (!iswspace(*it2))
			{
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
}
