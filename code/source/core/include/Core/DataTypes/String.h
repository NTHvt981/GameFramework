#pragma once
#include <string>

namespace core
{
class String
{
public:
	String();
	String(const char* i_chars);
	String(const wchar_t* i_chars);
	String(const std::string& i_stdString);
	String(const std::wstring& i_stdWString);

	void Set(const std::string& i_str);
	void Set(const std::wstring& i_wstr);
	const std::string ToStdStr() const;
	const std::wstring ToStdWStr() const;

	void Set(const char* i_chars);
	void Set(const wchar_t* i_wchars);
	const char* ToStr() const;
	const wchar_t* ToWStr() const;

	bool Contain(String i_subStr) const;
	void Trim();

	bool operator==(const String& i_other) const;
	bool operator<(const String& i_other) const;
	String operator+(const String& i_other) const;

	size_t Size() const;
	size_t FindFirstNotOf(const String& i_subStr, const size_t i_offSet) const;
	size_t FindLastOf(const String& i_subStr) const;
	size_t Find(const String& i_subStr, const size_t i_offSet) const;
	String SubString(const size_t i_start, const size_t i_end) const;
private:
#ifdef UNICODE
	std::wstring m_innerString;
#else
	std::string m_innerString;
#endif
};

} // namespace core