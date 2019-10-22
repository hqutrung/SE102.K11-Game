#ifndef __SCENE__
#define __SCENE__
#include <d3dx9.h>
#include <d3d9.h>

class Scene
{
public:

	virtual void Update(float dt) = 0;
	virtual void LoadContent() = 0;
	virtual void Render() = 0;

	virtual void ProcessInput();
	virtual int GetSceneID() = 0;

	D3DCOLOR GetBackcolor();
	void SetBackColor(D3DCOLOR backColor);
	
	~Scene();

protected:
	Scene();

	D3DCOLOR                backColor;

private:
};

#endif