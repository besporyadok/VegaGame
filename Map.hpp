#pragma once

#include <iostream>
#include <fstream>
#include <SFML\Graphics.hpp>

#include "Actor.hpp"

class CMap {
public:
	CMap();
	CMap(const char* szMapName);
	~CMap();
	
	void Render(sf::RenderWindow& wnd);
	void Frame(CActor& actor, float& fTime, float& fCurrFrame);
	
	std::string* getMapCode () {return m_pszMap;}
	
private:
	unsigned m_uMapHeight, m_uMapWidth;

	std::string* m_pszMap;
	std::string m_szTailset;
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
};