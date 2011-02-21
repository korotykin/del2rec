#pragma once

namespace del2rec
{

class DescrOfError;

class PrintOfErrors
{
public:
	PrintOfErrors();
	virtual ~PrintOfErrors();
public:
	void printError(const DescrOfError & error);
	bool GetWasPrinted() const;
private:
	bool m_WasPrinted;
};

}

