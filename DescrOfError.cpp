#include "DescrOfError.h"
#include "CnvWstrToStr.h"
#include <iostream>
#include <iomanip>
#include <windows.h>

using std::wstring;
using std::string;
using std::cerr;
using std::endl;

namespace { namespace Helper
{
	string RemoveLastEOL(string src);
}}

namespace del2rec
{

DescrOfError::DescrOfError(const wstring & a_FileName, const wstring & a_FullFileName, const wstring & a_ErrorDescription):
m_FileName(a_FileName), m_FullFileName(a_FullFileName), m_ErrorDescription(a_ErrorDescription)
{
}

DescrOfError::~DescrOfError()
{
}

void DescrOfError::print() const
{
	static CnvWstrToStr cnv(::GetConsoleOutputCP());
	//static CnvWstrToStr cnv(::GetConsoleCP());
	string strErrorDescription = cnv.ToString(m_ErrorDescription);
	strErrorDescription = Helper::RemoveLastEOL(strErrorDescription);
	cerr << "error: " << strErrorDescription << ", file name: " << cnv.ToString(m_FileName);
	if (m_FileName != m_FullFileName) cerr << ", full path: " << cnv.ToString(m_FullFileName);
	cerr << endl;
}

}

namespace { namespace Helper
{
	string RemoveLastEOL(string src)
	{
		size_t curPos = src.length() - 1;
		while((src[curPos] == '\r') || (src[curPos] == '\n')) --curPos;
		if (curPos < (src.length() - 1)) src.erase(curPos);
		return src;
	}
}}
