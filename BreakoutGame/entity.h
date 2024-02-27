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
	//Virtual destructor
	virtual ~entity() {}
};

#endif  // ! ENTITY_H