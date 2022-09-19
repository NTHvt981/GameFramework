#pragma once
#include <memory>
#include <assert.h>
#include "Callback.h"
#include "Connection.h"

namespace signals
{

template<class ...Args>
class Connection;

template<class ...Args>
class Signal
{
	typedef Callback<Args...> Callback;
	typedef Connection<Args...> Connection;
public:
	Signal()
	{

	}

#pragma warning(error:4834)
	[[nodiscard]]
	Connection Connect(Callback i_function)
	{
		auto func = std::make_shared<Callback>(i_function);

		m_functions.push_back(func);

		return Connection(*this, func);
	}

	void Disconnect(std::shared_ptr<Callback> i_function)
	{
		m_functions.remove(i_function);
	}

	void Clear()
	{
		m_functions.clear();
	}

	void Emit(Args... args) const
	{
		for (std::shared_ptr<Callback> function : m_functions)
		{
			(*function)(args...);
		}
	}

	void EmitReverseOrder(Args... args) const
	{
		for (auto function = m_functions.rbegin(); function != m_functions.rend(); ++function)
		{
			(*function)(args...);
		}
	}

private:
	std::list<std::shared_ptr<Callback>> m_functions;
};

} // namespace signals
