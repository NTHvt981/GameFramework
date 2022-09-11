#include "Core/DataTypes/String.h"

namespace data_types
{

////////////////////////////////////////////////////////////////////////////////

String::String()
{
}

////////////////////////////////////////////////////////////////////////////////

String::String(const char* i_chars)
	: m_innerString(i_chars)
{
}

////////////////////////////////////////////////////////////////////////////////

String::String(const wchar_t* i_chars)
{
	Set(i_chars);
}

////////////////////////////////////////////////////////////////////////////////

String::String(const std::string& i_stdString)
	: m_innerString(i_stdString)
{
}

////////////////////////////////////////////////////////////////////////////////

String::String(const std::wstring& i_stdWString)
{
	Set(i_stdWString);
}

////////////////////////////////////////////////////////////////////////////////

void String::Set(const std::string& i_str)
{
	m_innerString = i_str;
}

////////////////////////////////////////////////////////////////////////////////

void String::Set(const std::wstring& i_wstr)
{
	m_innerString = std::string(i_wstr.begin(), i_wstr.end());
}

////////////////////////////////////////////////////////////////////////////////

const std::string String::ToStdStr() const
{
	return m_innerString;
}

////////////////////////////////////////////////////////////////////////////////

const std::wstring String::ToStdWStr() const
{
	return std::wstring(m_innerString.begin(), m_innerString.end());
}

////////////////////////////////////////////////////////////////////////////////

void String::Set(const char* i_chars)
{
	m_innerString = i_chars;
}

////////////////////////////////////////////////////////////////////////////////

void String::Set(const wchar_t* i_wchars)
{
	Set(std::wstring(i_wchars));
}

////////////////////////////////////////////////////////////////////////////////

const char* String::ToStr() const
{
	return m_innerString.c_str();
}

////////////////////////////////////////////////////////////////////////////////

const wchar_t* String::ToWStr() const
{
	return std::move(ToStdWStr().c_str());
}

////////////////////////////////////////////////////////////////////////////////

bool String::Contain(String i_subStr) const
{
	return m_innerString.find(i_subStr.m_innerString) != -1;
}

////////////////////////////////////////////////////////////////////////////////

void String::Trim()
{
	size_t first = m_innerString.find_first_not_of(' ');
	if (first == std::string::npos)
	{
		first = 0;
	}
	size_t last = m_innerString.find_last_not_of(' ');
	if (last == std::string::npos)
	{
		last = 0;
	}

	m_innerString = m_innerString.substr(first, (last - first + 1));
}

////////////////////////////////////////////////////////////////////////////////

bool String::operator==(const String& i_other) const
{
	return m_innerString == i_other.m_innerString;
}

////////////////////////////////////////////////////////////////////////////////

String String::operator+(const String& i_other) const
{
	return String(m_innerString + i_other.m_innerString);
}

////////////////////////////////////////////////////////////////////////////////

size_t String::Size() const
{
	return m_innerString.size();
}

////////////////////////////////////////////////////////////////////////////////

size_t String::FindFirstNotOf(const String& i_subStr, const size_t i_offSet) const
{
	return m_innerString.find_first_not_of(i_subStr.ToStdStr(), i_offSet);
}

////////////////////////////////////////////////////////////////////////////////

size_t String::FindLastOf(const String& i_subStr) const
{
	return m_innerString.find_last_of(i_subStr.ToStdStr());
}

////////////////////////////////////////////////////////////////////////////////

size_t String::Find(const String& i_subStr, const size_t i_offSet) const
{
	return m_innerString.find(i_subStr.ToStdStr(), i_offSet);
}

////////////////////////////////////////////////////////////////////////////////

String String::SubString(const size_t i_start, const size_t i_end) const
{
	return String(m_innerString.substr(i_start, i_end));
}

////////////////////////////////////////////////////////////////////////////////

} // namespace data_types