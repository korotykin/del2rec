#include "CnvWstrToStr.h"
#include "Windows.h"

using std::string;
using std::wstring;

CnvWstrToStr::CnvWstrToStr(const unsigned int a_CodePage): m_CodePage(a_CodePage)
{
}

CnvWstrToStr::~CnvWstrToStr()
{
}

const string CnvWstrToStr::ToString(const wstring a_Src)
{
	string str;
	int lengthDesc = ::WideCharToMultiByte(m_CodePage, 0, a_Src.c_str(), -1, NULL, 0, NULL, NULL);
	str.resize(lengthDesc, '\0');
	lengthDesc = ::WideCharToMultiByte(m_CodePage, 0, a_Src.c_str(), -1, &str[0], lengthDesc, NULL, NULL);
	str.resize(lengthDesc - 1, '\0');
	return str;
}