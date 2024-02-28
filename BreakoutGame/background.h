#pragma once
#ifndef  BACKGROUND_H
#define  BACKGROUND_H


#include "constants.h"
#include "entity.h"

//Class to represent the background
//Inherits from entity
class background : public entity {
private:
	static sf::Texture texture;

public:
	//Interface of the class

	//Constructor
	//Arguments are the initial coordinates of the center of the background
	//SFML uses computer graphics convention -> (0,0) is in the top-left corner
	background(float x, float y);

	//Implement pure virtual functions
	void update() override;
	void draw(sf::RenderWindow& window) override;

};

#endif // ! BACKGROUND_H
