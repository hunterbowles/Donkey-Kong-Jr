#pragma once
#include "GameObject.h"

class Player :
	public GameObject
{
public:
	Player();
	~Player();
	void die();
	void input();
private:
};

