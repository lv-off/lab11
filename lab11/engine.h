#pragma once
#include<iostream>
#include<sstream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

namespace engine {

	class Player {
	public:
		Player();
		void draw(RenderWindow* window);
		void setSide(string a, RenderWindow* window);
		void move(RenderWindow* window, int dy);
		Vector2f getPosition() {return player.getPosition();}
		Vector2f  getSize() { return player.getSize(); }
		float speed = 25.f;
	private:
		RectangleShape player;
	};

	class ScoreBoard {
	public:
		ScoreBoard();
		void reset();
		void rightWon();
		void leftWon();
		void draw(RenderWindow* window);
	private:
		Font font;
		Text text;
		int rightScore = 0;
		int leftScore = 0;
		stringstream ss;
		string score;
	};

	class Ball {
	public:
		Ball(RenderWindow* window);
		void draw(RenderWindow* window);
		void move();
		void checkWall(RenderWindow* window);
		void reset(RenderWindow* window);
		void checkPlayer(Player* leftPlayer, Player* rightPlayer);
		float speed = 5.f;
		string side = "none";
		int dx = 1, dy = 1;
	private:
		RectangleShape ball;
	};

}
