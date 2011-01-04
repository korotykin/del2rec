// Del2RecVC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	int res = 0;
	bool files_only = false;
	int l = 0;
	for(int i = 1; i < argc; i++)
	{
		if((argv[i][0] == '-') || (argv[i][0] == '/'))
		{
			if(tolower(argv[i][1]) == 'f')
				files_only = true;
		}
		else
		{
			char absPath[256];
			if(_fullpath(absPath, argv[i], 255) != 0)
				l += strlen(absPath);
			l++;
		}
	}
	if(l > 0)
	{
		l++;
		char *ff = new char[l];
		char *_f = ff;
		for(int i = 1; i < argc; i++)
		{
			if(((argv[i][0] != '-') && (argv[i][0] != '/')) || (tolower(argv[i][1]) != 'f'))
			{
				char absPath[256];
				if(_fullpath(absPath, argv[i], 255) != 0)
					for(char *p = absPath; *p != 0; p++, _f++)
						*_f = *p;
				*_f = 0;
				_f++;
			}
		}
		*_f = 0;
		SHFILEOPSTRUCT arg_fo;
		arg_fo.hwnd = 0;
		arg_fo.wFunc = FO_DELETE;
		arg_fo.pFrom = ff;
		arg_fo.pTo = 0;
		arg_fo.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI;
		if(files_only)
			arg_fo.fFlags |= FOF_FILESONLY;
		res = ::SHFileOperation(&arg_fo);
		delete[] ff;
	}
	else
	{
		printf("\nDeleting one or more files to Recycle Bin"
			"\nUsage: Del2Rec [disk:][path]file_name [-r]"
			"\n-r or /r - recursing");
	}
	return res;
}

