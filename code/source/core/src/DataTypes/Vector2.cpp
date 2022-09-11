#include "Core/DataTypes/Vector2.h"
#include <math.h>

namespace data_types
{

float GetLength(const Vector2F& i_vector)
{
	return sqrtf(powf(i_vector.x, 2) + powf(i_vector.y, 2));
}

} // namespace data_types