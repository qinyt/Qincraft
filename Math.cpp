#include"Math.h"

void math::vec3i_add(GLint* v1, GLint* v2, GLint* res)
{
	res[0] = v1[0] + v2[0];
	res[1] = v1[1] + v2[1];
	res[2] = v1[2] + v2[2];
}

bool math::operator==(const math::VectorXZ& left, const math::VectorXZ& right) noexcept
{
	return (left.x == right.x) && (left.z == right.z);
}