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
};

} // namespace data_types