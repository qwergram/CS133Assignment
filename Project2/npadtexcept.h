//-----------------------------------------------------------------------------
//   Title: methodnotsupported exception
//   Description: This file contains the class 
//				  declarations for MethodNotSupported
//
//   Programmer: 
//    Norton Pengra
// 
//   Date: original: Spring 2017
//   Version: 1.10
//
//   Environment: Intel Xeon PC
//     Software: MS Windows 10 for execution;
//     Compiles under Microsoft Visual C++.Net 2017
//
//   class publicqueue : (inherits from cdll)
//
//     Methods:
// 
//       inline: 
//         const char* what(); -- pass through for runtime_error's what()
//
//
//   History Log:
//	   May 18, 2017, NP completed version 1.10
//-----------------------------------------------------------------------------

#pragma once
#include <exception>
#include <stdexcept>
using namespace std;

namespace NP_ADT {
	class MethodNotSupported : public runtime_error {
	public:
		MethodNotSupported() : runtime_error("method not supported") {}
		
		// Not strictly neccessary
		virtual const char* what() const throw () {
			return runtime_error::what();
		}
	};
}