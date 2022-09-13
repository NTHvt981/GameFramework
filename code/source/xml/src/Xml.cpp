#include "Xml/Xml.h"

namespace xml
{

Xml::Xml(std::weak_ptr<files::IFileSystem> i_fileSystem)
	: m_fileSystem(i_fileSystem)
{
}

void Xml::Initialize()
{
}

Xml::~Xml()
{
}

} // namespace xml