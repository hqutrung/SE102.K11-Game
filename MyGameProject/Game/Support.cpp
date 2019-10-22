#include "Support.h"

RECT Support::BoxColliderToRect(BoxCollider col) {

	RECT r;
	r.top = col.top;
	r.left = col.left;
	r.bottom = col.bottom;
	r.right = col.right;
	
	return r;
}

float Support::Clamp(float x, float a, float b) {
	if (x < a)
		x = a;
	else
		if (x > b)
			x = b;
	return x;
}

float Support::Distance(float x1, float x2) {
	return (x1 > x2) ? x1 - x2 : x2 - x1;
}

float Support::Lerp(float a, float b, float t) {
	Clamp(t, 0, 1);
	return a + (b - a) * t;
}
