#include "Sprites.h"

Sprites::Sprites(LPDIRECT3DTEXTURE9 texture, BoxCollider box)
{
	this->texture = texture;
	if (IsRect(box))
	{
		width = box.GetWidth();
		height = box.GetHeight();
		this->box = box;
	}
	else
	{
		D3DSURFACE_DESC desc;
		texture->GetLevelDesc(0, &desc);
		height = desc.Height;
		width = desc.Width;
		this->box = BoxCollider(0, 0, width, height);
	}

	position = D3DXVECTOR3(0 ,0, 0);
	translation = D3DXVECTOR2(0, 0);

	spriteHandler = Graphic::GetInstance()->GetCurrentSpriteHandler();

}

Sprites::~Sprites()
{
}

int Sprites::GetWidth()
{
	return width;
}

void Sprites::SetWidth(int width)
{
	this->width = width;
}

int Sprites::GetHeight()
{
	return height;
}

void Sprites::SetHeight(int height)
{
	this->height = height;
}

LPDIRECT3DTEXTURE9 Sprites::GetTexture()
{
	return texture;
}

bool Sprites::IsRect(BoxCollider r)
{
	if (r.top == r.bottom)
		return false;
	if (r.left == r.right)
		return false;
	return true;
}

void Sprites::Draw(D3DXVECTOR3 position, BoxCollider box, D3DCOLOR colorKey, bool reverse)
{
	D3DXVECTOR3 inPosition = this->position;
	BoxCollider inSourceRect = this->box;

	if (position != D3DXVECTOR3())
		inPosition = position;

	if (IsRect(box))
		inSourceRect = box;

	D3DXVECTOR3 center = D3DXVECTOR3(width / 2.0f, height / 2.0f, 0);

	D3DXMATRIX m_Maxtrix;

	D3DXMATRIX oldMatrix;

	spriteHandler->GetTransform(&oldMatrix);

	if (reverse)
	{
		D3DXMatrixIdentity(&m_Maxtrix);

		//auto scalingScenter = D3DXVECTOR2(p.x, p.y);
		auto scalingScenter = D3DXVECTOR2(inPosition.x + width / 2.0f, inPosition.y);
		auto inScale = D3DXVECTOR2(-1.0f, 1.0f);
		auto inRotationCenter = D3DXVECTOR2(0, 0);
		auto inRotation = 0;
		auto inTranslation = D3DXVECTOR2(0, 0);

		D3DXMatrixTransformation2D(&m_Maxtrix, &scalingScenter, 0, &inScale, &inRotationCenter, inRotation, &inTranslation);

		spriteHandler->SetTransform(&m_Maxtrix);
	}

	RECT r = Support::BoxColliderToRect(inSourceRect);
	spriteHandler->Draw(
		texture,			// Texture luu sprite
		&r,					// dien tich can the hien
		&center,			// tam dung de ve, xoay
		&inPosition,		// vi tri sprite
		colorKey			// mau thay the
	);
	spriteHandler->SetTransform(&oldMatrix);
}

void Sprites::NormalDraw(D3DXVECTOR3 position)
{
	RECT r = Support::BoxColliderToRect(box);
	spriteHandler->Draw(
		texture,
		&r,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}
//
//void ListSprites::Add(int id, BoxCollider rect, LPDIRECT3DTEXTURE9 tex)
//{
//	LPSPRITE s = new Sprites(id, rect, tex);
//	lSprites[id] = s;
//}
//
//LPSPRITE ListSprites::Get(int id)
//{
//	return lSprites[id];
//}
//
//ListSprites* ListSprites::GetInstance()
//{
//
//	if (instance == NULL) instance = new ListSprites();
//	return instance;
//}
