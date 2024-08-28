#pragma once
#include "AEMath.h"

struct Vec3
{
	float x, y, z;

	friend Vec3 operator *(const AEMtx33& mat, const Vec3& vec);
};

AEVec2 operator *(const AEVec2& vec2, const float& a);
AEVec2 operator /(const AEVec2& vec2, const float& a);

AEVec2 operator +(const AEVec2& vecA, const AEVec2& vecB);
AEVec2 operator -(const AEVec2& vecA, const AEVec2& vecB);
AEVec2 HadamardProduct(const AEVec2& vecA, const AEVec2& vecB);