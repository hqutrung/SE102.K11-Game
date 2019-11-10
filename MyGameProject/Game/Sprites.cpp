#include "Sprites.h"

Sprites::Sprites(LPDIRECT3DTEXTURE9 texture, BoxCollider box)
{
	this->texture = texture;
	if (IsRect(box))
	{
		width = box.right - box.left;
		height = box.bottom - box.top;
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

	position = D3DXVECTOR3(box.left ,box.top, 0);
	translation = D3DXVECTOR2(0, 0);

	spriteHandler = Graphic::GetInstance()->GetCurrentSpriteHandler();

	

}

Sprites::Sprites(const char* filePath, BoxCollider box, int width, int height, D3DCOLOR colorKey)
{
	this->InitWithSprite(filePath, box, width, height, colorKey);
}

void Sprites::InitWithSprite(const char* filePath, BoxCollider box, int width, int height, D3DCOLOR colorKey)
{
	HRESULT result;
	spriteHandler = Graphic::GetInstance()->GetCurrentSpriteHandler();
	position = D3DXVECTOR3(0, 0, 0);
	mRotation = 0;
	mRotationCenter = D3DXVECTOR2(position.x, position.y);
	translation = D3DXVECTOR2(0, 0);
	mScale = D3DXVECTOR2(0, 1);
	this->box = box;
	mScale.x = mScale.y = 1;

	D3DXGetImageInfoFromFileA(filePath, &mImageInfo);

	if (width == NULL)
	{
		if (!IsRect(box))
			width = mImageInfo.Width;
		else
			width = box.right - box.left;
	}
	else
		width = width;

	if (height == NULL)
	{
		if (!IsRect(box))
			height = mImageInfo.Height;
		else
			height = box.bottom - box.top;
	}
	else
		height = height;

	if (!IsRect(box))
	{
		this->box.left = 0;
		this->box.right = width;
		this->box.top = 0;
		this->box.bottom = height;
	}

	LPDIRECT3DDEVICE9 device;
	spriteHandler->GetDevice(&device);

	D3DXCreateTextureFromFileExA(
		device,
		filePath,
		mImageInfo.Width,
		mImageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorKey,
		&mImageInfo,
		NULL,
		&texture);
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

void Sprites::Draw(D3DXVECTOR3 position, BoxCollider box, D3DXCOLOR colorKey, bool reverse) 
{
	auto cam = Camera::GetInstance()->GetRect();
	if (!IsRect(cam))
		return;

	D3DXVECTOR3 inPosition = this->position;
	BoxCollider inSourceRect = this->box;

	if (position != D3DXVECTOR3())
		inPosition = position;

	if (IsRect(box))
		inSourceRect = box;

	D3DXMATRIX m_Maxtrix;
	D3DXMatrixIdentity(&m_Maxtrix);
	m_Maxtrix._22 = -1;
	m_Maxtrix._41 = -cam.left;
	m_Maxtrix._42 = cam.top;


	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &inPosition, &m_Maxtrix);
	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	p.x = (int)p.x;
	p.y = (int)p.y;

	D3DXMATRIX oldMatrix;
	spriteHandler->GetTransform(&oldMatrix);

	if (reverse) {
		D3DXMatrixIdentity(&m_Maxtrix);
		auto scalingScenter = D3DXVECTOR2(p.x, p.y);
		auto inScale = D3DXVECTOR2(-1, 1);
		auto inRotationCenter = D3DXVECTOR2(0, 0);
		auto inRotation = 0;
		auto inTranslation = D3DXVECTOR2(0, 0);
		D3DXMatrixTransformation2D(&m_Maxtrix, &scalingScenter, 0, &inScale, &inRotationCenter,
			inRotation, &inTranslation);
		spriteHandler->SetTransform(&m_Maxtrix);
	}

	RECT r = Support::BoxColliderToRect(inSourceRect);

	D3DXVECTOR3 center = D3DXVECTOR3(width / 2.0f, height / 2.0f, 0);
	
	spriteHandler->Draw(
		texture,			// Texture luu sprite
		&r,					// dien tich can the hien
		&center,			// tam dung de ve, xoay
		&p,					// vi tri sprite
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
