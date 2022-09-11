#include "stdafx.h"
#include "FileSystem/DataTypes/FolderDirectory.h"
#include "Core/Helpers/StringHelper.h"
#include <iterator>

namespace files
{

////////////////////////////////////////////////////////////////////////////////

FolderDirectory::FolderDirectory(std::initializer_list<Folder> i_folders)
	: m_folders(i_folders)
	, m_delimiter(Delimiter())
{
}

////////////////////////////////////////////////////////////////////////////////

FolderDirectory::FolderDirectory(const std::list<Folder>& i_folders)
	: m_folders(i_folders)
	, m_delimiter(Delimiter())
{
}

////////////////////////////////////////////////////////////////////////////////

FolderDirectory FolderDirectory::operator+(const FolderDirectory& i_other) const
{
	std::list<Folder> folders;
	std::copy(m_folders.begin(), m_folders.end(), std::back_inserter(folders));
	std::copy(i_other.m_folders.begin(), i_other.m_folders.end(), std::back_inserter(folders));

	FolderDirectory result(folders);
	result.Optimize();

	return result;
}

////////////////////////////////////////////////////////////////////////////////

void FolderDirectory::operator=(const FolderDirectory& i_other)
{
	m_folders = i_other.m_folders;
}

////////////////////////////////////////////////////////////////////////////////

void FolderDirectory::SetFolders(data_types::String i_path)
{
	std::vector<data_types::String> folderNames = data_types::string::Split(i_path, m_delimiter.GetName());
	for (const data_types::String& folderName : folderNames)
	{
		m_folders.push_back(Folder{ folderName });
	}
}

////////////////////////////////////////////////////////////////////////////////

data_types::String FolderDirectory::ToString() const
{
	std::string result;
	const std::string& stdDeli = m_delimiter.GetName().ToStdStr();

	for (const Folder& folder : m_folders)
	{
		result += folder.name.ToStdStr();
		result += stdDeli;
	}

	if (result.empty())
	{
		return data_types::String();
	}

	return result;
}

////////////////////////////////////////////////////////////////////////////////

void FolderDirectory::Optimize()
{
	std::list<Folder> folders;

	for (const Folder& folder : m_folders)
	{
		const bool notEmpty = folders.empty() == false;
		if (folder.name == BackwardFolder.name && notEmpty)
		{
			folders.pop_back();
		}
		else
		{
			folders.push_back(folder);
		}
	}

	m_folders = folders;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace files