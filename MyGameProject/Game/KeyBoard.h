
#pragma once
#include <InitGuid.h>
#include <dinput.h>
#include <vector>
#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_LAST_PRESS_TIME 0.125f

class KeyBoard
{
public:
	static KeyBoard* GetInstance();
	HRESULT Init(HWND hWnd);
	void KeySnapShot(float dt);
	void MouseSnapShot();
	bool GetKey(int DIK_Key);
	bool GetKeyDown(int DIK_Key);
	bool GetKeyUp(int DIK_Key);
	void Release();

	int GetLastPressKey();
	void ReleaseLastPressKey();
private:
	KeyBoard();
	~KeyBoard();

	bool BufferCheck(int DIK_Key);

	LPDIRECTINPUT8 dinput = NULL;
	LPDIRECTINPUTDEVICE8 dikeyboard = NULL;
	LPDIRECTINPUTDEVICE8 dimouse = NULL;

	bool FirstCheck;
	float delta;
	int LastKey, BufferLastKey;

	char keys[256];
	char buffer[256];
	DIMOUSESTATE mouse_state;
	static KeyBoard* Instance;
};