#pragma once

#include <string>
#include "D2RError.h"

namespace del2rec
{
	class FileOperationError: public D2RError
	{
	public:
		explicit FileOperationError(int err_num);
		virtual ~FileOperationError();
	public:
		virtual const std::wstring GetDescription() const;
		int GetNum() const;
		static const std::wstring GetDescription(int err_num);
	private:
		int m_errNum;
	};

}