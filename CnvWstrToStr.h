#pragma once

#include <string>

class CnvWstrToStr
{
public:
	explicit CnvWstrToStr(unsigned int a_CodePage);
	virtual ~CnvWstrToStr();
public:
	const std::string ToString(std::wstring a_Src);
private:
	unsigned int m_CodePage;
};

