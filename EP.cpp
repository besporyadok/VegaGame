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

	Event event;
	while(wnd.isOpen()) {
		while(wnd.pollEvent(event)) {
			if(event.type == Event::Closed) wnd.close();
		}
		
		wnd.clear();
		map.Render(wnd);
		wnd.display();
	}
	
	return 0;
}