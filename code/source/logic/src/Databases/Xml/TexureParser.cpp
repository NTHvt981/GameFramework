#include "TexureParser.h"
#include "Core/DataTypes/Texture.h"
#include "Databases/Xml/CommonParser.h"
#include "tinyxml2.h"

namespace xml
{

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, core::Texture& o_value);

////////////////////////////////////////////////////////////////////////////////

std::vector<core::Texture> LoadTexturesFile(const char* i_filePath)
{
	std::vector<core::Texture> result;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(i_filePath);
	ParseList<core::Texture>(doc.FirstChildElement("Textures"), result, "Texture", [](tinyxml2::XMLElement* itemElement, core::Texture& o_value)
		{
			Parse(itemElement, o_value);
		}
	);

	return result;
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, core::Texture& o_value)
{
	Parse(i_element->FirstChildElement("Id"), o_value.id);
	Parse(i_element->FirstChildElement("File"), o_value.filePath);
	Parse(i_element->FirstChildElement("Size"), o_value.size);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace xml
