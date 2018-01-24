#pragma once
#include "GameObject.h"

class Chomp : public GameObject
{
public:
	Chomp();
	void goDown();
	void fallOff();
	~Chomp();
};

