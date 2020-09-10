#pragma once
#include<glm/glm.hpp>

inline void print_vec3(glm::vec3& vec, const char* title = "")
{
	printf(title);
	printf("x:%f, y:%f, z:%f\n", vec.x, vec.y, vec.z);
}

inline void print_mat(glm::mat4& mat)
{
	printf("0:%f, 1:%f, 2:%f, 3:%f\n0:%f, 1:%f, 2:%f, 3:%f\n0:%f, 1:%f, 2:%f, 3:%f\n0:%f, 1:%f, 2:%f, 3:%f\n",
		mat[0][0], mat[0][1], mat[0][2], mat[0][3],
		mat[1][0], mat[1][1], mat[1][2], mat[1][3],
		mat[2][0], mat[2][1], mat[2][2], mat[2][3],
		mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
	printf("-----------\n\n");
}
