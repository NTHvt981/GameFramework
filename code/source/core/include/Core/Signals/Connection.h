#pragma once
#include "Signal.h"
#include "Callback.h"

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

	~Connection()
	{
		Disconnect();
	}

	void Disconnect()
	{
		assert(m_signal != nullptr);
		m_signal->Disconnect(m_function);
		m_function.reset();
	}

private:
	Signal* m_signal;
	std::shared_ptr<Callback> m_function;
};

} // namespace signals

