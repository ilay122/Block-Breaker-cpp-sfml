#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include <iostream>
#include <ctime>

const int Radius = 10;
const float BlSpeed = 7.f;
const sf::Vector2f startpos(300,310);
class Ball
{
public:
	sf::CircleShape shape;
	sf::Vector2f vel;
	sf::Vector2f pos;
	Ball();
	~Ball();
	bool update(std::vector<sf::RectangleShape>& bricks,Paddle& paddle);
	void draw(sf::RenderWindow&);
	void reset();
};

