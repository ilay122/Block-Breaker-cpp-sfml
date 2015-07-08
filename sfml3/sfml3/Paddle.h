#pragma once
#include <SFML/Graphics.hpp>
const float PdSpeed = 10.f;
const sf::Vector2f startposs(300, 550);
class Paddle
{
public:
	sf::RectangleShape shape;
	Paddle();
	~Paddle();
	void update(sf::Keyboard&);
	void draw(sf::RenderWindow&);
	void reset();

private:

protected:
	
};

