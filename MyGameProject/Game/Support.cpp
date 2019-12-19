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

bool Support::IsContainedIn(float x, float a, float b)
{
	return (x <= b && x >= a);
}
void Support::DrawRect(D3DXVECTOR3 pos, BoxCollider box)
{
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->GetTexture(2911);
	Sprites* sprite = new Sprites(texture, box);
	sprite->Draw(pos, box, D3DCOLOR_ARGB(130, 255, 255, 255));
	delete sprite;
	sprite = NULL;
}

float Support::LengthOfVector(D3DXVECTOR2 vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

BoxCollider Support::TextToRect(char text, int font)
{
	D3DSURFACE_DESC desc;
	Textures::GetInstance()->GetTexture(font)->GetLevelDesc(0, &desc);
	int width = desc.Width / 10;
	int height = desc.Height;

	int a = (int)text - 48;
	BoxCollider box;
	box.top = height;
	box.bottom = 0;
	box.left = a * width;
	box.right = (a + 1) * width;
	return box;
}


