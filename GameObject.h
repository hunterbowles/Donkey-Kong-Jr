#pragma once
#include <SFML\Graphics.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();
private:
	int x, y, velocity, team;
	sf::Sprite skin;
};
