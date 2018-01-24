#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}

void Game::run()
{
}

bool Game::checkCollision()
{
	return false;
}

void Game::gameOver()
{
}

Game::~Game()
{
}

int Game::getLives()
{
	return lives;
}

int Game::getLoops()
{
	return loops;
}

int Game::getScore()
{
	return score;
}

void Game::setLives(int l)
{
	lives = l;
}

void Game::setLoops(int l)
{
	loops = l;
}

void Game::setScore(int s)
{
	score = s;
}
