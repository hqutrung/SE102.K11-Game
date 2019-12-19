#include "Animation.h"

Animation::Animation(float defaultTime)
{
	totalFrame = 0;
	currentFrame = 0;
	this->defaultTime = defaultTime;
}

Animation::~Animation()
{
	for (size_t i = 0; i < frames.size(); i++) {
		delete frames[i];
		frames[i] = NULL;
	}
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
	float frameWidth = (float)desc.Width / columns;
	float frameHeight = (float)desc.Height / rows;
	BoxCollider box = BoxCollider(0, 0, frameWidth, frameHeight);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			box.left = j * frameWidth;
			box.top = i * frameHeight;
			box.right = box.left + frameWidth;
			box.bottom = box.top + frameHeight;
			AddFrame(new AnimationFrame(texture, box, defaultTime));
		}
}

void Animation::AddFramesA(LPDIRECT3DTEXTURE9 texture, int firstRow, int firstColumn, int finalRow, int finalColumn, int columns, int rowNumber, int columnNumber, float timePerFrame, D3DCOLOR colorKey)
{
	defaultTime = (timePerFrame == 0) ? defaultTime : timePerFrame;
	totalFrame = (finalRow - firstRow) * columnNumber + (finalColumn - firstColumn + 1);
	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);
	float frameWidth = (float)desc.Width / columnNumber;
	float frameHeight = (float)desc.Height / rowNumber;
	BoxCollider r = BoxCollider(0, 0, frameHeight, frameWidth);
	for (int i = firstRow - 1; i < finalRow; i++)
		for (int j = 0; j < columns; j++) 
		{
			if ((i == firstRow - 1 && j < firstColumn - 1) || (i == finalRow - 1 && j > finalColumn - 1))
				continue;
			r.left = j * frameWidth;
			r.top = i * frameHeight;
			r.bottom = r.top + frameHeight;
			r.right = r.left + frameWidth;
			AddFrame(new AnimationFrame(texture, r, defaultTime));
		}
}

float Animation::GetCurrentTotalTime()
{
	return currentTotalTime;
}

float Animation::GetDefaultTime()
{
	return defaultTime;
}

int Animation::GetWidthCurrentFrame()
{
	return frames[currentFrame]->GetWidth();
}

int Animation::GetHeightCurrentFrame()
{
	return frames[currentFrame]->GetHeight();
}

void Animation::SetCurrentFrame(int frame)
{
	currentFrame = frame;
}

void Animation::Render(D3DXVECTOR3 position, BoxCollider sourceRect, D3DXCOLOR colorKey, bool isReverse)
{
	frames[currentFrame]->Draw(position, sourceRect, colorKey, isReverse);
}

void Animation::NormalRender(D3DXVECTOR3 position)
{
	frames[currentFrame]->NormalDraw(position);
}

void Animation::Update(float dt)
{
	//delay 1 frame
	if (!startUpdate) {
		startUpdate = true;
		return;
	}
	currentTotalTime += dt;
	int nextFrame = currentFrame + 1;
	if (nextFrame >= totalFrame)
		nextFrame = 0;

	if (currentTotalTime >= defaultTime) {
		currentTotalTime = 0;
		currentFrame = nextFrame;
	}

	time += dt;
}

void Animation::Update1(float dt)
{
	//delay 1 frame
	if (!startUpdate) {
		startUpdate = true;
		return;
	}
	currentTotalTime += dt;
	int nextFrame = currentFrame - 1;
	if (nextFrame <= -1)
		nextFrame = totalFrame-1;

	if (currentTotalTime >= defaultTime) {
		currentTotalTime = 0;
		currentFrame = nextFrame;
	}

	time += dt;
}

void Animation::ResetAnimation()
{
	currentFrame = 0;
	currentTotalTime = 0;
	time = 0;
	startUpdate = false;
}

int Animation::GetCurrentFrameID()
{
	return currentFrame;
}

bool Animation::IsLastFrame(float dt)
{
	return (currentFrame == totalFrame - 1 && currentTotalTime + dt >= defaultTime);
}
bool Animation::IsEndFrame(int frame,float dt)
{
	return (currentFrame == frame  && currentTotalTime + dt >= defaultTime);
}

double Animation::GetPercentTime()
{
	return time / (defaultTime * totalFrame);
}
