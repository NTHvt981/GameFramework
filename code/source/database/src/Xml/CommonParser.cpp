#include "Xml/CommonParser.h"
#include "Core/Identifiers/TextureId.h"

namespace xml
{

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, int64_t& o_value)
{
	o_value = std::atoi(i_element->GetText());
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, uint64_t& o_value)
{
	o_value = std::atoi(i_element->GetText());
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, float& o_value)
{
	o_value = std::atof(i_element->GetText());
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, double& o_value)
{
	o_value = std::atof(i_element->GetText());
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, bool& o_value)
{
	const char* text = i_element->GetText();
	if (strcmp(text, "true") == 0)
	{
		o_value = true;
	}
	else
	{
		o_value = false;
	}
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, core::String& o_value)
{
	o_value = i_element->GetText();
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, core::Vector2F& o_value)
{
	Parse(i_element->FirstChildElement("X"), o_value.x);
	Parse(i_element->FirstChildElement("Y"), o_value.y);
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, core::BoxI64& o_value)
{
	Parse(i_element->FirstChildElement("Bottom"), o_value.bottom);
	Parse(i_element->FirstChildElement("Top"), o_value.top);
	Parse(i_element->FirstChildElement("Right"), o_value.right);
	Parse(i_element->FirstChildElement("Left"), o_value.left);
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, core::SizeI64& o_value)
{
	Parse(i_element->FirstChildElement("Width"), o_value.width);
	Parse(i_element->FirstChildElement("Height"), o_value.height);
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, core::TextureId& o_value)
{
	uint64_t temp;
	Parse(i_element, temp);
	o_value = static_cast<core::TextureId>(temp);
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, core::SpriteId& o_value)
{
	uint64_t temp;
	Parse(i_element, temp);
	o_value = static_cast<core::SpriteId>(temp);
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, core::AnimationId& o_value)
{
	uint64_t temp;
	Parse(i_element, temp);
	o_value = static_cast<core::AnimationId>(temp);
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, core::SoundId& o_value)
{
	uint64_t temp;
	Parse(i_element, temp);
	o_value = static_cast<core::SoundId>(temp);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace xml