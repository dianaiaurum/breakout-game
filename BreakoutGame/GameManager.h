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

// A class to manage the entities in the game
// It stores the entities in a vector of std::unique_ptr
// The manager can create an entity object and add it to the vector

// Example: create a ball object at position (x, y) on the screen
// manager.create<ball>(x, y);

// When an entity is destroyed, the game will mark it as destroyed, but not delete it.
// Instead, the manager will scan all entities and clean up the destroyed ones

// The manager can also locate all the objects with a given entity type
// These are stored as alias pointers (non-owning) to the allocated objects
// This is useful for performing an operation on e.g. all bricks

// Use aliases to simplify the code
using entity_vector = std::vector<std::unique_ptr<entity>>;
using entity_alias_vector = std::vector<entity*>;

class EntityManager {
	//A vector to store all the entities in the game (all brick objects, background, ball, paddle)
	entity_vector all_entities;

	//A map to store the entities grouped by type
	//We can iterate over this to get a vector of all brick objects, then a vector of all ball objects, etc
	//The vector will contain non-owning pointers to the objects
	//Do not delete these pointers!
	//Do not use them after the objects they point to have been destroyed!
	std::map<size_t, entity_alias_vector> grouped_entities;

public:
	//Function to create an entity object of type T using args as the constructor arguments
	//We use a variadic template to pass any number of arguments
	//We use perfect forwarding to avoid any innecessary copying of the arguments
	template <typename T, typename... Args> //template can have multiple types
	T& create(Args&&...args) {  //forwarding reference
		//Check that the type parameter is derived from the entity base class - extra caution, not necessary
		static_assert(std::is_base_of<entity, T>::value,
			R"("T" type parameter in create() must be derived from "entity")");

		//Create a unique_ptr to entity
		//Forward the arguments to the entity's constructor
		auto ptr{ std::make_unique<T>(std::forward<Args>(args)...) };

		//Make an alias pointer to the allocated memory
		//This will be stored in the entity_type_vector
		auto ptr_alias = ptr.get();

		//Get the hash code for the entity object's type - hash codes are unique for each object
		auto hash = typeid(T).hash_code();

		// Insert the alias pointer into the map
		grouped_entities[hash].emplace_back(ptr_alias);

		// Insert the object's pointer into the entities vector
		all_entities.emplace_back(std::move(ptr));

		// Return the new object
		return *ptr_alias;
	}

	//Function to scan all entities and clean up destroyed ones
	void refresh();

	//Function to destroy all entities
	void clear();

	//Function to retrieve all objects of a given type
	template <typename T>
	auto& get_all() {
		return grouped_entities[typeid(T).hash_code()];
	}

	//Apply a function to all entities of a given type
	template <typename T, typename Func>
	void apply_all(const Func& func) {
		auto& entity_group{ get_all<T>() };

		for (auto ptr : entity_group)
			func(*dynamic_cast<T*>(ptr));
	}

	//Function to update all entities
	void update();

	//Function to make all entities draw themselves
	void draw(sf::RenderWindow& window);
};

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

	//Instead of embedding every entity in the game class, use an entity_manager
	EntityManager manager;

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
