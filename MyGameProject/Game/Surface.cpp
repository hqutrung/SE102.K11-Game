#include "Surface.h"

Surface::Surface()
{
	SetType(Layer::Surface);
	SetStatic(true);
}

Surface::~Surface()
{
}

void Surface::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}

void Surface::SetSpawnBox(BoxCollider box)
{
	position = D3DXVECTOR3(box.getCenter());
	SetWidth(box.right - box.left);
	SetHeight(box.top - box.bottom);
}
