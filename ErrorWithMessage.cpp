#include "ErrorWithMessage.h"

using std::wstring;

namespace del2rec
{

	ErrorWithMessage::ErrorWithMessage(const std::wstring & a_Message): m_Message(a_Message)
	{
	}


	ErrorWithMessage::~ErrorWithMessage()
	{
	}

	const wstring ErrorWithMessage::GetDescription() const
	{
		return m_Message;
	}
}