#pragma once

#include <iostream>
#include <fstream>
#include <SFML\Graphics.hpp>

class CMap {
public:
	CMap();
	CMap(const char* szMapName);
	~CMap();
	
	void Render(sf::RenderWindow& wnd);
	
private:
	unsigned m_uMapHeight, m_uMapWidth;

	std::string* m_pszMap;
	std::string m_szTailset;
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
};