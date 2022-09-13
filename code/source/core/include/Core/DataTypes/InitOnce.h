#pragma once
#include <optional>
#include <assert.h>

namespace data_types
{

template<typename T>
class InitOnce
{
public:
	void Set(const T& i_newValue)
	{
		assert(!m_value.has_value());
		m_value = i_newValue;
	}
	void operator=(const T& i_newValue)
	{
		Set(i_newValue);
	}

	T Get() const
	{
		assert(m_value.has_value());
		return m_value.value();
	}

	bool IsInitialized() const
	{
		return m_value.has_value();
	}

private:
	std::optional<T> m_value;
	T* m_value2;
};

} // namespace data_types