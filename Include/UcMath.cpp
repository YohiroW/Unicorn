#include "UcMath.h"
#include <glm/gtx/norm.hpp>

using namespace Unicorn;

const double Math::PRECISION = 0.0000000001;


float Math::getLength2(const Vector3& vec)
{
	return	glm::length2(glm::vec3(vec.x, vec.y, vec.z));
}
