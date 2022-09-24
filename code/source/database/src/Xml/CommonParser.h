#pragma once
#include "Core/DataTypes/String.h"
#include "Core/DataTypes/Vector2.h"
#include "Core/DataTypes/Box.h"
#include "Core/DataTypes/Size.h"
#include "Core/Identifiers/TextureId.h"
#include "Core/Identifiers/SpriteId.h"
#include <stdint.h>
#include <vector>
#include <functional>
#include "tinyxml2.h"

namespace xml
{

void Parse(const tinyxml2::XMLElement* i_element, int64_t& o_value);
void Parse(const tinyxml2::XMLElement* i_element, uint64_t& o_value);
void Parse(const tinyxml2::XMLElement* i_element, float& o_value);
void Parse(const tinyxml2::XMLElement* i_element, double& o_value);

void Parse(const tinyxml2::XMLElement* i_element, core::String& o_value);
void Parse(const tinyxml2::XMLElement* i_element, core::Vector2F& o_value);
void Parse(const tinyxml2::XMLElement* i_element, core::BoxI64& o_value);
void Parse(const tinyxml2::XMLElement* i_element, core::SizeI64& o_value);

void Parse(const tinyxml2::XMLElement* i_element, ids::TextureId& o_value);
void Parse(const tinyxml2::XMLElement* i_element, ids::SpriteId& o_value);

template<typename T>
void ParseList(
	tinyxml2::XMLElement* i_element, 
	std::vector<T>& o_listItem, 
	const char* i_listItemName, 
	std::function<void(tinyxml2::XMLElement*, T&)> i_callback)
{
	tinyxml2::XMLElement* element = i_element->FirstChildElement(i_listItemName);
	while (element != nullptr)
	{
		T item;
		i_callback(element, item);
		o_listItem.push_back(item);

		i_element->DeleteChild(element);
		element = i_element->FirstChildElement(i_listItemName);
	}
}

} // namespace xml