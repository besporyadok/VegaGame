/*++

VegeTable group, FTI grp. 21317

Filename:
	EP.cpp
	
Abstract:
	Define entry point
	
Author:
	KIRAY

--*/

#include <SFML\Graphics.hpp>

#include "Map.hpp"

#pragma comment(lib, "sfml-system-d")
#pragma comment(lib, "sfml-window-d")
#pragma comment(lib, "sfml-graphics-d")

using namespace sf;

int main(int argc, char* argv[]) {
	RenderWindow wnd(VideoMode(640, 480, 32), "VegaGame");
	
	// Map test
	CMap map("./Data/Level0");
	CActor actor("Actor0", 250.f, 250.f, 96.f, 96.f);

	float fCurrFrame = 0.f;
	Event event;
	Clock clock;
	while(wnd.isOpen()) {
		float fTime = clock.getElapsedTime().asMicroseconds();
		fTime /= 400;
		clock.restart();
	
		while(wnd.pollEvent(event)) {
			if(event.type == Event::Closed) wnd.close();
		}
		
		map.Frame(actor, fTime, fCurrFrame);
		actor.Frame(map.getMapCode(), fTime);
		
		wnd.clear();
		map.Render(wnd);
		wnd.draw(actor.Ractor);
		wnd.display();
	}
	
	return 0;
}