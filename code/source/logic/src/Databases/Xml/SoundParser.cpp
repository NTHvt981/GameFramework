#include "SoundParser.h"
#include "AudioSystem/DataTypes/Sound.h"
#include "Databases/Xml/CommonParser.h"
#include "tinyxml2.h"

namespace xml
{

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, core::Sound& o_value);

////////////////////////////////////////////////////////////////////////////////

std::vector<core::Sound> LoadSoundsFile(const char* i_filePath)
{
	std::vector<core::Sound> result;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(i_filePath);
	ParseList<core::Sound>(doc.FirstChildElement("Sounds"), result, "Sound",
		[](tinyxml2::XMLElement* itemElement, core::Sound& o_value)
			{
				Parse(itemElement, o_value);
			}
	);

	return result;
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, core::Sound& o_value)
{
	Parse(i_element->FirstChildElement("Id"), o_value.id);
	Parse(i_element->FirstChildElement("File"), o_value.filePath);
	Parse(i_element->FirstChildElement("Loop"), o_value.loop);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace xml
