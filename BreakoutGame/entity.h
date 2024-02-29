#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

//Abstract base class to represent any graphical entity on the screen
class entity {
protected:
	sf::Sprite sprite;
	bool destroyed{ 0 };


public:
	//Pure member functions -> concrete graphical entities must implement these functions
	//The update member function will compute the new possition, appearance, etc of the object
	//The display member function will display the object in the game window
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	//Helper functions for the state of the entity
	void destroy() noexcept;
	bool is_destroyed() const noexcept;

	//Helper function to get the bounding box of a sprite
	sf::FloatRect get_bounding_box() const noexcept;

	//Helper function to het the center of a sprite
	sf::Vector2f get_centre() const noexcept;

	//Helper function to get the position of the sprite
	float x() const noexcept;
	float y() const noexcept;

	//Virtual destructor
	virtual ~entity() {}
};

class moving_entity : public entity {
protected:
	sf::Vector2f velocity;
	bool game_started{ false };


public:
	//Pure virtual functions inherited from parent class
	virtual void process_player_input() = 0;
	virtual void reset_position(float x, float y) = 0;
	virtual void set_velocity() = 0;

	//Helper functions to get the edges of the sprite
	float left() const noexcept;
	float right() const noexcept;
	float top() const noexcept;
	float bottom() const noexcept;

	
};



#endif  // ! ENTITY_H