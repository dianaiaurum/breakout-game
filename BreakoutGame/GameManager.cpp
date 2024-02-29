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
}

void GameManager::reset() {
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
		/*if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) && !start_key_active) {
			start_key_active = true;
			the_ball.set_velocity();
		}*/

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

		//Calculate the updated graphics if the game is not paused
		if (state != game_state::paused) {
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
		}

		//Display the updated graphics
		manager.draw(game_window);
		game_window.display();
	}
}



