// Del2RecVC.cpp : Defines the entry point for the console application.
//

#include <string.h>
#include <shlobj.h>
#include <stdio.h>
#include <shellapi.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include "FileOperationError.h"
#include "ErrorWithMessage.h"

using std::endl;
using std::wstring;
using std::cerr;

namespace del2rec {
	enum {NoError = 0, OperError = 1, ArgError = 2};
	void print_help(std::ostream & output)
	{
		output << endl << "Deleting one or more files to Recycle Bin" << endl
			<< "Usage: Del2Rec [disk:][path]file_name" << endl;
	}

	void delete_files(const wchar_t * const files) // throw FileOperationError
	{
		SHFILEOPSTRUCT arg_fo;
		arg_fo.hwnd = 0;
		arg_fo.wFunc = FO_DELETE;
		arg_fo.pFrom = files;
		arg_fo.pTo = 0;
		arg_fo.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI;
		const int res = ::SHFileOperationW(&arg_fo);
		if (res != 0) throw(FileOperationError(res));
		if (arg_fo.fAnyOperationsAborted == TRUE) throw(ErrorWithMessage(L"Operation aborted by user"));
	}

	void delete_file(wstring FullFileName)
	{
		const size_t sizeName = FullFileName.size();
		FullFileName.resize(sizeName + 1, 0); // add extra '0' to string
		delete_files(FullFileName.c_str());
	}
	struct DeleteError
	{
		wstring m_FileName;
		wstring m_FullFileName;
		wstring m_ErrorDescription;
		DeleteError(const wstring & FileName, const wstring & FullFileName, const wstring & ErrorDescription)
			: m_FileName(FileName), m_FullFileName(FullFileName), m_ErrorDescription(ErrorDescription)
		{}
	};
}

using namespace del2rec;

int wmain(const int argc, const wchar_t* const argv[])
{
	if (argc <= 1)
	{
		print_help(std::cout);
		return NoError;
	}
	bool isDeleted = false;
	std::vector<DeleteError> Errors;
	for(int i = 1; i < argc; ++i)
	{
		if((argv[i][0] == '-') || (argv[i][0] == '/')) continue; // skip options
		const wchar_t * const absPath = ::_wfullpath(NULL, argv[i], 0);
		if(absPath == 0)
		{
			Errors.push_back(DeleteError(argv[i], L"", L"can't get full path"));
			continue;
		}
		const wstring absFullPath(absPath);
		::free((void *)absPath);
		try
		{
			delete_file(absFullPath);
			isDeleted = true;
		}
		catch (const D2RError & error)
		{
			Errors.push_back(DeleteError(argv[i], absFullPath, error.GetDescription()));
		}
	}
	if (!isDeleted && Errors.empty())
	{
		print_help(cerr);
		return ArgError;
	}
	if (!Errors.empty())
	{
		const UINT cpo = ::GetConsoleOutputCP();
		//const UINT cpi = ::GetConsoleCP();
		cerr << endl;
		for (std::vector<DeleteError>::const_iterator i = Errors.begin(); i != Errors.end(); ++i)
		{
			const wstring errDescUTF16(L"error: " + i->m_ErrorDescription);
			std::string strDesc;
			int lengthDesc = ::WideCharToMultiByte(cpo, 0, errDescUTF16.c_str(), -1, NULL, 0, NULL, NULL);
			strDesc.resize(lengthDesc);
			lengthDesc = ::WideCharToMultiByte(cpo, 0, errDescUTF16.c_str(), -1, &strDesc[0], lengthDesc, NULL, NULL);
			cerr << strDesc;
		}
		cerr << endl;
		return OperError;
	}
	return NoError;
}

