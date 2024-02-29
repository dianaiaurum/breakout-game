#pragma once
#ifndef GAMEMANAGER_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "constants.h"
#include "background.h"
#include "ball.h"
#include "paddle.h"
#include "collisions.h"
#include "brick.h"

using namespace std::literals;

class GameManager {
private:
	//Enum class with allowed values for the game's state
	enum class game_state{paused, running};

	//Member to store the current state of the game
	game_state state{ game_state::running };

	//Create the game's window using an object of class RenderWindow
	//The constructor takes and SFML 2d vector with the window dimensions
	//and an std::string with the window title
	//The sfml code is in the sf namespace
	sf::RenderWindow game_window{ {constants::window_width, constants::window_height},
								"Simple Breakout version 1" };

	//Create the background object
	background the_background{ 0.0f, 0.0f };

	//Create a ball object in the middle of the screen
	ball the_ball{ constants::window_width / 2, constants::window_height - constants::paddle_height - 13.0f };
	
	//Create a paddle object at the bottom of the screen in the middle
	paddle the_paddle{constants::window_width / 2, constants::window_height - constants::paddle_height};

	//Create the grid of bricks and store them in an std::vector
	std::vector<brick> bricks;

	//Tracks if the start key "Space" has been pressed for the game to start
	bool start_key_active{ false };


public:
	GameManager();

	//Run the game
	void run();

	//Reinitialize the game
	void reset();

};

#endif // !GAMEMANAGER_H
