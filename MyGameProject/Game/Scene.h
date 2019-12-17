#ifndef __SCENE__
#define __SCENE__
#include <d3dx9.h>
#include <d3d9.h>
#include "GameMap.h"
#include "Sound.h"

class Scene
{
protected:
	D3DCOLOR backColor;
	float gameTime;
	bool isEndScene = false;
	bool isTransition = false;
public:
	Scene();
	virtual ~Scene();
	virtual void ProcessInput();
	virtual void Update(float dt) = 0;
	virtual void LoadContent() = 0;
	virtual void Render() = 0;
	virtual int GetSceneID() = 0;

	bool IsEndScene() { return isEndScene; }
	bool IsTransition() { return isTransition; }
	void SetIsTransition(bool x) { isTransition = x; }

	D3DCOLOR GetBackcolor();
	void SetBackColor(D3DCOLOR backColor);
	float GetGameTime();
	virtual GameMap* GetGameMap() { return NULL; }
};

#endif