#include "quaternion.h"
#include <cmath>

eulerAngle::eulerAngle(const quaternion& q) {
	float x = q.v.x, y = q.v.y, z = q.v.z, w = q.w;
	float e20 = 2.0f * (x * z - w * y);
	float e22 = 1.0f - 2.0f * (x * x + y * y);
	head = std::atan2(-e20, e22);
	float e21 = 2 * (y * z + w * x);
	e21 = e21 > 1.0f ? 1.0f : e21;
	e21 = e21 < -1.0f ? -1.0f : e21;
	pitch = std::asin(e21);
	float e01 = 2.0f * (x * y - w * z);
	float e11 = 1.0f - 2.0f * (x * x + z * z);
	roll = std::atan2(-e01, e11);
}

// orthogonal matrix
matrix44 quaternion::toTransform() const {
	float xx = v.x * v.x, yy = v.y * v.y, zz = v.z * v.z;
	float xy = v.x * v.y, yz = v.y * v.z, xz = v.x * v.z;
	float wx = w * v.x, wy = w * v.y, wz = w * v.z;
	matrix44 ret;
	InitMat(matrix44, ret, 4, float, 1);
	ret[0][0] = 1 - 2 * (yy + zz);
	ret[0][1] = 2 * (xy - wz);
	ret[0][2] = 2 * (xy + wy);
	ret[1][0] = 2 * (xy + wz);
	ret[1][1] = 1 - 2 * (xx + zz);
	ret[1][2] = 2 * (yz - wx);
	ret[2][0] = 2 * (xz - wy);
	ret[2][1] = 2 * (yz + wx);
	ret[2][2] = 1 - 2 * (xx + yy);
	return ret;
}

// z * x * y - head, pitch, roll order(multiply reverse)
quaternion::quaternion(const eulerAngle& ea) {
	float cosa, sina, cosb, sinb, cosg, sing;
	cosa = std::cos(ea.pitch / 2.f);
	sina = std::sin(ea.pitch / 2.f);
	cosb = std::cos(ea.head / 2.f);
	sinb = std::sin(ea.head / 2.f);
	cosg = std::cos(ea.roll / 2.f);
	sing = std::sin(ea.roll / 2.f);
	w = cosg * cosa * cosb + sing * sina * sinb;
	v.x = cosg * sina * cosb - sing * cosa * sinb;
	v.y = cosg * cosa * sinb + sing * sina * cosb;
	v.z = cosg * sina * sinb + sing * cosa * cosb;
}

