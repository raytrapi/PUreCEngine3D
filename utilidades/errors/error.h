#ifndef _ERROR
#define _ERROR
#include <string>
struct Error {
	int code;
	std::string message;
	Error(int c, std::string m) :code(c), message(m) {};
	//Error(int c, const char * m) :code(c), message(m) {};
	Error(Error& e) {
		code = e.code;
		message = e.message;
	}
	Error(Error&& e) {
		code = e.code;
		message = e.message;
	}
};
#endif // !_ERROR
