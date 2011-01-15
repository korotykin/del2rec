#include "FileOperationError.h"

namespace del2rec
{

FileOperationError::FileOperationError(const int a_errNum): m_errNum(a_errNum)
{
}

FileOperationError::~FileOperationError()
{
}

	int FileOperationError::GetNum() const
	{
		return m_errNum;
	}

	const std::wstring FileOperationError::GetDescription() const
	{
		return GetDescription(m_errNum);
	}

	const std::wstring FileOperationError::GetDescription(const int a_errNum)
	{
		switch (a_errNum) {
		case 0x71:
			return L"The source and destination files are the same file.";
			break;
		case 0x72:
			return L"Multiple file paths were specified in the source buffer, but only one destination file path.";
			break;
		case 0x73:
			return L"Rename operation was specified but the destination path is a different directory. Use the move operation instead.";
			break;
		case 0x74:
			return L"The source is a root directory, which cannot be moved or renamed.";
			break;
		case 0x75:
			return L"The operation was canceled by the user, or silently canceled if the appropriate flags were supplied to SHFileOperation.";
			break;
		case 0x76:
			return L"The destination is a subtree of the source.";
			break;
		case 0x78:
			return L"Security settings denied access to the source.";
			break;
		case 0x79:
			return L"The source or destination path exceeded or would exceed MAX_PATH.";
			break;
		case 0x7A:
			return L"The operation involved multiple destination paths, which can fail in the case of a move operation.";
			break;
		case 0x7C:
			return L"The path in the source or destination or both was invalid.";
			break;
		case 0x7D:
			return L"The source and destination have the same parent folder.";
			break;
		case 0x7E:
			return L"The destination path is an existing file.";
			break;
		case 0x80:
			return L"The destination path is an existing folder.";
			break;
		case 0x81:
			return L"The name of the file exceeds MAX_PATH.";
			break;
		case 0x82:
			return L"The destination is a read-only CD-ROM, possibly unformatted.";
			break;
		case 0x83:
			return L"The destination is a read-only DVD, possibly unformatted.";
			break;
		case 0x84:
			return L"The destination is a writable CD-ROM, possibly unformatted.";
			break;
		case 0x85:
			return L"The file involved in the operation is too large for the destination media or file system.";
			break;
		case 0x86:
			return L"The source is a read-only CD-ROM, possibly unformatted.";
			break;
		case 0x87:
			return L"The source is a read-only DVD, possibly unformatted.";
			break;
		case 0x88:
			return L"The source is a writable CD-ROM, possibly unformatted.";
			break;
		case 0xB7:
			return L"MAX_PATH was exceeded during the operation.";
			break;
		case 0x402:
			return L"An unknown error occurred. This is typically due to an invalid path in the source or destination.";
			break;
		case 0x10074:
			return L"Destination is a root directory and cannot be renamed.";
			break;
		}
		if (a_errNum & 0x10000) return L"An unspecified error occurred on the destination.";
		return L"An unspecified error occurred.";
	}
}