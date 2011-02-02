#pragma once

#include "D2RError.h"
#include <string>

namespace del2rec
{

	class ErrorWithMessage: public D2RError
	{
	public:
		explicit ErrorWithMessage(const std::wstring & a_Message);
		virtual ~ErrorWithMessage();
	public:
		virtual const std::wstring GetDescription() const;
	private:
		std::wstring m_Message;
	};

}