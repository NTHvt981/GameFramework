#pragma once
#include "Core/DataTypes/String.h"
#include <stdint.h>

namespace tinyxml2
{
class XMLElement;
} // namespace tinyxml2

namespace data_types
{
struct BoxI64;
} // namespace data_types

namespace ids
{
enum class TextureId : uint64_t;
} // namespace data_types

namespace xml
{

void Parse(const tinyxml2::XMLElement* i_element, int64_t& o_value);
void Parse(const tinyxml2::XMLElement* i_element, uint64_t& o_value);
void Parse(const tinyxml2::XMLElement* i_element, float& o_value);
void Parse(const tinyxml2::XMLElement* i_element, double& o_value);

void Parse(const tinyxml2::XMLElement* i_element, data_types::String& o_value);
void Parse(const tinyxml2::XMLElement* i_element, data_types::BoxI64& o_value);

void Parse(const tinyxml2::XMLElement* i_element, ids::TextureId& o_value);

} // namespace xml