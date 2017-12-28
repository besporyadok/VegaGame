/*++

VegeTable group, FTI grp. 21317

Filename:
	EP.cpp
	
Abstract:
	Define entry point
	
Author:
	KIRAY

--*/

#include <sstream>
#include <SFML\Graphics.hpp>

#include "Actor.hpp"
#include "Enemy.hpp"
#include "Teacher.h"

#pragma comment(lib, "sfml-system-d")
#pragma comment(lib, "sfml-window-d")
#pragma comment(lib, "sfml-graphics-d")

using namespace sf;

int main(int argc, char* argv[]) {
	VideoMode desk = VideoMode::getDesktopMode();
	RenderWindow wnd(VideoMode(640, 480, desk.bitsPerPixel), "VegaGame");
	
	// Создаём шрифты для отображения худа
	Font fnt;
	fnt.loadFromFile("../Data/main.ttf");
	Text txt("", fnt, 20);
	txt.setColor(Color::Green);
	
	float fTime = 0.f;
	// Создаём спрайт для карты
	Texture mapTexture;
	mapTexture.loadFromFile("../Data/Level0.png");
	Sprite mapSprite;
	mapSprite.setTexture(mapTexture);
	
	// Создаём объект класса игрока
	Texture actorTexture;
	actorTexture.loadFromFile("../Data/Actor0.png");
	CActor actor(actorTexture, 50.f, 50.f, 96, 96, "Actor");

	// Создаём объект класса враг
	Image enemyImg;
	enemyImg.loadFromFile("../Data/enemy.png");
	enemyImg.createMaskFromColor(Color(255, 255, 255));
	Texture textEnemy;
	textEnemy.loadFromImage(enemyImg);
	
	CEnemy Army1(textEnemy, 100.f, 200.f, 96, 96, "Army");

	// Создаём объект класса учитель
	sf:: Image image_Teacher;
	image_Teacher.loadFromFile("../Data/Teacher.png");
	image_Teacher.createMaskFromColor(image_Teacher.getPixel(0,0));
	Texture textTeacher;
	textTeacher.loadFromImage(image_Teacher);

	CTeacher Teacher(textTeacher, 100.f, 200.f, 96, 96, "Teacher");

	Clock clock;
	Event event;
	while(wnd.isOpen()) {
		fTime = clock.getElapsedTime().asMicroseconds();
		fTime /= 600; // Скорость игры
		clock.restart();
	
		while(wnd.pollEvent(event)) {
			if(event.type == Event::Closed) wnd.close();
		}		
		
		// Готовим кадр для рендеринга (обрабатываем управление, просчитываем столкновения и перемещаем спрайт, если необходимо)
		// Передаём скорость игры
		actor.Frame(fTime);
		Army1.Frame(fTime);
		Teacher.Frame(fTime);

		/* if(actor.m_bLife == true) {
			if(actor.getRect() == Army1.getRect())
				actor.setHealth(0);
		} */

		wnd.clear();
		
		// Отрисовываем карту
		for(unsigned i=0; i<MAP_HEIGHT; i++)
			for(unsigned j=0; j<MAP_WIDTH; j++) {
				if(g_szMap[i][j] == '0') mapSprite.setTextureRect(IntRect(32, 0, 32, 32));
				if(g_szMap[i][j] == '1') mapSprite.setTextureRect(IntRect(0, 0, 32, 32));
				if(g_szMap[i][j] == '2') mapSprite.setTextureRect(IntRect(64, 0, 32, 32));
				if(g_szMap[i][j] == '3') mapSprite.setTextureRect(IntRect(96, 0, 32, 32));
				
				mapSprite.setPosition(j*32, i*32);
				wnd.draw(mapSprite);
			}
		
		// Отрисовываем худ (здоровье, собранные лабы)
		std::ostringstream strLab, strHealth;
		strLab << actor.getLabCnt(); strHealth << actor.getHealth();
		txt.setString("Lab's: " + strLab.str() + "\nHealth: " + strHealth.str());
		txt.setPosition(500, 400);
		wnd.draw(txt);
		
		// Рисуем объекты
		wnd.draw(actor.getSprite());
		wnd.draw(Army1.getSprite());
		wnd.draw(Teacher.getSprite());
		
		wnd.display();
	}
	
	return 0;
}