#pragma once

#include <string>

namespace del2rec
{
	class FileOperationError
	{
	public:
		explicit FileOperationError(int err_num);
		virtual ~FileOperationError();
	public:
		int GetNum() const;
		const std::wstring GetDescription() const;
		static const std::wstring GetDescription(int err_num);
	private:
		int m_errNum;
	};

}