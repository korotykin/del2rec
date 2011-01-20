#pragma once

#include <string>

namespace del2rec
{

	class D2RError
	{
	public:
		D2RError();
		virtual ~D2RError();
	public:
		virtual const std::wstring GetDescription() const = 0;
	};

}