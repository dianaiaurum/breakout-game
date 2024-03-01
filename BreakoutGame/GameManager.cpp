#include <algorithm>

#include "GameManager.h"
#include "collisions.h"

//Function to scan all entities and clean up destroyed ones
void EntityManager::refresh() {
	//We must clean up the alias pointers first, to avoid dangling pointers
	//We simply remove them from their vector
	for (auto& [type, alias_vector] : grouped_entities) {
		//remove_if takes an iterator range and a predicate
		//All the elements for which the predicate is true are moved to the back
		//It returns an iterator to the first moved element
		//erase takes an iterator range and deletes all elements in the range
		alias_vector.erase(std::remove_if(begin(alias_vector), end(alias_vector),
			[](const auto& p) {return p->is_destroyed(); }),
			end(alias_vector));
	}

	//Now we can safely deestroy thee objects, now that there are no aliases to them
	all_entities.erase(remove_if(begin(all_entities), end(all_entities),
		[](const auto& p) {return p->is_destroyed(); }),
		end(all_entities));
}

//Function to destroy all entities
void EntityManager::clear() {
	//Again, we must clear up the alias pointers first
	grouped_entities.clear();
	all_entities.clear();
}

//Function to update all the entities
void EntityManager::update() {
	for (auto& e : all_entities)
		e->update();
}

//Function to make all entities draw themselves
void EntityManager::draw(sf::RenderWindow& window) {
	for (auto& e : all_entities)
		e->draw(window);
}

GameManager::GameManager() {
	game_window.setFramerateLimit(60);   //Max framerate is 60 fps

	// Load a font from file
	verdana.loadFromFile("C:/Windows/fonts/Verdana.ttf");

	//Configure our text objects
	text_state.setFont(verdana);
	text_state.setPosition(constants::window_width / 2.0f - 100.0f, constants::window_height / 2.0f - 100.0f);
	text_state.setCharacterSize(35);
	text_state.setFillColor(sf::Color::White);
	text_state.setString("Paused");

	text_lives.setFont(verdana);
	text_lives.setPosition(constants::window_width / 2.0f - 65.0f, constants::window_height / 2.0f - 50.0f);
	text_lives.setCharacterSize(35);
	text_lives.setFillColor(sf::Color::White);
	text_lives.setString("Lives: " + std::to_string(lives));

}

void GameManager::reset() {
	set_lives();
	state = game_state::paused;
	//We reset the start key
	//start_key_active = false;
	//Repopulate the brick grid

	manager.clear();

	manager.create<background>(0.0f, 0.0f);
	manager.create<ball>(constants::window_width / 2, constants::window_height - constants::paddle_height - 13.0f);
	manager.create<paddle>(constants::window_width / 2, constants::window_height - constants::paddle_height);

	for (int i = 1; i <= constants::brick_collumns; i++) {
		for (int j = 1; j <= constants::brick_rows; j++) {
			//Calculate brick's possition
			float x = constants::brick_offset + i * constants::brick_width;
			float y = j * constants::brick_height;

			//Create the brick object
			manager.create<brick>(x, y);
		}
	}
}

void GameManager::lose_a_life() noexcept{
	if (lives > 0) lives--;
}

void GameManager::set_lives() noexcept{
	lives = constants::player_lives;
}



//Game loop
//Clear the screen
//Check for new events
//Calculate updated graphics
//Display updated graphics
void GameManager::run() {


	//Was the pause key pressed in the last frame? - anticipates the user pressing
	//and holding gown the pause key
	bool pause_key_active{ false };

	//Game loop

	while (game_window.isOpen()) {
		//game_state::running;
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

		//If the game is not running, the entities are not updated
		// They ar redrawn only if the game is paused
		if (state == game_state::paused) {
			//Display the graphics
			manager.draw(game_window);
		}

		//Calculate the updated graphics if the game is not paused
		if (state != game_state::running) {
			switch (state) {
			case game_state::paused:
				text_state.setString("   Paused   ");
				break;
			case game_state::game_over:
				text_state.setString(" Game over! ");
				break;
			case game_state::win:
				text_state.setString("Player Wins!");
				break;
			default:
				break;
			}
			game_window.draw(text_state);
			game_window.draw(text_lives);
		} 
		else {
			//If there are no remaining balls on the screen
			if (manager.get_all<ball>().empty()) {
				//Spawn a new one and reduce the player's remaining lives
				manager.create<ball>(constants::window_width / 2.0f, constants::window_height / 2.0f);
				--lives;

				state = game_state::paused;
			}

			//If there are no remaining bricks on the screen, the player has won
			if (manager.get_all<brick>().empty())
				state = game_state::win;

			// If the player has used up all of their lives, the game is over
			if (lives <= 0)
				state = game_state::game_over;

			//Update the text for the number of remaining lives
			text_lives.setString("Lives: " + std::to_string(lives));

			manager.update();

			//For every ball, call a function which
			//		For every brick, call a function which
			//			Calls handle_collision with the ball and the brick as arguments
			manager.apply_all<ball>([this](auto& the_ball) {
				manager.apply_all<brick>([&the_ball](auto& the_brick) {
					handle_collision(the_ball, the_brick);
					});
				});

			//Paddle interaction
			manager.apply_all<ball>([this](auto& the_ball) {
				manager.apply_all<paddle>([&the_ball](auto& the_paddle) {
					handle_collision(the_ball, the_paddle);
					});
				});
			manager.refresh();
			manager.draw(game_window);
		}

		//Display the updated graphics
		game_window.display();
	}
}



