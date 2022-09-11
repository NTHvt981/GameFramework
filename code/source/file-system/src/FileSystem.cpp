#include "FileSystem/FileSystem.h"
#include <windows.h>

data_types::String GetApplicationFolderPath(const data_types::String& i_demiliter);

namespace files
{

////////////////////////////////////////////////////////////////////////////////

FileSystem::FileSystem()
{

}

////////////////////////////////////////////////////////////////////////////////

FileSystem::~FileSystem()
{

}

////////////////////////////////////////////////////////////////////////////////

void FileSystem::Initialize()
{
	m_initializeFlag.Set();

	FolderDirectory newValue({});
	newValue.SetFolders(GetApplicationFolderPath("//"));
	m_applicationFolderDirectory.Set(newValue);
}

////////////////////////////////////////////////////////////////////////////////

void Initialize()
{

}

////////////////////////////////////////////////////////////////////////////////

void FileSystem::WriteTextFile(const FileId i_fileId)
{
}

////////////////////////////////////////////////////////////////////////////////

void FileSystem::ReadTextFile(const FileId i_fileId)
{
}

////////////////////////////////////////////////////////////////////////////////

data_types::String FileSystem::GetFileDirectory(const FileId i_fileId) const
{
	return data_types::String();
}

////////////////////////////////////////////////////////////////////////////////

data_types::String FileSystem::ToPath(const FolderDirectory& i_folderDirectory) const
{
	return (m_applicationFolderDirectory.Get() + (i_folderDirectory)).ToString();
}

////////////////////////////////////////////////////////////////////////////////

data_types::String FileSystem::ToPath(const FileDirectory& i_fileDirectory) const
{
	FileDirectory result;
	result.folderDirectory = m_applicationFolderDirectory.Get() + (i_fileDirectory.folderDirectory);
	return result.ToString();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace files

data_types::String GetApplicationFolderPath(const data_types::String& i_demiliter)
{
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);

	data_types::String result(buffer);
	std::wstring::size_type pos = result.FindLastOf(i_demiliter);
	return data_types::String(buffer).SubString(0, pos);
}