#pragma once
#include "Graphic.h"
#include"SceneManager.h"
#include "KeyBoard.h"

class GameManager {

	HWND hWnd;
	HINSTANCE hInstance;

	bool isPause;

public:
	GameManager(HWND hWnd, HINSTANCE hInstance);
	~GameManager();

	void Update(float dt);
	void Render();
	void ProcessInput();

};