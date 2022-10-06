#pragma once
#include <stdint.h>

namespace core
{

class Duration
{
public:
	Duration(uint64_t i_milisecond);
	static Duration FromMillisecond(uint64_t i_milisecond);
	static Duration FromSecond(float i_milisecond);

	uint64_t ToMilisecond() const;
	float ToSecond() const;

	Duration operator+(const Duration& i_other) const;
	Duration operator-(const Duration& i_other) const;
	Duration operator*(const float i_magnitude) const;
	bool operator>(const Duration& i_other) const;
	bool operator<(const Duration& i_other) const;
	bool operator==(const Duration& i_other) const;
	bool operator>=(const Duration& i_other) const;
	bool operator<=(const Duration& i_other) const;

private:
	uint64_t m_milisecond = 0;
};

} // namespace core