#include "ball.h"

sf::Texture ball::texture;

ball::ball(float x, float y) {
	texture.loadFromFile("ball.png");
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	velocity = { constants::ball_speed, constants::ball_speed };
	sprite.setOrigin(get_centre());

}

void ball::update() {
	sprite.move(velocity);

	//We check if the ball has moved out of the left of right side of the screen
	//If its out of bounds, we reverse the velocity so that it will "bounce back"
	if (x() < 0 || x() > constants::window_width) {
		velocity.x = -velocity.x;
	}
	if (y() < 0 || y() > constants::window_height) {
		velocity.y = -velocity.y;
	}
}

void ball::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

void ball::process_player_input()
{
}

void ball::move_up(){
	velocity.y = -constants::ball_speed;
}

void ball::move_left(){
	velocity.x = -constants::ball_speed;
}

void ball::move_right(){
	velocity.x = constants::ball_speed;
}
