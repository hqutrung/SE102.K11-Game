#include "KeyBoard.h"
#include "Debug.h"

KeyBoard* KeyBoard::Instance = NULL;

KeyBoard* KeyBoard::GetInstance()
{
	if (!Instance)
		Instance = new KeyBoard();
	return Instance;
}

HRESULT KeyBoard::Init(HWND hWnd)
{
	HRESULT result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, NULL);
	if (result != DI_OK)
	{		return result;
	}
	result = dinput->CreateDevice(GUID_SysKeyboard, &dikeyboard, NULL);
	if (result != DI_OK)
	{
	
		return result;
	}
	result = dikeyboard->SetDataFormat(&c_dfDIKeyboard);
	result = dikeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);;
	result = dikeyboard->Acquire();

	result = dinput->CreateDevice(GUID_SysMouse, &dimouse, NULL);
	if (result != DI_OK)
	{
		
		return result;
	}
	result = dimouse->SetDataFormat(&c_dfDIMouse);
	result = dimouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	result = dimouse->Acquire();		
	return result;
}

void KeyBoard::KeySnapShot(float dt)
{

	delta += dt;
	if (delta > KEYBOARD_LAST_PRESS_TIME)
		ReleaseLastPressKey();
	for (int i = 0; i < 256; i++)
		buffer[i] = keys[i];

	HRESULT result = dikeyboard->GetDeviceState(sizeof(keys), (LPVOID)&keys);
	while (result != DI_OK && (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED))
	{
		//Debug::PrintOut(L"[Error code %d] Error while Acquire Keyboard!", &result);
		result = dikeyboard->Acquire();
	}
	FirstCheck = true;
}

void KeyBoard::MouseSnapShot()
{
	dimouse->GetDeviceState(sizeof(mouse_state), (LPVOID)&mouse_state);
}

bool KeyBoard::GetKey(int key)
{
	if (keys[key] & 0x80)
	{
		if (FirstCheck && buffer[key] != keys[key])
		{
			BufferLastKey = LastKey;
			LastKey = key;
			delta = 0.0f;
			FirstCheck = false;
		}
		return true;
	}
	return false;
}

bool KeyBoard::GetKeyDown(int Key)
{
	return GetKey(Key) && !BufferCheck(Key);
}

bool KeyBoard::GetKeyUp(int Key)
{
 	return !GetKey(Key) && BufferCheck(Key);
}

void KeyBoard::Release()
{
	delete Instance;
}

int KeyBoard::GetLastPressKey()
{
	return BufferLastKey;
}

void KeyBoard::ReleaseLastPressKey()
{
	delta = 0.0f;
	BufferLastKey = -1;
	LastKey = -1;
}

KeyBoard::KeyBoard()
{

}

KeyBoard::~KeyBoard()
{
	if (dikeyboard != NULL)
	{
		dikeyboard->Unacquire();
		dikeyboard->Release();
		dikeyboard = NULL;
	}
	if (dimouse != NULL)
	{
		dimouse->Unacquire();
		dimouse->Release();
		dimouse = NULL;
	}
	if (dinput != NULL)
		dinput->Release();
}

bool KeyBoard::BufferCheck(int key)
{
	return buffer[key] & 0x80;
}
