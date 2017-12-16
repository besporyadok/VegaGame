#pragma once

#include "Entity.hpp"

class CActor : public CEntity {
public:
	CActor();
	CActor(sf::Texture&, float, float, int, int, std::string);
	
	void Frame(float& fTime);
	
	void setMap(std::string* szMapCode) { m_pszMapCode = szMapCode; }
	sf::Sprite& getSprite() {return m_Sprite;}
	
private:
	void Input();
	void Collision(float fDx, float fDy);

	std::string* m_pszMapCode;
};