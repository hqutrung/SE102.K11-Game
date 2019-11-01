#include "Sprites.h"

Sprites::Sprites(LPDIRECT3DTEXTURE9 texture, BoxCollider box)
{
	this->texture = texture;
	if (IsRect(box))
	{
		width = box.GetWidth();
		height = box.GetHeight();
		this->mbox = box;
	}
	else
	{
		D3DSURFACE_DESC desc;
		texture->GetLevelDesc(0, &desc);
		height = desc.Height;
		width = desc.Width;
		this->mbox = BoxCollider(0, 0, width, height);
	}

	m_Position = D3DXVECTOR3(box.left ,box.top, 0);
	m_Translation = D3DXVECTOR2(0, 0);

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
	m_Position = D3DXVECTOR3(0, 0, 0);
	mRotation = 0;
	mRotationCenter = D3DXVECTOR2(m_Position.x, m_Position.y);
	m_Translation = D3DXVECTOR2(0, 0);
	mScale = D3DXVECTOR2(0, 1);
	mbox = box;
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
		mbox.left = 0;
		mbox.right = width;
		mbox.top = 0;
		mbox.bottom = height;
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

void Sprites::Draw(D3DXVECTOR3 position, BoxCollider r, D3DXCOLOR colorKey, bool reverse) 
{
	auto cam = Camera::GetInstance()->GetRect();

	//phng: Doc them cai slide thay Kha de hieu ro hon ve matrix nay nghe
	if (!IsRect(cam))
		return;

	D3DXVECTOR3 inPosition = m_Position;
	BoxCollider inSourceRect = mbox;

	if (position != D3DXVECTOR3())
		inPosition = position;

	if (IsRect(r))
		inSourceRect = r;

	D3DXMATRIX m_Maxtrix;
	D3DXMatrixIdentity(&m_Maxtrix);
	m_Maxtrix._22 = -1;
	m_Maxtrix._41 = -cam.left;
	m_Maxtrix._42 = cam.top;

	D3DXVECTOR3 center = D3DXVECTOR3(width / 2, height / 2, 0);

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
	else
	{
		D3DXMatrixIdentity(&m_Maxtrix);
		auto scalingScenter = D3DXVECTOR2(p.x, p.y);
		auto inScale = D3DXVECTOR2(1, 1);
		auto inRotationCenter = D3DXVECTOR2(0, 0);
		auto inRotation = 0;
		auto inTranslation = D3DXVECTOR2(0, 0);
		D3DXMatrixTransformation2D(&m_Maxtrix, &scalingScenter, 0, &inScale, &inRotationCenter,
			inRotation, &inTranslation);
		spriteHandler->SetTransform(&m_Maxtrix);
	}

	RECT rr = Support::BoxColliderToRect(inSourceRect);


	spriteHandler->Draw(
		texture,
		&rr,
		&center,
		&p,
		colorKey
	);
	spriteHandler->SetTransform(&oldMatrix);
}


void Sprites::NormalDraw(D3DXVECTOR3 position)
{
	RECT r = Support::BoxColliderToRect(mbox);
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
