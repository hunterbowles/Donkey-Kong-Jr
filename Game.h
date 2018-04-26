#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Vine.h"
#include "Chomp.h"
#include "OChomp.h"
#include "Fruit.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <time.h>
#include <string>
#include <SFML\Audio.hpp>


class Game
{
public:
	Game();
	~Game();
	void play();
	void nextStep();
	void platformCheck();
	void vineCheck();
	void chompCheck();
	void playerCheck();
	void gameOver();
	void buildLevelOne();
	void buildLevelTwo();
	void buildLevelThree();
	void buildLevelFour();
	void clearAll();
private:
	Player* p;
	sf::RenderWindow window;
	std::vector<Platform*> plats;
	std::vector<Vine*> vines;
	std::vector<Chomp*> chomps;
	std::vector<OChomp*> ochomps;
	sf::Music music;
	sf::Font f;
	sf::Text lives, score;
	sf::Event event;
	sf::Texture t;
	//sf::Sprite key;
	//Fruit fruit;
};

