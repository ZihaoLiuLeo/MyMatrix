
#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include <iostream>
#include "mymatrix.h"

class quaternion;

struct eulerAngle {
	eulerAngle() = default;
	eulerAngle(const float p, const float h, const float r):pitch(p), head(h), roll(r){}
	eulerAngle(const quaternion& q);

	float pitch, head, roll;
};

inline std::ostream& operator<<(std::ostream& os, eulerAngle& ea) {
	os << "[ " << ea.pitch << ", " << ea.head << ", " << ea.roll << " ]." << std::endl;
	return os;
}

class quaternion {
public:
	quaternion() = default;
	quaternion(const vector3f& vv, const float ww) :v(vv), w(ww) {}
	quaternion(const eulerAngle& ea);
	matrix44 toTransform() const;

	quaternion& operator+=(const quaternion& q) {
		v = q.v + v;
		w = q.w + w;
		return *this;
	}

	quaternion& operator-=(const quaternion& q) {
		v = v - q.v; // TODO implement minus
		w = w - q.w;
		return *this;
	}

	quaternion& operator*=(float f) {
		v = v * f;
		w *= f;
		return *this;
	}

	quaternion& operator/=(float f) {
		v = v / f;
		w /= f;
		return *this;
	}

	quaternion& operator*=(const quaternion& q) {
		v = cross(v, q.v) + v * q.w + q.v * q.w;
		w = w * q.w - v * q.v;
		return *this;
	}

	vector3f v;
	float w;
};

quaternion slerp(float t, const quaternion& q1, const quaternion& q2);
quaternion vectorRotation(vector3f start, vector3f dest);

inline quaternion operator+(quaternion q1, const quaternion& q2) {
	return q1 += q2;
}

inline quaternion operator-(quaternion q1, const quaternion& q2) {
	return q1 -= q2;
}

inline quaternion operator*(quaternion q1, const float f) {
	return q1 *= f;
}

inline quaternion operator/(quaternion q1, const float f) {
	return q1 /= f;
}

inline quaternion operator*(quaternion q1, const quaternion& q2) {
	return q1 *= q2;
}


inline std::ostream& operator<<(std::ostream& os, quaternion& q){
	os << "virtual part: " << q.v << std::endl;
	os << "real part: " << q.w << std::endl;
	return os;
}


#endif // !__QUATERNION_H__
