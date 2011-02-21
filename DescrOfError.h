#pragma once

#include <string>

namespace del2rec
{
	class DescrOfError
	{
	public:
		DescrOfError(const std::wstring & FileName, const std::wstring & FullFileName, const std::wstring & ErrorDescription);
		virtual ~DescrOfError();
	public:
		void print() const;
	private:
		std::wstring m_FileName;
		std::wstring m_FullFileName;
		std::wstring m_ErrorDescription;
	};

}
