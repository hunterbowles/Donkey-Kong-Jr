#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Vine.h"
#include "Chomp.h"
#include "OChomp.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <SFML\Audio.hpp>
#include <time.h>


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
	void buildChomps();
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
	sf::Sprite key;
	sf::Texture t;
	bool deathWait;
	int level, levelsPlayed;
};

