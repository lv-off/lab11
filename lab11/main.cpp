#include<iostream>
#include <cstdlib>
#include"engine.h"
#include<Windows.h>

using namespace engine;

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(1280, 720), "PingPong");  
    ScoreBoard scoreboard;
    Ball ball(&window);
    Player player1,player2;
    player1.setSide("left", &window);
    player2.setSide("right", &window);
    Clock clock;
    float timer = 0, delay = 0.02, time;
    bool pause = true;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) player2.move(&window,-1);
                else if (event.key.code == Keyboard::Down) player2.move(&window, 1);

                if (event.key.code == Keyboard::W) player1.move(&window, -1);
                else if (event.key.code == Keyboard::S) player1.move(&window, 1);
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == Keyboard::Space) {
                    pause = !pause;
                }
                if (event.key.code == Keyboard::R) {
                    ball.reset(&window);
                    scoreboard.reset();
                    pause = true;
                }
                if (event.key.code == Keyboard::Num1) {
                    ball.speed = 5.f;
                }
                if (event.key.code == Keyboard::Num2) {
                    ball.speed = 10.f;
                }
                if (event.key.code == Keyboard::Num3) {
                    ball.speed = 15.f;
                }
            }

        }
        if (ball.side == "left") { ball.reset(&window); ball.side = "none"; scoreboard.rightWon(); }
        if (ball.side == "right") { ball.reset(&window); ball.side = "none"; scoreboard.leftWon(); }
        if (!pause) {
            time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;
            if (timer > delay)
            {
                ball.checkPlayer(&player1, &player2);
                ball.checkWall(&window);
                ball.move();
                timer = 0;
            }
        }
        window.clear();
        scoreboard.draw(&window);
        ball.draw(&window);
        player1.draw(&window);
        player2.draw(&window);
        window.display();
    }
	return 0;
}