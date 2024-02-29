#include "brick.h"

sf::Texture brick::texture;

brick::brick(float x, float y){
	texture.loadFromFile("brick01.png");
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	sprite.setOrigin(get_centre());
}

void brick::update(){
}

void brick::draw(sf::RenderWindow& window){
	window.draw(sprite);
}

void brick::process_player_input()
{
}

void brick::reset_position(float x, float y)
{
}

void brick::set_velocity()
{
}


