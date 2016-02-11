//
// VisualStudioのデバッグコンソールに
// coutできるようにする
// 

#include <windows.h>
#include <iostream>
#include <string>
#include <streambuf>
#include <vector>


// デバッグコンソールにcoutする
class DbgStreambuf : public std::streambuf {
	std::vector<TCHAR> str_;
	// ↑OutputDebugString()がcharではなくTCHARを要求する

public:
	int_type overflow(int_type c = EOF) {
		str_.push_back(c);
		return c;
	}

	int sync() {
		str_.push_back('\0');

		OutputDebugString(&str_[0]);
		str_.clear();
		return 0;
	}
};

