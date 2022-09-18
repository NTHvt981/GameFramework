#pragma once
#include "Signal.h"
#include "Callback.h"
#include <assert.h>

namespace signals
{

template<class ...Args>
class Signal;

template<class ...Args>
class Connection
{
public:
	typedef Signal<Args...> Signal;
	typedef Callback<Args...> Callback;
public:
	Connection(Signal& i_signal,
		std::shared_ptr<Callback>& i_function)
		: m_signal(&i_signal)
		, m_function(i_function)
	{

	}
	Connection()
	{

	}

	void operator=(const Connection& i_other)
	{
		this->m_signal = i_other.m_signal;
		this->m_function = i_other.m_function;
	}

	~Connection()
	{
		Disconnect();
	}

	void Disconnect()
	{
		if (m_signal != nullptr)
		{
			if (m_function.use_count() == 2)
			{
				m_signal->Disconnect(m_function);
			}
			m_function.reset();

			m_signal = nullptr;
		}
	}

private:
	Signal* m_signal = nullptr;
	std::shared_ptr<Callback> m_function;
};

} // namespace signals