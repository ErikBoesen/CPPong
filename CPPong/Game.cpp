#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

using namespace std;

int main() {
	int p1X = 100;
	int p2X = 875;
	int p1Y = 150;
	int p2Y = 150;

	int p1Score = 0;
	int p2Score = 0;

	int bX = 500;
	int bY = 250;

	int bSpeedX = -5;
	int bSpeedY = 0;

	sf::RenderWindow window(sf::VideoMode(1000, 500), "Pong");

	sf::RectangleShape centerLine(sf::Vector2f(10, 500));
	centerLine.setFillColor(sf::Color::White);
	centerLine.setPosition(495, 0);

	sf::CircleShape ball(25, 8);
	ball.setFillColor(sf::Color::White);

	sf::RectangleShape paddle1(sf::Vector2f(25, 200));
	paddle1.setFillColor(sf::Color::White);

	sf::RectangleShape paddle2(sf::Vector2f(25, 200));
	paddle2.setFillColor(sf::Color::White);


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (p2Y + 100 > bY && p2Y > 0 && !(abs(p2Y + 100 - bY) < 25)) {
			p2Y -= 3;
		} else if (p2Y + 100 < bY && p2Y < 300 && !(abs(p2Y + 100 - bY) < 25)) {
			p2Y += 3;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && p1Y > 0) {
			p1Y -= 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && p1Y < 300) {
			p1Y += 5;
		}

		if (ball.getGlobalBounds().intersects(paddle1.getGlobalBounds()) && bX > 104) {
			bX = 125;
			bSpeedY = (p1X - bX) / 10 + rand() % 6 - 3;
			bSpeedX = -bSpeedX;
		}
		if (ball.getGlobalBounds().intersects(paddle2.getGlobalBounds()) && bX < 840) {
			bX = 825;
			bSpeedY = (p2X - bX) / 10 + rand() % 6 - 3;
			bSpeedX = -bSpeedX;
		}
		if (bY <= 0 || bY >= 450) { bSpeedY = -bSpeedY; }
		if (bX <= -100) {
			bX = 500;
			bY = 250;
			bSpeedY = 1;
			p2Score++;
		}
		if (bX >= 1100) {
			bX = 500;
			bY = 250;
			p1Score++;
		}

		bX += bSpeedX;
		bY += bSpeedY;

		ball.setPosition(bX, bY);
		paddle1.setPosition(p1X, p1Y);
		paddle2.setPosition(p2X, p2Y);

		window.clear();
		window.draw(centerLine);
		window.draw(ball);
		window.draw(paddle1);
		window.draw(paddle2);
		window.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	return 0;
}