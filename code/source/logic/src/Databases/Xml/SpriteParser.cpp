#include "SpriteParser.h"
#include "Core/DataTypes/SpriteDef.h"
#include "Databases/Xml/CommonParser.h"
#include "tinyxml2.h"

namespace xml
{

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, graphics::SpriteDef& o_value);

////////////////////////////////////////////////////////////////////////////////

std::vector<graphics::SpriteDef> LoadSpritesFile(const char* i_filePath)
{
	std::vector<graphics::SpriteDef> result;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(i_filePath);
	ParseList<graphics::SpriteDef>(doc.FirstChildElement("Sprites"), result, "Sprite", 
		[](tinyxml2::XMLElement* itemElement, graphics::SpriteDef& o_value)
		{
			Parse(itemElement, o_value);
		}
	);

	return result;
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, graphics::SpriteDef& o_value)
{
	Parse(i_element->FirstChildElement("Id"), o_value.id);
	Parse(i_element->FirstChildElement("Boundary"), o_value.textureBoundary);
	Parse(i_element->FirstChildElement("Origin"), o_value.origin);
	Parse(i_element->FirstChildElement("TextureId"), o_value.textureId);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace xml
