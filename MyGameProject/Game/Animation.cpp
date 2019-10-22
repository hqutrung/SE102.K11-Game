#include "Animation.h"

Animation::Animation(float defaultTime)
{
	totalFrame = 0;
	currentFrame = 0;
	this->defaultTime = defaultTime;
}

Animation::~Animation()
{
}

void Animation::AddFrame(LPANIMATION_FRAME frame)
{
	frames.push_back(frame);
}

void Animation::AddFrames(LPDIRECT3DTEXTURE9 texture, int rows, int columns, float timePerFrame, D3DCOLOR colorKey)
{
	defaultTime = timePerFrame == 0 ? defaultTime : timePerFrame;
	totalFrame = rows * columns;
	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);
	float frameWidth = (float)desc.Width;
	float frameHeight = (float)desc.Height;
	BoxCollider box = BoxCollider(0, 0, frameWidth, frameHeight);
	//for (int i = 1; i < rows; i++)
		//for(int j=1;j<columns;j++)

}
