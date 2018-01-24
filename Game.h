#pragma once
class Game
{
public:
	Game();
	void run();
	bool checkCollision();
	void gameOver();
	~Game();

	//Getters and Setters
	int getLives();
	int getLoops();
	int getScore();
	void setLives();
	void setLoops();
	void setScore();

private:
	int lives, loops, score;
};

