//
// VisualStudio�̃f�o�b�O�R���\�[����
// cout�ł���悤�ɂ���
// 

#include <windows.h>
#include <iostream>
#include <string>
#include <streambuf>
#include <vector>


// �f�o�b�O�R���\�[����cout����
class DbgStreambuf : public std::streambuf {
	std::vector<TCHAR> str_;
	// ��OutputDebugString()��char�ł͂Ȃ�TCHAR��v������

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

