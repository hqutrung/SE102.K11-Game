#include "Graphic.h"
#include "Textures.h"
#include "Sprites.h"
#include "BoxCollider.h"

Graphic* Graphic::instance = NULL;


Graphic* Graphic::GetInstance()
{
	if (instance == NULL)
		instance = new Graphic();
	return instance;
}

void Graphic::Init(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;
	
	D3DPRESENT_PARAMETERS d3dpp;
	
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv
	);
	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] Create Device failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
	
	D3DXCreateSprite(d3ddv, &spriteHandler);

	OutputDebugString(L"Init Device Successful;\n");

	InitFont();
}

void Graphic::InitFont()
{
	auto tex = Textures::GetInstance();
	tex->Add(TEX_FONT1, "Resources/Font/font1.png", D3DCOLOR_XRGB(255, 0, 255));
	tex->Add(TEX_FONT2, "Resources/Font/font2.png", D3DCOLOR_XRGB(255, 0, 255));
}

Graphic::~Graphic()
{
	if (backBuffer != NULL) {
		backBuffer->Release();
	}
	if (d3ddv != NULL) {
		d3ddv->Release();
	}
	if (d3d != NULL) {
		d3d->Release();
	}

	if (spriteHandler != NULL) {
		spriteHandler->Release();
	}
}

void Graphic::DrawString(const std::string& text, D3DXVECTOR3 pos, int font)
{
	BoxCollider box;
	auto textures = Textures::GetInstance();
	D3DSURFACE_DESC desc;
	Textures::GetInstance()->GetTexture(font)->GetLevelDesc(0, &desc);
	int width = desc.Width / 10;
	
	int i = 0;
	for (auto c:text) {
		box = Support::TextToRect(c, font);
		auto position = pos;
		position.x += i++ * width;
		auto sprite = new Sprites(textures->GetTexture(font), box);
		//sprite->Draw(position, box, D3DCOLOR_XRGB(255, 255, 255));
		sprite->NormalDraw(position);
	}
}

HWND Graphic::GetCurrentHWND()
{
	return hWnd;
}

void Graphic::SetCurrentHWND(HWND hWnd)
{
	this->hWnd = hWnd;
}

LPDIRECT3DDEVICE9 Graphic::GetCurrentDirect3DDevice()
{
	return d3ddv;
}

void Graphic::SetCurrentDirect3DDevice(LPDIRECT3DDEVICE9 d3dvv)
{
	this->d3ddv = d3ddv;
}

LPD3DXSPRITE Graphic::GetCurrentSpriteHandler()
{
	return spriteHandler;
}

void Graphic::SetCurrentSpriteHandler(LPD3DXSPRITE spriteHandler)
{
	this->spriteHandler = spriteHandler;
}

LPDIRECT3DSURFACE9 Graphic::GetBackBuffer()
{
	return backBuffer;
}

void Graphic::SetBackBuffer(LPDIRECT3DSURFACE9 backBuffer)
{
	this->backBuffer = backBuffer;
}


