#include "mymatrix.h"
#include "quaternion.h"
#include <iostream>



int main() {
	/*vector3f v1{ 1.f, 2.f, -3.5f };
	vector3f v2{ 2.f, 0.5f, 4.32f };
	vector3f temp = mycross(v1, v2);
	vector3f temp2 = cross(v1, v2);
	std::cout << temp << std::endl;
	std::cout << temp2 << std::endl;*/

	eulerAngle ea(0.2f, 0.4f, 1.0f);
	quaternion q(ea);
	eulerAngle test(q);
	std::cout << test << std::endl;

	/*eulerAngle ea(.0f, 1.57f, .0f);
	quaternion q(ea);
	matrix44 rot = q.toTransform();
	vector3f o1(.0f, 1.0f, .0f);
	vector4f o = homorize<4>(o1, 1.0f);
	vector4f n = rot * o;
	std::cout << n << std::endl;*/
}