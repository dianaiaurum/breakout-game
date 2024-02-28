//Code for a "breakout" game
//Final project of UDEMY C++ course
//Uses the SFM graphics library
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

int main() {
	//Create the background object
	background the_background(0.0f, 0.0f);
	
	//Create ball
	ball the_ball(constants::window_width / 2, constants::window_height / 2);

	//Create the paddle
	paddle the_paddle(constants::window_width / 2, constants::window_height - constants::paddle_height);

	//Populate bricks
	std::vector<brick> bricks;

	for (int i = 1; i <= constants::brick_columns; i++) {
		for (int j = 1; j <= constants::brick_rows; j++) {
			//Calculate brick's possition
			float x = constants::brick_offset + i * constants::brick_width;
			float y = j * constants::brick_height;

			//Create the brick object
			bricks.emplace_back(x, y);
		}
	}

	//Create the game's window using an object of class RenderWindow
	//The constructor takes and SFML 2d vector with the window dimensions
	//and an std::string with the window title
	//The sfml code is in the sf namespace
	sf::RenderWindow game_window{ {constants::window_width, constants::window_height},
								"Simple Breakout version 1" };

	//Limit framerate
	//This allows other processes to run and reduces power consumption
	game_window.setFramerateLimit(60);   //Max framerate is 60 fps

	//Game loop
	//Clear the screen
	//Check for new events
	//Calculate updated graphics
	//Display updated graphics
	while (game_window.isOpen()) {
		//Clear the screen
		game_window.clear(sf::Color::Black);

		//Check for new events
		sf::Event event;

		//If the user presses Escape or clicks "close", we close the window
		//This terminates the program
		while (game_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) game_window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			game_window.close();

		//Calculate the updated graphics
		the_background.update();
		the_ball.update();
		the_paddle.update();

		for (auto& b : bricks) 
			b.update();
	
		handle_collision(the_ball, the_paddle);

		//Display the updated graphics
		the_background.draw(game_window);
		the_ball.draw(game_window);
		the_paddle.draw(game_window);
		for (auto& b : bricks)
			b.draw(game_window);

		
		game_window.display();

	}
}