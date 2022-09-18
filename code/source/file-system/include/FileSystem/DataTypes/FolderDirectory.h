#pragma once
#include "Delimiter.h"
#include <list>

namespace files
{
struct Folder;

class FolderDirectory
{
public:
	FolderDirectory(std::initializer_list<Folder> i_folders);
	FolderDirectory(const std::list<Folder>& i_folders);
	FolderDirectory operator+(const FolderDirectory& i_other) const;
	void operator=(const FolderDirectory& i_other);
	void SetFolders(core::String i_path);
	core::String ToString() const;
	void Optimize();

private:
	std::list<Folder> m_folders;
	const Delimiter m_delimiter;
};

} // namespace files