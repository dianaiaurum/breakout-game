#include "brick.h"

<<<<<<< Updated upstream
sf::Texture brick::texture;

=======
>>>>>>> Stashed changes
brick::brick(float x, float y){
	texture.loadFromFile("brick01.png");
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
<<<<<<< Updated upstream
	sprite.setOrigin(get_centre());
=======
>>>>>>> Stashed changes
}

void brick::update(){
}

void brick::draw(sf::RenderWindow& window){
	window.draw(sprite);
}
