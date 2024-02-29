#include "ball.h"

sf::Texture ball::texture;

ball::ball(float x, float y) {
	texture.loadFromFile("ball.png");
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	velocity = { constants::no_speed, constants::no_speed };
	sprite.setOrigin(get_centre());

}

void ball::update() {
	//If the start key has been pressed, the ball enters its free movement; until then, the ball moves 
	//with the paddle
	sprite.move(velocity);
	if (game_started) {
		//We check if the ball has moved out of the left of right side of the screen
	//If its out of bounds, we reverse the velocity so that it will "bounce back"
		if (x() < 0 || x() > constants::window_width) {
			velocity.x = -velocity.x;
		}
		if (y() < 0 || y() > constants::window_height) {
			velocity.y = -velocity.y;
		}
	}
	else {
		process_player_input();
	}
	
}

void ball::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

void ball::process_player_input(){
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

void ball::reset_position(float x, float y){
	sprite.setPosition(x, y);
	game_started = false;
	velocity = { constants::no_speed, constants::no_speed };

}

void ball::move_up(){
	velocity.y = -constants::ball_speed;
}

void ball::move_down() {
	velocity.y = constants::ball_speed;
}

void ball::move_left(){
	velocity.x = -constants::ball_speed;
}

void ball::move_right(){
	velocity.x = constants::ball_speed;
}

void ball::set_velocity(){
	game_started = true;
	velocity = { constants::ball_speed, -constants::ball_speed };
}
