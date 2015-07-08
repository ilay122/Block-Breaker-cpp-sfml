#include "Paddle.h"


Paddle::Paddle()
{
	shape.setPosition(startposs);
	shape.setFillColor(sf::Color::White);
	shape.setSize(sf::Vector2f(120,10));
}


Paddle::~Paddle()
{
}
void Paddle::update(sf::Keyboard& keyb){
	if (keyb.isKeyPressed(keyb.Right)){
		shape.move(PdSpeed, 0);
	}
	if (keyb.isKeyPressed(keyb.Left)){
		shape.move(-PdSpeed, 0);
	}
	if (shape.getPosition().x < 0){
		shape.setPosition(0, shape.getPosition().y);
	}
	if (shape.getPosition().x > 800 - shape.getGlobalBounds().width){
		shape.setPosition(800 - shape.getGlobalBounds().width, shape.getPosition().y);
	}
}
void Paddle::draw(sf::RenderWindow& win){
	win.draw(shape);
}
void Paddle::reset(){
	shape.setPosition(startposs);
	shape.setFillColor(sf::Color::White);
}