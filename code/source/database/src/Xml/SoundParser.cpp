#include "SoundParser.h"
#include "AudioSystem/DataTypes/Sound.h"
#include "Xml/CommonParser.h"
#include "tinyxml2.h"

namespace xml
{

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, audios::Sound& o_value);

////////////////////////////////////////////////////////////////////////////////

std::vector<audios::Sound> LoadSoundsFile(const char* i_filePath)
{
	std::vector<audios::Sound> result;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(i_filePath);
	ParseList<audios::Sound>(doc.FirstChildElement("Sounds"), result, "Sound", 
		[](tinyxml2::XMLElement* itemElement, audios::Sound& o_value)
			{
				Parse(itemElement, o_value);
			}
	);

	return result;
}

////////////////////////////////////////////////////////////////////////////////

void Parse(const tinyxml2::XMLElement* i_element, audios::Sound& o_value)
{
	Parse(i_element->FirstChildElement("Id"), o_value.id);
	Parse(i_element->FirstChildElement("File"), o_value.filePath);
	Parse(i_element->FirstChildElement("Loop"), o_value.loop);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace xml
