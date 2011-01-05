// Del2RecVC.cpp : Defines the entry point for the console application.
//

#include <string.h>
#include <shlobj.h>
#include <stdio.h>
#include <shellapi.h>
#include <stdlib.h>
#include <vector>

void print_help()
{
	::printf("\nDeleting one or more files to Recycle Bin"
		"\nUsage: Del2Rec [disk:][path]file_name\n");
}

int main(const int argc, const char* const argv[])
{
	if (argc <= 1) {
		::print_help();
		return 0;
	}
	int length = 0;
	for(int i = 1; i < argc; ++i)
	{
		if((argv[i][0] == '-') || (argv[i][0] == '/')) continue; // skip options
		char * absPath = ::_fullpath(NULL, argv[i], 0);
		if(absPath == 0) continue; // error - wrong full path
		length += ::strlen(absPath);
		::free(absPath);
		++length;
	}
	if (length == 0) {
		::print_help();
		return 1;
	}
	++length;
	std::vector<char> files_buf(length);
	char *fbp = &files_buf[0];
	for(int i = 1; i < argc; ++i)
	{
		if((argv[i][0] == '-') || (argv[i][0] == '/')) continue;
		char * absPath = ::_fullpath(NULL, argv[i], 0);
		if(absPath == 0) continue;
		for(const char *p = absPath; *p != 0; ++p, ++fbp) *fbp = *p; // strcpy is not sutable
		::free(absPath);
		*fbp = 0;
		++fbp;
	}
	*fbp = 0;
	SHFILEOPSTRUCT arg_fo;
	arg_fo.hwnd = 0;
	arg_fo.wFunc = FO_DELETE;
	arg_fo.pFrom = &files_buf[0];
	arg_fo.pTo = 0;
	arg_fo.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI;
	return ::SHFileOperation(&arg_fo);
}

