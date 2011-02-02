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

namespace del2rec {
	enum {NoError = 0, OperError = 1, ArgError = 2};
	void print_help(std::wostream & output)
	{
		output << endl << L"Deleting one or more files to Recycle Bin" << endl
			<< L"Usage: Del2Rec [disk:][path]file_name" << endl;
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
}

int wmain(const int argc, const wchar_t* const argv[])
{
	if (argc <= 1) {
		del2rec::print_help(std::wcout);
		return del2rec::NoError;
	}
	int length = 0;
	for(int i = 1; i < argc; ++i)
	{
		if((argv[i][0] == '-') || (argv[i][0] == '/')) continue; // skip options
		wchar_t * const absPath = ::_wfullpath(NULL, argv[i], 0);
		if(absPath == 0) continue; // error - wrong full path
		length += ::wcslen(absPath);
		::free(absPath);
		++length;
	}
	if (length == 0) {
		del2rec::print_help(std::wcerr);
		return del2rec::ArgError;
	}
	++length;
	std::vector<wchar_t> files_buf(length);
	wchar_t *fbp = &files_buf[0];
	for(int i = 1; i < argc; ++i)
	{
		if((argv[i][0] == '-') || (argv[i][0] == '/')) continue;
		wchar_t * const absPath = ::_wfullpath(NULL, argv[i], 0);
		if(absPath == 0) continue;
		for(const wchar_t *p = absPath; *p != 0; ++p, ++fbp) *fbp = *p; // strcpy is not sutable
		::free(absPath);
		*fbp = 0;
		++fbp;
	}
	*fbp = 0;
	try
	{
		del2rec::delete_files(&files_buf[0]);
		return del2rec::NoError;
	}
	catch (const del2rec::D2RError & error)
	{
		std::wcerr << endl << L"error: " << error.GetDescription() << endl;
		return del2rec::OperError;
	}
}

