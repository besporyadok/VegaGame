#pragma once

#include <SFML\Graphics.hpp>

class CEntity {
public:
	CEntity();
	CEntity(sf::Texture&, float, float, int, int, std::string);
	
protected:
	enum {
		LEFT = 0,
		RIGHT,
		UP,
		DOWN,
		STAY = -1
	} eState;

	virtual void Frame(float&) = 0;
	
	bool  m_bLife;
	int   m_nW, m_nH, m_nHealth;
	float m_fX, m_fY, m_fDx, m_fDy;
	float m_fSpeed, m_fCurrFrame;
	sf::Sprite  m_Sprite;
	
private:
	float m_fMoveTimer;
	
	std::string m_szName;

	sf::Texture m_Texture;
};