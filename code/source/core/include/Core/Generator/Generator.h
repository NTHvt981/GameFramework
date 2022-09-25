#pragma once

namespace core
{

template<typename T>
class Generator
{
public:
	virtual T Generate() = 0;
};


} // namespace core