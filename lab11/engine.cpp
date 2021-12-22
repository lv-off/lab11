#include "engine.h"

namespace engine {

	ScoreBoard::ScoreBoard()
	{
		font.loadFromFile("font.ttf");
		text.setFont(font);
		text.setCharacterSize(101);
		ss << leftScore << ":" << rightScore;
		ss >> score;
		text.setString(score);

	}

	void ScoreBoard::rightWon()
	{
		rightScore++;
		ss.clear();
		ss << leftScore << ":" << rightScore;
		ss >> score;
		text.setString(score);
	}

	void ScoreBoard::leftWon()
	{
		leftScore++;
		ss.clear();
		ss << leftScore << ":" << rightScore;
		ss >> score;
		text.setString(score);
	}

	void ScoreBoard::draw(RenderWindow* window)
	{
		text.setPosition(window->getSize().x / 2 - text.getCharacterSize() / 1.35, 0);
		window->draw(text);
	}

	void ScoreBoard::reset()
	{
		leftScore = rightScore = 0;
		ss.clear();
		ss << leftScore << ":" << rightScore;
		ss >> score;
		text.setString(score);
	}

	Ball::Ball(RenderWindow* window)
	{
		ball.setSize(Vector2f(40.f, 40.f));
		ball.setPosition(window->getSize().x / 2 - ball.getSize().x, window->getSize().y / 2 - ball.getSize().y);
	}

	void Ball::draw(RenderWindow* window)
	{
		window->draw(ball);
	}

	void Ball::move()
	{
		ball.move(dx * speed, dy * speed);
	}

	void Ball::checkWall(RenderWindow* window)
	{
		if (ball.getPosition().x < 0) { side = "left";}
		if (ball.getPosition().x > window->getSize().x - ball.getSize().x) { side = "right"; }
		if (ball.getPosition().y < 0) {dy *= -1; ball.setPosition(ball.getPosition().x, 0);}
		if (ball.getPosition().y > window->getSize().y - ball.getSize().y) { dy *= -1; ball.setPosition(ball.getPosition().x, window->getSize().y - ball.getSize().y);}
	}

	void Ball::reset(RenderWindow* window)
	{
		ball.setPosition(window->getSize().x / 2 - ball.getSize().x, window->getSize().y / 2 - ball.getSize().y);
		dx *= -1;
		dy *= -1;
	}

	void Ball::checkPlayer(Player* leftPlayer, Player* rightPlayer)
	{
		if (ball.getPosition().y >= leftPlayer->getPosition().y - ball.getSize().y && ball.getPosition().x <= leftPlayer->getSize().x &&
			ball.getPosition().y <= leftPlayer->getPosition().y + leftPlayer->getSize().y + ball.getSize().y) {
			dx *= -1; ball.setPosition(Vector2f(leftPlayer->getSize().x, ball.getPosition().y));
		}

			if (ball.getPosition().y >= rightPlayer->getPosition().y - ball.getSize().y && ball.getPosition().x >= rightPlayer->getPosition().x-2*rightPlayer->getSize().x &&
				ball.getPosition().y <= rightPlayer->getPosition().y + rightPlayer->getSize().y + ball.getSize().y) {
				dx *= -1; ball.setPosition(Vector2f(rightPlayer->getPosition().x-2*rightPlayer->getSize().x, ball.getPosition().y));
		}
	}

	Player::Player() {
		player.setSize(Vector2f(20.f, 120.f));
	}

	void Player::setSide(string a, RenderWindow* window)
	{
		if (a == "left") player.setPosition(Vector2f(0, window->getSize().y / 2 - player.getSize().y / 2));
		if (a == "right") player.setPosition(Vector2f(window->getSize().x - player.getSize().x, window->getSize().y / 2 - player.getSize().y / 2));
	}

	void Player::draw(RenderWindow* window)
	{
		window->draw(player);
	}

	void Player::move(RenderWindow* window,int dy)
	{
		player.move(0, speed * dy);
		if (player.getPosition().y <= 0) player.setPosition(Vector2f(player.getPosition().x, 0));
		if(player.getPosition().y + player.getSize().y >= window->getSize().y) player.setPosition(Vector2f(player.getPosition().x, window->getSize().y - player.getSize().y));
	}

}
