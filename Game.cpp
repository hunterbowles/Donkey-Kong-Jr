#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	srand(time(NULL));
	window.create(sf::VideoMode(520, 600), "DK Jr");
	p = new Player(10, 500);

	window.setFramerateLimit(60);
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	if (!f.loadFromFile("Sprites\\game_over.ttf"))
	{
		std::cout << "you no good :(" << std::endl;
	}

	t.loadFromFile("Sprites/spritesheet.png");
	key.setTexture(t);

	deathWait = false;
	level = 1;

	lives.setFont(f);
	score.setFont(f);
	levelsPlayed = 1;
}


Game::~Game()
{
	clearAll();

	delete p;
}


//Method to clear the game board.
void Game::clearAll()
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
}


//Method with the play loop.
void Game::play()
{
	buildLevelOne();

	while (window.isOpen())
	{
		if (p->getLives() >= 0)
		{
			if (deathWait)
			{
				_sleep(2000);
				deathWait = false;
			}

			nextStep();
			platformCheck();
			vineCheck();
			chompCheck();
			playerCheck();
			window.display();
			window.clear();

			//Test Purposes. Make beeter pls
			window.draw(key);

			
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


//Method to set up all the variables for the next step.
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


//Method to see what is on a platform.
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


//Method to see what is on a vine.
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


//Method to see what is touching a chomp.
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


//Method to check what the player is pressing.
void Game::playerCheck()
{

		if (p->getTouchingEnemy() || p->getY() > window.getSize().y)
		{
			p->die();
			//Deletes all pointers in Chomps
			for (int i = 0; i< chomps.size(); i++)
				delete (chomps[i]);
			chomps.clear();

			//Deletes all pointers in Chomps
			for (int i = 0; i< ochomps.size(); i++)
				delete (ochomps[i]);
			ochomps.clear();

			buildChomps();

			deathWait = true;
		}
		else
		{
			p->step();
			window.draw(p->getSprite());
		}

		if (p->getBB().intersects(key.getGlobalBounds()))
		{
			switch (level)
			{
			case 1:
				levelsPlayed++;
				buildLevelTwo();
				_sleep(2000);
				break;
			case 2:
				levelsPlayed++;
				buildLevelOne();
				_sleep(2000);
				break;
			}
			p->setScore(p->getScore() + 500);
		}

	lives.setPosition(5, 0);
	lives.setString("Lives: " + std::to_string(p->getLives()));
	window.draw(lives);
	score.setPosition(5, 15);
	score.setString("Score:  " + std::to_string(p->getScore()));
	window.draw(score);
}


//Tell the user they have lost.
void Game::gameOver()
{
	lives.setString("Game Over");
	lives.setScale(5, 5);
	lives.setPosition(window.getSize().x / 4 - 25, window.getSize().y / 4);
	window.draw(lives);
	lives.setString("Press Space to Play Again!");
	lives.setScale(3, 3);
	lives.setPosition(window.getSize().x / 8 - 26, window.getSize().y / 4 + 100);
	window.draw(lives);
	window.display();
	window.clear();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		p->setLives(3);
		p->setScore(0);
		lives.setScale(1, 1);
		clearAll();
		window.clear();
		levelsPlayed = 1;
		buildLevelOne();
		p->setX(10);
		p->setY(500);
	}
}


//Build all the chomps.
void Game::buildChomps()
{
	//blue bois
	for (int i = 0; i < levelsPlayed; i++)
	{
		chomps.push_back(new Chomp(200, 100));
		ochomps.push_back(new OChomp(200, 100));
	}
}


//Build Level One.
void Game::buildLevelOne()
{
	clearAll();
	if (!music.openFromFile("Sprites\\yes.ogg"))
		std::cout << "Not working" << std::endl; // error
	music.play();

	plats.push_back(new Platform(5, 0, 562, 1));//1
	plats.push_back(new Platform(2, 185, 524, 1));//2
	plats.push_back(new Platform(2, 278, 543, 1));//3
	plats.push_back(new Platform(2, 352, 524, 1));//4
	plats.push_back(new Platform(2, 440, 506, 1));//5
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
	vines.push_back(new Vine(9, 200, 189));
	vines.push_back(new Vine(6, 280, 189));
	//Middle Right
	vines.push_back(new Vine(10, 335, 206));
	vines.push_back(new Vine(8, 391, 206));
	//Right top
	vines.push_back(new Vine(7, 447, 112));
	vines.push_back(new Vine(7, 503, 112));
	//Right Bottom
	vines.push_back(new Vine(3, 447, 356));
	vines.push_back(new Vine(3, 503, 356));
	//Lil boi
	vines.push_back(new Vine(2, 180, 80));

	buildChomps();

	p->setX(10);
	p->setY(500);

	//MAKE BETTER
	key.setTextureRect(sf::IntRect(189, 182, 16, 16));
	key.setScale(2, 2);
	key.setPosition(87, 58);

	//Fruit Testing
	//fruit = Fruit(0, 0, 0);

	level = 1;
}


//Build Level Two.
void Game::buildLevelTwo()
{
	clearAll();
	if (!music.openFromFile("Sprites\\yes.ogg"))
		std::cout << "Not working" << std::endl; // error
	music.play();

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
	vines.push_back(new Vine(9, 200, 189));
	vines.push_back(new Vine(6, 280, 189));
	//Middle Right
	vines.push_back(new Vine(10, 335, 206));
	vines.push_back(new Vine(8, 391, 206));
	//Right top
	vines.push_back(new Vine(7, 447, 112));
	vines.push_back(new Vine(7, 503, 112));
	//Right Bottom
	vines.push_back(new Vine(3, 447, 356));
	vines.push_back(new Vine(3, 503, 356));
	//Lil boi
	vines.push_back(new Vine(2, 180, 80));

	buildChomps();

	//MAKE BETTER
	key.setTextureRect(sf::IntRect(189, 182, 16, 16));
	key.setScale(2, 2);
	key.setPosition(87, 58);

	p->setX(10);
	p->setY(500);

	//Fruit Testing
	//fruit = Fruit(0, 0, 0);

	level = 2;
}


//Build Level Three.
void Game::buildLevelThree()
{

}


//Build Level Four.
void Game::buildLevelFour()
{

}
