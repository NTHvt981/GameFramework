#include "Xml/CommonParser.h"
#include "Core/Identifiers/TextureId.h"
#include "tinyxml2.h"

namespace xml
{

void Parse(const tinyxml2::XMLElement* i_element, int64_t& o_value)
{
	o_value = std::atoi(i_element->GetText());
}

void Parse(const tinyxml2::XMLElement* i_element, uint64_t& o_value)
{
	o_value = std::atoi(i_element->GetText());
}

void Parse(const tinyxml2::XMLElement* i_element, float& o_value)
{
	o_value = std::atof(i_element->GetText());
}

void Parse(const tinyxml2::XMLElement* i_element, double& o_value)
{
	o_value = std::atof(i_element->GetText());
}

void Parse(const tinyxml2::XMLElement* i_element, core::String& o_value)
{
	o_value = i_element->GetText();
}

void Parse(const tinyxml2::XMLElement* i_element, core::BoxI64& o_value)
{
	Parse(i_element->FirstChildElement("bottom"), o_value.bottom);
	Parse(i_element->FirstChildElement("top"), o_value.top);
	Parse(i_element->FirstChildElement("right"), o_value.right);
	Parse(i_element->FirstChildElement("left"), o_value.left);
}

void Parse(const tinyxml2::XMLElement* i_element, ids::TextureId& o_value)
{
	uint64_t temp;
	Parse(i_element, temp);
	o_value = static_cast<ids::TextureId>(temp);
}

} // namespace xml