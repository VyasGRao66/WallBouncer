#include <SFML/Graphics.hpp>
#include <iostream>
#include "ball.h"
#include "Paddle.h"
#include <sstream>

int main()
{
	sf::VideoMode VM(1280, 720);
	sf::RenderWindow window(VM, "WallBouncer");

	sf::Clock clock;
	ball myball(1280/2, 0);
	Paddle myPaddle(1280 / 2, 710);


    sf::Font font;
    font.loadFromFile("SRC/Fonts/Bangers-Regular.ttf");
    sf::Text currentlives;
    currentlives.setFont(font);
    currentlives.setPosition(5, 0);
    currentlives.setCharacterSize(25);
    currentlives.setFillColor(sf::Color::Green);

    std::stringstream ss;
    int lives = 3;

    ss << "Lives: " << lives;
    currentlives.setString(ss.str());

    std::stringstream bounce;
    int bounceOnPaddle = 0;

    sf::Text score;
    score.setFont(font);
    score.setPosition(5, 25);
    score.setCharacterSize(25);
    score.setFillColor(sf::Color::Green);

    bounce << "Score: " << bounceOnPaddle;
    score.setString(bounce.str());

    sf::Text endText;
    endText.setFont(font);
    endText.setPosition(1280/2, 690/2);
    endText.setCharacterSize(50);
    endText.setFillColor(sf::Color::Green);
    endText.setString("Game Over");


	sf::Time dt;
	sf::Event event;

	float bounceTimer = 0.10f;



	while (window.isOpen()) {
		
		dt = clock.restart();
		bounceTimer -= dt.asSeconds();

		if (myball.getPosition().intersects(myPaddle.getPosition())) {
			
			if (bounceTimer < 0) {
				myball.hitBall();
				bounceTimer = 0.10f;

                bounceOnPaddle++;
                bounce.str("");
                bounce << "Score: " << bounceOnPaddle;
                score.setString(bounce.str());

			}
		
		}


		while (window.pollEvent(event)) {
		
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && myPaddle.getPosition().left >= 0) {

			myPaddle.moveLeft();
		}
		else {
			myPaddle.stopLeft();

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && myPaddle.getPosition().left + myPaddle.getPosition().width  <= 1280) {
		
			myPaddle.moveRight();
		}
		else {
		
			myPaddle.stopRight();
		
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}

        if (myball.getPosition().top < 0 && bounceTimer < 0) {

            myball.bounceTop();
            bounceTimer = 0.10f;
        }

		if (myball.getPosition().left <= 0 || myball.getPosition().left + myball.getPosition().width > 1280) {
            if (bounceTimer < 0) {
                myball.bonceSides();
            
            }
		
		}

        if (myball.getPosition().top + myball.getPosition().height > 720) {

            myball.missBottom();

            lives--;
            ss.str("");
            ss << "Lives: " << lives;
            currentlives.setString(ss.str());

            bounceOnPaddle = 0;
            bounce.str("");
            bounce << "Score: " << bounceOnPaddle;
            score.setString(bounce.str());

            
        }

		window.clear();

		myPaddle.update(dt);
		myball.update(dt);

        if (lives > 0) {
            window.draw(myball.getShape());
            window.draw(myPaddle.getShape());
            window.draw(currentlives);
            window.draw(score);
        }
        
        if (lives <= 0) {
            window.draw(endText);
        }

        

		window.display();
	}

	return 0;
}