#pragma once

#include"glad\glad.h"
#include<unordered_map>

namespace math 
{
	void vec3i_add(GLint* v1, GLint* v2, GLint* res);

	typedef struct VectorXZ 
	{
		int x, z;
	}VectorXZ_t;
    bool operator==(const VectorXZ& left, const VectorXZ& right) noexcept;
}

namespace std {
    template <> struct hash<math::VectorXZ> {
        size_t operator()(const math:: VectorXZ& vect) const noexcept
        {
            std::hash<decltype(vect.x)> hasher;

            auto hash1 = hasher(vect.x);
            auto hash2 = hasher(vect.z);

            return std::hash<decltype(vect.x)>{}((hash1 ^ hash2) >> 2);
        }
    };
}