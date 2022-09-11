#pragma once
#include <optional>

namespace data_types
{

template<typename T>
class InitOnce
{
public:
	void Set(const T& i_newValue)
	{
		if (m_value.has_value())
		{
			throw("InitOnce logic violation, value can only be initialized once!");
		}
		m_value = i_newValue;
	}

	T Get() const
	{
		if (!m_value.has_value())
		{
			throw("InitOnce logic violation, value must be initialized!");
		}
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