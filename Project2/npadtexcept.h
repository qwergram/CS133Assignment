#pragma once
#include <exception>
#include <stdexcept>
using namespace std;

namespace NP_ADT {
	class MethodNotSupported : public runtime_error {
	public:
		MethodNotSupported() : runtime_error("method not supported") {}
		virtual const char* what() const throw () {
			return runtime_error::what();
		}
	};
}