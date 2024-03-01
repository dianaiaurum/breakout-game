#include "brick.h"

// Initialize static data
sf::Texture brick::texture;

// Use different colors, depending on the strength of the brick
// Fromat: RGBA (a - aplha - opacity)
const sf::Color brick_colour_hit1{ 0, 255, 0, 80 }; // Dull green
const sf::Color brick_colour_hit2{ 0, 255, 0, 170 }; // Medium green
const sf::Color brick_colour_hit3{ 0, 255, 0, 255 }; // Bright green

brick::brick(float x, float y){
	texture.loadFromFile("brick01.png");
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	sprite.setOrigin(get_centre());
}

void brick::update(){
	switch (strength){
		case 3: {
			sprite.setColor(brick_colour_hit3);
			break; }
		case 2: {
			sprite.setColor(brick_colour_hit2);
			break; }
		case 1: {
			sprite.setColor(brick_colour_hit1);
			break; }
		default:
			break;
	}
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

void brick::set_strength(int s) noexcept{
	strength = s;
}

void brick::weaken() noexcept {
	if (strength > 0) strength--;
}

bool brick::is_weakened() const noexcept{
	return strength <= 0;
}


