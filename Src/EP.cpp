//! KIRAY begin1
/*++

VegeTable group, FTI grp. 21317

Filename:
	EP.cpp
	
Abstract:
	Define entry point
	
Author:
	KIRAY

--*/

#include <list>
#include <sstream>
#include <SFML\Graphics.hpp>

#include "Actor.hpp"
#include "Enemy.hpp"
#include "Teacher.hpp"

#pragma comment(lib, "sfml-system-d")
#pragma comment(lib, "sfml-window-d")
#pragma comment(lib, "sfml-graphics-d")

using namespace sf;

int main(int argc, char* argv[]) {
	bool bGame = true; // Флаг, если игра окончена (игрок проиграл) - ложь

	VideoMode desk = VideoMode::getDesktopMode();
	RenderWindow wnd(VideoMode(800, 600, desk.bitsPerPixel), "VegaGame", Style::None);
	
	// Создаём шрифты для отображения худа и сообщения о конце игры
	Font fnt;
	fnt.loadFromFile("../Data/main.ttf");
	Text txt("", fnt, 20);
	txt.setColor(Color::Green);
	// Сообщение о конце игры
	Text endGame ("You lost :-(", fnt, 60);
	endGame.setColor(Color::Red);
	
	float fTime = 0.f;
	// Создаём спрайт для карты
	Texture mapTexture;
	mapTexture.loadFromFile("../Data/Level0.png");
	Sprite mapSprite;
	mapSprite.setTexture(mapTexture);
	
	// Создаём объект класса игрока
	Texture actorTexture;
	actorTexture.loadFromFile("../Data/Actor.png");
	CActor actor(actorTexture, 50.f, 50.f, 96, 96);
//! KIRAY end1

	// Создаём объект класса враг
	Image enemyImg;
	enemyImg.loadFromFile("../Data/Voenkom.png");
	enemyImg.createMaskFromColor(Color(255, 255, 255));
	Texture textEnemy;
	textEnemy.loadFromImage(enemyImg);

//! KIRAY begin2	
	unsigned const nKomsCnt = 3; // Кол-во коммисаров для спавна
	std::list<CEntity*> lstKoms; // Список, куда мы их собственно запихаем
	std::list<CEntity*>::iterator itKoms;
	srand(time(NULL)); // Инициализируем генератора псевдослучайных чисел, так, на всякий
	
	for(unsigned i=0; i<nKomsCnt; i++) {
		float fRx = 100 + rand()%700; // Генерим координату X в диапазоне [100;700]
		float fRy = 100 + rand()%400; // Генерим координату Y в диапазоне [100;400]
		// Плодим нужное кол-во коммисаров и заталкиваем в конец списка
		lstKoms.push_back(new CEnemy(textEnemy, fRx, fRy, 96, 96));
	}
//!KIRAY end2
	
	// Создаём объект класса учитель
	sf:: Image image_Teacher;
	image_Teacher.loadFromFile("../Data/Teacher.png");
	image_Teacher.createMaskFromColor(image_Teacher.getPixel(0,0));
	Texture textTeacher;
	textTeacher.loadFromImage(image_Teacher);

	CTeacher Teacher(textTeacher, 100.f, 200.f, 96, 96);

//! KIRAY begin3
	Clock clock;
	Event event;
	while(wnd.isOpen()) {
		if(bGame) {
			fTime = clock.getElapsedTime().asMicroseconds();
			fTime /= 600; // Скорость игры
			clock.restart();
		} else fTime = 0.f;
	
		while(wnd.pollEvent(event)) {
			if(event.type == Event::Closed || 
			  (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) 
				wnd.close();
		}		
		
		// Готовим кадр для рендеринга (обрабатываем управление, просчитываем столкновения и перемещаем спрайт, если необходимо)
		// Передаём в качестве параметра скорость игры
		if(bGame) {
			actor.Frame(fTime);
//! KIRAY end3
			Teacher.Frame(fTime);
//! KIRAY begin4
			for(itKoms = lstKoms.begin(); itKoms != lstKoms.end(); itKoms++) 
				(*itKoms)->Frame(fTime); // Готовим кадр для коммисаров
		}

		// Пока игрок чуть менее, чем полностью жив, то проверяем столкновение 
		// с тов. военкомом
		if(actor.m_bLife == true) {
			for(itKoms = lstKoms.begin(); itKoms != lstKoms.end(); itKoms++) {
				// Встретил военкома - добро пожаловать в вооруженные силы ;-)
				if(actor.getRect().intersects((*itKoms)->getRect())) bGame = false;
			}
				
			if(actor.getRect().intersects(Teacher.getRect()) && actor.uLabCnt >= 3)
				actor.uLabCnt -= 3;
		}
		
		wnd.clear(); // Очищаем окно
		
		// Отрисовываем карту
		for(unsigned i=0; i<MAP_HEIGHT; i++)
			for(unsigned j=0; j<MAP_WIDTH; j++) {
				if(g_szMap[i][j] == '0') mapSprite.setTextureRect(IntRect(32, 0, 32, 32)); // Стена
				if(g_szMap[i][j] == '1') mapSprite.setTextureRect(IntRect(0, 0, 32, 32)); // Пол
				if(g_szMap[i][j] == '2') mapSprite.setTextureRect(IntRect(64, 0, 32, 32)); // Лаба
				if(g_szMap[i][j] == '3') mapSprite.setTextureRect(IntRect(96, 0, 32, 32)); // Жёлтый дом
				
				mapSprite.setPosition(j*32, i*32);
				wnd.draw(mapSprite);
			}
		
		// Отрисовываем худ (здоровье, собранные лабы)
		std::ostringstream strLab;
		strLab << actor.uLabCnt;
		txt.setString("Lab's: " + strLab.str());
		txt.setPosition(650, 500);
		wnd.draw(txt);
		// Выводим, если необходимо, сообщение о проигрыше
		if(!bGame) {
			endGame.setPosition(250.f, 250.f); // for 800x600 res
			wnd.draw(endGame);
		}
		
		// Рисуем объекты
		wnd.draw(actor.getSprite());
//! KIRAY end4
		wnd.draw(Teacher.getSprite());
		
//! KIRAY begin5	
		for(itKoms = lstKoms.begin(); itKoms != lstKoms.end(); itKoms++)
			wnd.draw((*itKoms)->getSprite()); // Отрисовываем твоего любимого военкома

		wnd.display(); // Отображаем отрисованный кадр
	}
	
	return 0;
}
//! KIRAY end5