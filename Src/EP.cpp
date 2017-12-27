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

#pragma comment(lib, "sfml-system-d")
#pragma comment(lib, "sfml-window-d")
#pragma comment(lib, "sfml-graphics-d")

using namespace sf;

#define MAP_HEIGHT 15
#define MAP_WIDTH 20
std::string szMap[MAP_HEIGHT] = {
	"00000000000000000000",
	"01111111110011111100",
	"01111111112011111100",
	"01111111111011111100",
	"01111111111011111100",
	"01111111111111111110",
	"01111111111111111110",
	"01111111111111111110",
	"01111111000000011110",
	"01111111111111111110",
	"01221111111111111110",
	"01111111111111111110",
	"01111111111111111110",
	"01111111111111111110",
	"00000000000000000000",
};

int main(int argc, char* argv[]) {
	RenderWindow wnd(VideoMode(640, 480, 32), "VegaGame");
	
	// Font test
	Font fnt;
	fnt.loadFromFile("../Data/main.ttf");
	Text txt("", fnt, 20);
	txt.setColor(Color::Green);
	
	float fTime = 0.f;
	// Map tmp
	Texture mapTexture;
	mapTexture.loadFromFile("../Data/Level0.png");
	Sprite mapSprite;
	mapSprite.setTexture(mapTexture);
	
	// Actor test
	Texture actorTexture;
	actorTexture.loadFromFile("../Data/Actor0.png");
	CActor actor(actorTexture, 50.f, 50.f, 96, 96, "Actor");
	actor.setMap(szMap);

	// Enemy Test
	Texture textEnemy;
	textEnemy.loadFromFile("../Data/enemy.png");
	CEnemy Army1(textEnemy, 100.f, 200.f, 96, 96, "Army");//объект класса врага
	Army1.setMap(szMap);
	
	Clock clock;
	Event event;
	while(wnd.isOpen()) {
		fTime = clock.getElapsedTime().asMicroseconds();
		fTime /= 600;
		clock.restart();
	
		while(wnd.pollEvent(event)) {
			if(event.type == Event::Closed) wnd.close();
		}

		
		
		actor.Frame(fTime);
		Army1.Frame(fTime);

		wnd.clear();
		
		// Map tmp
		for(unsigned i=0; i<MAP_HEIGHT; i++)
			for(unsigned j=0; j<MAP_WIDTH; j++) {
				if(szMap[i][j] == '0') mapSprite.setTextureRect(IntRect(32, 0, 32, 32));
				if(szMap[i][j] == '1') mapSprite.setTextureRect(IntRect(0, 0, 32, 32));
				if(szMap[i][j] == '2') mapSprite.setTextureRect(IntRect(64, 0, 32, 32));
				if(szMap[i][j] == '3') mapSprite.setTextureRect(IntRect(96, 0, 32, 32));
				
				mapSprite.setPosition(j*32, i*32);
				wnd.draw(mapSprite);
			}
		
		std::ostringstream strStream;
		strStream << actor.getLabCnt();
		txt.setString("Lab's: " + strStream.str());
		txt.setPosition(500, 400);
		wnd.draw(txt);
		
		wnd.draw(actor.getSprite());
		wnd.draw(Army1.getSprite());
		
		wnd.display();
	}
	
	return 0;
}