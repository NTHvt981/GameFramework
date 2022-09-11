#pragma once

namespace data_types
{

class Flag
{
public:
	void Set()
	{
		if (m_flag)
		{
			throw("Flag logic violation, value can only be set once!");
		}
		m_flag = true;
	}

	bool IsSet() const
	{
		return m_flag;
	}

private:
	bool m_flag = false;
};

} // namespace data_types
