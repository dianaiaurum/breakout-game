#include "paddle.h"
#include "iostream"
paddle::paddle(float x, float y) {
	texture.loadFromFile("paddle.png");
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	velocity = { constants::no_speed, constants::no_speed };
	//Make the origin of the sprite the center instead of the top-left corner
	sprite.setOrigin(get_centre());
}

void paddle::update() {
	//Paddle moves as long as one of the keys is pressed
	//The paddle should not go out of window bounds
	sprite.move(velocity);
	process_player_input();

}

void paddle::process_player_input() {
	//Paddle moves as long as one of the keys is pressed
	//The paddle should not go out of window bounds
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		if (x() > 0)
			velocity.x = -constants::paddle_speed;
		else
			velocity.x = constants::no_speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		if (x() < constants::window_width)
			velocity.x = constants::paddle_speed;
		else
			velocity.x = constants::no_speed;
	}
	else velocity.x = 0;
}

void paddle::reset_position(float x, float y){
	sprite.setPosition(x, y);
}

void paddle::set_velocity()
{
}

void paddle::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
