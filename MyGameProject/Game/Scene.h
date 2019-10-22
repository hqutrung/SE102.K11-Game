#ifndef __SCENE__
#define __SCENE__
#include <d3dx9.h>
#include <d3d9.h>

class Scene
{
public:

	virtual void Update(float dt);
	virtual void LoadContent();
	virtual void Render() =0;

	D3DCOLOR GetBackcolor();
	
	~Scene();

protected:
	Scene();

	D3DCOLOR                mBackColor;

private:
};

#endif