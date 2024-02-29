#pragma once
#ifndef BALL_H
#define BALL_H
#include "entity.h"
#include "constants.h"

class ball : public moving_entity {
private:
	static sf::Texture texture;

public:
	//Constructor
	//Arguments are the initial coordinates of the center of the ball
	//SFML uses computer graphics convention -> (0,0) is in the top-left corner
	ball(float x, float y);
	void update() override;
	void draw(sf::RenderWindow& window) override;
	void process_player_input() override;
	void reset_position(float x, float y) override;
	void set_velocity() override;
	void move_up();
	void move_down();
	void move_left();
	void move_right();

};
#endif // !BALL_H
