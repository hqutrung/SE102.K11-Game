#pragma once
#include "Graphic.h"

class GameManager {

	HWND hWnd;
	HINSTANCE hInstance;

	bool isPause;
	Graphic* graphic;
	//KeyBoard* keyBoard;
	//SceneManager* sceneManager;

public:
	GameManager(HWND hWnd, HINSTANCE hInstance);
	~GameManager();

	void Update(DWORD dt);
	void Render();
	void ProcessInput();

};