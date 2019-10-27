#pragma once

class DemoObject;
class DemoObjectState;

class DemoObjectData
{
public:
	DemoObjectData() {};
	~DemoObjectData() {};

	DemoObject* DemoObject;
	DemoObjectState* state;
};
