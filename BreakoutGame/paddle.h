#pragma once
#ifndef PADDLE_H
#include "entity.h"
#include "constants.h"

class paddle : public moving_entity {
private:
	sf::Texture texture;

public:
	paddle(float x, float y);
	void update() override;
	void draw(sf::RenderWindow& window) override;
	void process_player_input() override;
};

#endif // !PADDLE_H

