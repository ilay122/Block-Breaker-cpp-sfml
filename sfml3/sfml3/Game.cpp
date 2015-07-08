#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "vector"
#include <iostream>
class Game{
public:

	void drawBricks(std::vector<sf::RectangleShape>& bricks, sf::RenderWindow& window){
		for (int i = 0; i < bricks.size(); i++){
			window.draw(bricks[i]);
		}
	}
	void reset(std::vector<sf::RectangleShape>& bricks, sf::RectangleShape rect){
		bricks.clear();
		for (int i = 0; i < 5; i++){
			for (int j = 0; j < 14; j++){
				sf::Color color(rand(), rand(), rand());
				rect.setFillColor(color);
				rect.setPosition(j * (rect.getGlobalBounds().width + 4) + 25, i*(rect.getGlobalBounds().height + 3));
				bricks.push_back(rect);
			}
		}
	}
	int run()
	{

		sf::RenderWindow window(sf::VideoMode(800, 600), "Block Breaker");
		window.setFramerateLimit(60);

		int state = 0;//0 -> playing \ 1->lost \2->won \ 3-> pause
		bool ppresed = false;
		bool spacepressed = false;
		bool lost = false;

		Paddle* player = new Paddle();
		Ball* ball = new Ball();

		std::vector<sf::RectangleShape> bricks;
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(50, 20));

		reset(bricks, rect);
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			bool currentppressed = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
			if (currentppressed && !ppresed && state != 1 && state != 2){
				if (state == 0)
					state = 3;
				else
					state = 0;
			}
			ppresed = currentppressed;

			if (state == 0){
				player->update(sf::Keyboard());
				lost = ball->update(bricks, (*player));
			}

			if (lost)
				state = 1;
			else if (bricks.empty())
				state = 2;

			bool spaceclicked = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
			if (state != 0 && state != 3){
				if (spaceclicked && !spacepressed){
					reset(bricks, rect);
					ball->reset();
					player->reset();
					state = 0;
				}
			}
			spacepressed = spaceclicked;

			window.clear();
			player->draw(window);
			ball->draw(window);
			drawBricks(bricks, window);
			window.display();
		}

		return 0;
	}

};