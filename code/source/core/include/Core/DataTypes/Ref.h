#pragma once
#include <memory>

namespace core
{

template<typename T>
class Ref
{
public:
	Ref(const std::shared_ptr<T> i_sharedPtr)
		: m_innerRef(std::ref<T>(*i_sharedPtr.get()))
	{

	}

	Ref(T* i_sharedRawPtr)
		: m_innerRef(std::ref<T>(*i_sharedRawPtr))
	{
	}

	constexpr T& Get() const noexcept
	{
		return m_innerRef.get();
	}

	constexpr T* operator->() const noexcept
	{
		return &m_innerRef.get();
	}

private:
	std::reference_wrapper<T> m_innerRef;
};

} // namespace core