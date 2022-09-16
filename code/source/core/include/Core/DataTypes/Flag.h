#pragma once
#include <assert.h>

namespace core
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

} // namespace core
