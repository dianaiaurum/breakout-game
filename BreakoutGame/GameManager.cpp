#include "GameManager.h"

GameManager::GameManager()  {
	//The ball, background and paddle are initialized in-place
	//Populate the bricks vector
	for (int i = 1; i <= constants::brick_collumns; i++) {
		for (int j = 1; j <= constants::brick_rows; j++) {
			//Calculate brick's possition
			float x = constants::brick_offset + i * constants::brick_width;
			float y = j * constants::brick_height;

			//Create the brick object
			bricks.emplace_back(x, y);
		}
	}
	//Limit framerate
	//This allows other processes to run and reduces power consumption
	game_window.setFramerateLimit(60);   //Max framerate is 60 fps

}

//Game loop
//Clear the screen
//Check for new events
//Calculate updated graphics
//Display updated graphics
void GameManager::run(){
	

	//Was the pause key pressed in the last frame? - anticipates the user pressing
	//and holding gown the pause key
	bool pause_key_active{ false };

	//Game loop
	
	while (game_window.isOpen()) {
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) && !start_key_active) {
			start_key_active = true;
			the_ball.set_velocity();
		}
		
		game_state::running;
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
			break;

		//If the user presses "P", we pause/unpause the game
		//To prevent repeated use, we ignore it if it was pressed in the last iteration
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
			//If it was not pressed in the last iteration, toggle the status
			if (!pause_key_active) {
				if (state == game_state::paused)
					state = game_state::running;
				else
					state = game_state::paused;
			}
			pause_key_active = true;
		}
		else
			pause_key_active = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
			reset();

		//Calculate the updated graphics if the game is not paused
		if (state != game_state::paused) {
			the_background.update();
			the_ball.update();
			the_paddle.update();

			for (auto& b : bricks)
				b.update();

			handle_collision(the_ball, the_paddle);

			//Check every brick for collision with the ball
			for (auto& b : bricks)
				handle_collision(the_ball, b);

			//Erase any destroyed bricks
			bricks.erase(std::remove_if(std::begin(bricks), std::end(bricks),
				[](const brick& b) {return b.is_destroyed(); }),
				std::end(bricks));
		}
		
		//Display the updated graphics
		the_background.draw(game_window);
		the_ball.draw(game_window);
		the_paddle.draw(game_window);
		for (auto& b : bricks)
			b.draw(game_window);


		game_window.display();
	}
}

void GameManager::reset(){
	//We reset the start key
	start_key_active = false;
	//Repopulate the brick grid

	manager.clear();

	manager.create<background>(0.0f, 0.0f);
	manager.create<ball>(constants::window_width / 2, constants::window_height - constants::paddle_height - the_ball.get_centre().y * 2);
	manager.create<paddle>(constants::window_width / 2, constants::window_height - constants::paddle_height);

	for (int i = 1; i <= constants::brick_collumns; i++) {
		for (int j = 1; j <= constants::brick_rows; j++) {
			//Calculate brick's possition
			float x = constants::brick_offset + i * constants::brick_width;
			float y = j * constants::brick_height;

			//Create the brick object
			bricks.emplace_back(x, y);
		}
	}
}

void EntityManager::refresh()
{
}

void EntityManager::clear()
{
}

void EntityManager::update()
{
}

void EntityManager::draw(sf::RenderWindow& window)
{
}
