#pragma once
#include "IXml.h"
#include "FileSystem/IFileSystem.h"
#include <memory>

namespace xml
{

class Xml final: public IXml
{
public:
	Xml(std::weak_ptr<files::IFileSystem> i_fileSystem);
	void Initialize();
	~Xml();

private:
	std::weak_ptr<files::IFileSystem> m_fileSystem;
};

} // namespace xml