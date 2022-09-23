#include "Xml/CommonParser.h"
#include "Core/Identifiers/TextureId.h"
#include "tinyxml2.h"
#include "TexureParser.h"

namespace xml
{

void Parse(tinyxml2::XMLElement* i_element, std::vector<graphics::Texture>& o_value);
void Parse(const tinyxml2::XMLElement* i_element, graphics::Texture& o_value);
void Parse(const tinyxml2::XMLElement* i_element, ids::TextureId& o_value);

std::vector<graphics::Texture> LoadFile(const char* i_filePath)
{
	std::vector<graphics::Texture> result;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(i_filePath);
	ParseList<graphics::Texture>(doc.FirstChildElement("Textures"), result, "Texture", [](tinyxml2::XMLElement* itemElement, graphics::Texture& o_value)
		{
			Parse(itemElement, o_value);
		}
	);

	return result;
}

void Parse(tinyxml2::XMLElement* i_element, std::vector<graphics::Texture>& o_value)
{
	tinyxml2::XMLElement* textureElement = i_element->FirstChildElement("Texture");
	while (textureElement != nullptr)
	{
		graphics::Texture value;
		Parse(textureElement, value);
		o_value.push_back(value);
		
		i_element->DeleteChild(textureElement);
		textureElement = i_element->FirstChildElement("Texture");
	}
}

void Parse(const tinyxml2::XMLElement* i_element, graphics::Texture& o_value)
{
	Parse(i_element->FirstChildElement("Id"), o_value.id);
	Parse(i_element->FirstChildElement("File"), o_value.filePath);
	Parse(i_element->FirstChildElement("Size"), o_value.size);
}

void Parse(const tinyxml2::XMLElement* i_element, ids::TextureId& o_value)
{
	uint64_t temp;
	Parse(i_element, temp);
	o_value = static_cast<ids::TextureId>(temp);
}

} // namespace xml