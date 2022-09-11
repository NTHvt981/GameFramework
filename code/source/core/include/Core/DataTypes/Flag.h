#pragma once
#include <assert.h>

namespace data_types
{

class Flag
{
public:
	void Set()
	{
		assert(!m_flag);
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
