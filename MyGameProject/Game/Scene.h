#ifndef __SCENE__
#define __SCENE__
#include <d3dx9.h>
#include <d3d9.h>

class Scene
{

protected:
	D3DCOLOR                backColor;

	Scene();

public:

	virtual ~Scene();

	virtual void Update(float dt) = 0;
	virtual void LoadContent() = 0;
	virtual void Render() = 0;

	virtual void ProcessInput();
	virtual int GetSceneID() = 0;

	D3DCOLOR GetBackcolor();
	void SetBackColor(D3DCOLOR backColor);
	
};

#endif