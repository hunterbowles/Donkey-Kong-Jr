#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	window.create(sf::VideoMode(520, 600), "DK Jr");
	p = new Player(20, 500);

	window.setFramerateLimit(60);
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	if (!f.loadFromFile("Sprites\\game_over.ttf"))
	{
		std::cout << "you no good :(" << std::endl;
	}

	lives.setFont(f);
	score.setFont(f);
}


Game::~Game()
{
	//Deletes all pointers in Plats
	for (int i = 0; i< plats.size(); i++)
		delete (plats[i]);
	plats.clear();

	//Deletes all pointers in Vines
	for (int i = 0; i< vines.size(); i++)
		delete (vines[i]);
	vines.clear();

	//Deletes all pointers in Chomps
	for (int i = 0; i< chomps.size(); i++)
		delete (chomps[i]);
	chomps.clear();

	//Deletes all pointers in Chomps
	for (int i = 0; i< ochomps.size(); i++)
		delete (ochomps[i]);
	ochomps.clear();

	delete p;
}


void Game::play()
{
	buildLevelOne();

	while (window.isOpen())
	{
		if (p->getLives() >= 0)
		{

			nextStep();
			platformCheck();
			vineCheck();
			chompCheck();
			playerCheck();
			window.display();
			window.clear();
		}
		else
		{
			gameOver();
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
		}
	}
}


void Game::nextStep()
{
	//Reset
	p->input();
	p->setOnPlat(false);
	p->setTouchingEnemy(false);

	for (int i = 0; i < chomps.size(); i++)
		chomps.at(i)->setOnVine(false);
	for (int i = 0; i < ochomps.size(); i++)
		ochomps.at(i)->setOnVine(false);

}


void Game::platformCheck()
{
	//Check collisions with the platforms
	//and draw platforms.
	for (int i = 0; i < plats.size(); i++)
	{
		if (plats.at(i)->collision(p))
			p->setOnPlat(true);

		for (int j = 0; j < chomps.size(); j++)
		{
			if (!chomps.at(j)->getOnVineAgain())
				plats.at(i)->collision(chomps.at(j));
		}
		for (int j = 0; j < ochomps.size(); j++)
		{
			if (!ochomps.at(j)->getOnVineAgain())
				plats.at(i)->collision(ochomps.at(j));
		}
		plats.at(i)->drawPlat(window);
	}
}


void Game::vineCheck()
{
	//Check collisions with the vines
	if (vines.at(0)->allVines(vines, p) == 0)
	{
		p->setOnVine(false);
		p->setDualCollide(false);
	}
	else if (vines.at(0)->allVines(vines, p) == 1)
	{
		p->setOnVine(true);
		p->setDualCollide(false);
	}
	else if (vines.at(0)->allVines(vines, p) == 2)
	{
		p->setDualCollide(true);
		p->setOnVine(true);
	}
	//Draw vines.
	for (int i = 0; i < vines.size(); i++)
	{
		vines.at(i)->drawVine(window);
	}

}


void Game::chompCheck()
{
	//Check collision with the chomps
	for (int i = 0; i < chomps.size(); i++)
	{
		vines.at(0)->allVines(vines, chomps.at(i));
		chomps.at(i)->step();
		if (chomps.at(i)->collision(p))
			p->setTouchingEnemy(true);
		window.draw(chomps.at(i)->getSprite());
	}

	//Check collision with the chomps
	for (int i = 0; i < ochomps.size(); i++)
	{
		vines.at(0)->allVines(vines, ochomps.at(i));
		ochomps.at(i)->step();
		if (ochomps.at(i)->collision(p))
			p->setTouchingEnemy(true);
		window.draw(ochomps.at(i)->getSprite());
	}
}


void Game::playerCheck()
{
	if (p->getTouchingEnemy() || p->getY() > window.getSize().y)
	{
		p->die();
		for (int i = 0; i < ochomps.size(); i++)
		{
			ochomps.at(i)->setX(200);
			ochomps.at(i)->setY(100);
		}
		for (int i = 0; i < chomps.size(); i++)
		{
			chomps.at(i)->setX(200);
			chomps.at(i)->setY(100);
		}
	}

	p->step();
	window.draw(p->getSprite());

	lives.setPosition(5, 0);
	lives.setString("Lives: " + std::to_string(p->getLives()));
	window.draw(lives);
	score.setPosition(5, 15);
	score.setString("Score:  " + std::to_string(p->getScore()));
	window.draw(score);
}


void Game::gameOver()
{
	lives.setString("Game Over");
	lives.setScale(5, 5);
	lives.setPosition(window.getSize().x / 4 - 25, window.getSize().y / 4);
	window.draw(lives);
	window.display();
	window.clear();
}


void Game::buildLevelOne()
{
	if (!music.openFromFile("Sprites\\yes.ogg"))
		std::cout << "Not working" << std::endl; // error
												 //music.play();

	plats.push_back(new Platform(5, 0, 562, 1));//1
	plats.push_back(new Platform(2, 185, 524, 1));//2
	plats.push_back(new Platform(2, 278, 543, 1));//3
	plats.push_back(new Platform(2, 352, 524, 1));//4
	plats.push_back(new Platform(2, 445, 506, 1));//5
	plats.push_back(new Platform(4, 80, 393, 2));//6
	plats.push_back(new Platform(3, 80, 280, 2));//7
	plats.push_back(new Platform(5, 415, 337, 2));//8
	plats.push_back(new Platform(5, 305, 188, 2));//9
	plats.push_back(new Platform(13, 0, 168, 2));//10
	plats.push_back(new Platform(2, 80, 93, 2));//11

												//Long first two
	vines.push_back(new Vine(13, 1, 189));
	vines.push_back(new Vine(13, 57, 189));
	//Short ones next to the two plats
	vines.push_back(new Vine(2, 112, 301));
	vines.push_back(new Vine(4, 112, 413));
	//Middle two
	vines.push_back(new Vine(9, 206, 189));
	vines.push_back(new Vine(6, 280, 189));
	//Middle Right
	vines.push_back(new Vine(10, 335, 206));
	vines.push_back(new Vine(8, 391, 206));
	//Right top
	vines.push_back(new Vine(7, 440, 112));
	vines.push_back(new Vine(7, 496, 112));
	//Right Bottom
	vines.push_back(new Vine(3, 440, 356));
	vines.push_back(new Vine(3, 496, 356));
	//Lil boi
	vines.push_back(new Vine(2, 180, 80));

	//blue bois
	chomps.push_back(new Chomp(150, 100));
	chomps.push_back(new Chomp(250, 100));

	//orange bois
	ochomps.push_back(new OChomp(200, 100));
}


void Game::buildLevelTwo()
{

}


void Game::buildLevelThree()
{

}

void Game::buildLevelFour()
{

}
