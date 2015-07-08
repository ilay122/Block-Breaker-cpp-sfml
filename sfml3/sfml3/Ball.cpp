#include "Ball.h"


Ball::Ball()
{
	//this->pos = startpos;
	(*this).pos = startpos;

	shape.setPosition((*this).pos);
	shape.setRadius(Radius);
	shape.setFillColor(sf::Color::Red);
	vel.x = BlSpeed;
	vel.y = BlSpeed;
}


Ball::~Ball()
{
}

bool Ball::update(std::vector<sf::RectangleShape>& bricks, Paddle& paddle){
	bool lost = false;
	pos.x += vel.x;
	pos.y += vel.y;

	if (pos.y <= 0){
		pos.y = 0;
		vel.y *= -1;
	}
	if (pos.y + shape.getRadius() * 2 >= 600){
		pos.y = 600 - shape.getRadius() * 2;
		vel.y *= -1;
		lost = true;
	}
	if (pos.x <= 0){
		pos.x = 0;
		vel.x *= -1;
	}
	if (pos.x + shape.getRadius() * 2 >= 800){
		pos.x = 800 - shape.getRadius() * 2;
		vel.x *= -1;
	}
	if (shape.getGlobalBounds().intersects(paddle.shape.getGlobalBounds())){
		pos.y = paddle.shape.getPosition().y - shape.getRadius() * 2 - 1;
		vel.y *= -1;
		if (pos.x + shape.getRadius() >paddle.shape.getPosition().x + paddle.shape.getGlobalBounds().width / 2 ){
			vel.x = BlSpeed;
		}
		else{
			vel.x = -BlSpeed;
		}
		srand(std::time(nullptr));
		shape.setFillColor(sf::Color(rand(), rand(), rand()));

		paddle.shape.setFillColor(sf::Color(rand(), rand(), rand()));
	}
	shape.setPosition(pos);
	
	for (int i = 0; i < bricks.size(); i++){
		if (shape.getGlobalBounds().intersects(bricks[i].getGlobalBounds())){
			
			float overlapLeft = pos.x + shape.getRadius() * 2 - bricks[i].getPosition().x;
			float overlapRight= bricks[i].getPosition().x+bricks[i].getSize().x - pos.x ;
			float overlapTop{ pos.y + shape.getRadius() * 2 - bricks[i].getPosition().y};
			float overlapBottom{ bricks[i].getPosition().y + bricks[i].getSize().y - pos.y };
			

			bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
			bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

			float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
			float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

			if (abs(minOverlapX) < abs(minOverlapY))
				vel.x = ballFromLeft ? -BlSpeed : BlSpeed;
			else
				vel.y = ballFromTop ? -BlSpeed : BlSpeed;


			bricks.erase(bricks.begin() + i);
			
		}
	}

	shape.setPosition(pos);
	return lost;
}
void Ball::draw(sf::RenderWindow& win){
	win.draw(shape);
}
void Ball::reset(){
	pos = startpos;
	shape.setPosition(pos);
	vel.x = BlSpeed;
	vel.y = BlSpeed;
}