//! KIRAY begin1
/*++

VegeTable group, FTI grp. <extr>

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
	bool bGame = true; // ����, ���� ���� �������� (����� ��������) - ����

	VideoMode desk = VideoMode::getDesktopMode();
	RenderWindow wnd(VideoMode(800, 600, desk.bitsPerPixel), "VegaGame", Style::None);
	
	// ������ ������ ��� ����������� ���� � ��������� � ����� ����
	Font fnt;
	fnt.loadFromFile("../Data/main.ttf");
	Text txt("", fnt, 20);
	txt.setColor(Color::Green);
	// ��������� � ����� ����
	Text endGame ("You lost :-(", fnt, 60);
	endGame.setColor(Color::Red);
	
	float fTime = 0.f;
	// ������ ������ ��� �����
	Texture mapTexture;
	mapTexture.loadFromFile("../Data/Level0.png");
	Sprite mapSprite;
	mapSprite.setTexture(mapTexture);
	
	// ������ ������ ������ ������
	Texture actorTexture;
	actorTexture.loadFromFile("../Data/Actor.png");
	CActor actor(actorTexture, 50.f, 50.f, 96, 96);
//! KIRAY end1

	// ������ ������ ������ ����
	Image enemyImg;
	enemyImg.loadFromFile("../Data/Voenkom.png");
	enemyImg.createMaskFromColor(Color(255, 255, 255));
	Texture textEnemy;
	textEnemy.loadFromImage(enemyImg);

//! KIRAY begin2	
	unsigned const nKomsCnt = 3; // ���-�� ���������� ��� ������
	std::list<CEntity*> lstKoms; // ������, ���� �� �� ���������� ��������
	std::list<CEntity*>::iterator itKoms;
	srand(time(NULL)); // �������������� ���������� ��������������� �����, ���, �� ������
	
	for(unsigned i=0; i<nKomsCnt; i++) {
		float fRx = 100 + rand()%700; // ������� ���������� X � ��������� [100;700]
		float fRy = 100 + rand()%400; // ������� ���������� Y � ��������� [100;400]
		// ������ ������ ���-�� ���������� � ����������� � ����� ������
		lstKoms.push_back(new CEnemy(textEnemy, fRx, fRy, 96, 96));
	}
//!KIRAY end2
	
	// ������ ������ ������ �������
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
			fTime /= 600; // �������� ����
			clock.restart();
		} else fTime = 0.f;
	
		while(wnd.pollEvent(event)) {
			if(event.type == Event::Closed || 
			  (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) 
				wnd.close();
		}		
		
		// ������� ���� ��� ���������� (������������ ����������, ������������ ������������ � ���������� ������, ���� ����������)
		// ������� � �������� ��������� �������� ����
		if(bGame) {
			actor.Frame(fTime);
//! KIRAY end3
			Teacher.Frame(fTime);
//! KIRAY begin4
			for(itKoms = lstKoms.begin(); itKoms != lstKoms.end(); itKoms++) 
				(*itKoms)->Frame(fTime); // ������� ���� ��� ����������
		}

		// ���� ����� ���� �����, ��� ��������� ���, �� ��������� ������������ 
		// � ���. ���������
		if(actor.m_bLife == true) {
			for(itKoms = lstKoms.begin(); itKoms != lstKoms.end(); itKoms++) {
				// �������� �������� - ����� ���������� � ����������� ���� ;-)
				if(actor.getRect().intersects((*itKoms)->getRect())) bGame = false;
			}
				
			if(actor.getRect().intersects(Teacher.getRect()) && actor.uLabCnt >= 3)
				actor.uLabCnt -= 3;
		}
		
		wnd.clear(); // ������� ����
		
		// ������������ �����
		for(unsigned i=0; i<MAP_HEIGHT; i++)
			for(unsigned j=0; j<MAP_WIDTH; j++) {
				if(g_szMap[i][j] == '0') mapSprite.setTextureRect(IntRect(32, 0, 32, 32)); // �����
				if(g_szMap[i][j] == '1') mapSprite.setTextureRect(IntRect(0, 0, 32, 32)); // ���
				if(g_szMap[i][j] == '2') mapSprite.setTextureRect(IntRect(64, 0, 32, 32)); // ����
				if(g_szMap[i][j] == '3') mapSprite.setTextureRect(IntRect(96, 0, 32, 32)); // Ƹ���� ���
				
				mapSprite.setPosition(j*32, i*32);
				wnd.draw(mapSprite);
			}
		
		// ������������ ��� (��������, ��������� ����)
		std::ostringstream strLab;
		strLab << actor.uLabCnt;
		txt.setString("Lab's: " + strLab.str());
		txt.setPosition(650, 500);
		wnd.draw(txt);
		// �������, ���� ����������, ��������� � ���������
		if(!bGame) {
			endGame.setPosition(250.f, 250.f); // for 800x600 res
			wnd.draw(endGame);
		}
		
		// ������ �������
		wnd.draw(actor.getSprite());
//! KIRAY end4
		wnd.draw(Teacher.getSprite());
		
//! KIRAY begin5	
		for(itKoms = lstKoms.begin(); itKoms != lstKoms.end(); itKoms++)
			wnd.draw((*itKoms)->getSprite()); // ������������ ������ �������� ��������

		wnd.display(); // ���������� ������������ ����
	}
	
	return 0;
}
//! KIRAY end5