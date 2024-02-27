#include "background.h"

//Initialize static data - static data are shared by all instances of the class
sf::Texture background::texture;

background::background(float x, float y) : entity() {
	texture.loadFromFile("background.jpg");
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void background::update() {
	//nothing to do here
}

void background::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
