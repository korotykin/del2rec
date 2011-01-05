// Del2RecVC.cpp : Defines the entry point for the console application.
//

#include <string.h>
#include <shlobj.h>
#include <stdio.h>
#include <shellapi.h>
#include <stdlib.h>


int main(const int argc, const char* const argv[])
{
	int res = 0;
	int l = 0;
	for(int i = 1; i < argc; i++)
	{
		if((argv[i][0] == '-') || (argv[i][0] == '/')) continue; // skip options
		char * absPath = ::_fullpath(NULL, argv[i], 0);
		if(absPath == 0) continue; // error - wrong full path
		l += ::strlen(absPath);
		::free(absPath);
		++l;
	}
	if(l > 0)
	{
		++l;
		char *ff = new char[l];
		char *_f = ff;
		for(int i = 1; i < argc; i++)
		{
			if((argv[i][0] == '-') || (argv[i][0] == '/')) continue;
			char * absPath = ::_fullpath(NULL, argv[i], 0);
			if(absPath == 0) continue;
			for(const char *p = absPath; *p != 0; ++p, ++_f) *_f = *p;
			::free(absPath);
			*_f = 0;
			++_f;
		}
		*_f = 0;
		SHFILEOPSTRUCT arg_fo;
		arg_fo.hwnd = 0;
		arg_fo.wFunc = FO_DELETE;
		arg_fo.pFrom = ff;
		arg_fo.pTo = 0;
		arg_fo.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI;
		res = ::SHFileOperation(&arg_fo);
		delete[] ff;
	}
	else
	{
		::printf("\nDeleting one or more files to Recycle Bin"
			"\nUsage: Del2Rec [disk:][path]file_name");
	}
	return res;
}

