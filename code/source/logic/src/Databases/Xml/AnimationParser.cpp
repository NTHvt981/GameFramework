#include "AnimationParser.h"
#include "tinyxml2.h"

namespace xml
{

////////////////////////////////////////////////////////////////////////////////

void Parse(tinyxml2::XMLElement* i_element, core::AnimationDef& o_value);
void Parse(const tinyxml2::XMLElement* i_element, core::AnimationFrameDef& o_value);

////////////////////////////////////////////////////////////////////////////////

std::vector<core::AnimationDef> LoadAnimationsFile(const char* i_filePath)
{
	std::vector<core::AnimationDef> result;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(i_filePath);
	ParseList<core::AnimationDef>(doc.FirstChildElement("Animations"), result, "Animation",
		[](tinyxml2::XMLElement* itemElement, core::AnimationDef& o_value)
		{
			Parse(itemElement, o_value);
		}
	);

	return result;
}

////////////////////////////////////////////////////////////////////////////////

void Parse(tinyxml2::XMLElement* i_element, core::AnimationDef& o_value)
{
	Parse(i_element->FirstChildElement("Id"), o_value.id);
	ParseList<core::AnimationFrameDef>(i_element->FirstChildElement("Frames"), o_value.frames, "Frame",
		[](tinyxml2::XMLElement* itemElement, core::AnimationFrameDef& o_value)
		{
			Parse(itemElement, o_value);
		}
	);
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, core::AnimationFrameDef& o_value)
{
	Parse(i_element->FirstChildElement("SpriteId"), o_value.spriteId);
	Parse(i_element->FirstChildElement("TimeSpan"), o_value.duration);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace xml