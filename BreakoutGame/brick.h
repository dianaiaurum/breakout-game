#pragma once
#ifndef BRICK_H
#define BRICK_H
#include "entity.h"
#include "constants.h"

//Class to represent a brick
//Inherits from entity
//A grid of bricks is displayed across the top of the screen
//This grid will be represented by an std::vector of brick obj
//When the ball hits a brick, the brick is destroyd and dissapears
//When a brick is destroyed, it is deleted from the vector

class brick : public moving_entity {
private:
	static sf::Texture texture;

public:
	brick(float x, float y);
	void update() override;
	void draw(sf::RenderWindow& window) override;

	void process_player_input() override;


};

#endif // !BRICK_H