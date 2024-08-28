#include "MathUtils.h"

#include <cmath>

Vec3 operator*(const AEMtx33& mat, const Vec3& vec)
{
	Vec3 ret;
	ret.x = mat.m[0][0] * vec.x + mat.m[0][1] * vec.y + mat.m[0][2] * vec.z;
	ret.y = mat.m[1][0] * vec.x + mat.m[1][1] * vec.y + mat.m[1][2] * vec.z;
	ret.z = mat.m[2][0] * vec.x + mat.m[2][1] * vec.y + mat.m[2][2] * vec.z;
	return ret;
}

AEVec2 operator*(const AEVec2& vec2, const float& a)
{
	AEVec2 ret = vec2;
	ret.x *= a;
	ret.y *= a;
	return ret;
}

AEVec2 operator/(const AEVec2& vec2, const float& a)
{
	return operator*(vec2, 1.f / a);
}

AEVec2 operator+(const AEVec2& vecA, const AEVec2& vecB)
{
	return AEVec2{ vecA.x + vecB.x, vecA.y + vecB.y };
}

AEVec2 operator-(const AEVec2& vecA, const AEVec2& vecB)
{
	return AEVec2{ vecA.x - vecB.x, vecA.y - vecB.y };
}

AEVec2 HadamardProduct(const AEVec2& vecA, const AEVec2& vecB)
{
	return AEVec2{ vecA.x * vecB.x, vecA.y * vecB.y };
}
