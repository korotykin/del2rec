#include "PrintOfErrors.h"
#include "DescrOfError.h"
#include <iostream>
#include <iomanip>

using std::cerr;
using std::endl;

namespace del2rec
{

PrintOfErrors::PrintOfErrors(): m_WasPrinted(false)
{
}

PrintOfErrors::~PrintOfErrors()
{
	if (m_WasPrinted) cerr << endl;
}

void PrintOfErrors::printError(const DescrOfError & error)
{
	if (!m_WasPrinted) {
		cerr << endl;
		m_WasPrinted = true;
	}
	error.print();
}

bool PrintOfErrors::GetWasPrinted() const
{
	return m_WasPrinted;
}

}
