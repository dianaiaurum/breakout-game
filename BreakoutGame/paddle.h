#pragma once
#ifndef PADDLE_H
#include "entity.h"
#include "constants.h"

// A class to represent a paddle
// Inherits from moving_entity
// The paddle moves across the bottom of the screen, under the user's control
// When the ball hits the paddle, it will bounce and change its direction
class paddle : public moving_entity {
private:
	static sf::Texture texture;

public:
	// Interface of the class

// Constructor
// Arguments are the initial coordinates of the centre of the paddle
	paddle(float x, float y);

// Implement the pure virtual functions
	void update() override;
	void draw(sf::RenderWindow& window) override;
	void reset_position(float x, float y) override;
	void set_velocity() override;

// Respond to input data from the player
	void process_player_input() override;

};

#endif // !PADDLE_H

