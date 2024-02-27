#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

//Abstract base class to represent any graphical entity on the screen
class entity {
protected:
	sf::Sprite sprite;

public:
	//Pure member functions -> concrete graphical entities must implement these functions
	//The update member function will compute the new possition, appearance, etc of the object
	//The display member function will display the object in the game window
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

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

};


#endif  // ! ENTITY_H