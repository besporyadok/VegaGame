/*++

VegeTable group, FTI grp. 21317

Filename:
	Entity.hpp
	
Abstract:
	Definition base class for Actor, Enemy's and other
	
Author:
	KIRAY

--*/

#pragma once

#include <SFML\Graphics.hpp>

class CEntity {
public:
	CEntity();
	CEntity(sf::Texture&, float, float, int, int, std::string);
	
	int getHealth() { return m_nHealth; }
	void setHealth(int const nHealth) { m_nHealth = nHealth; }
	sf::Sprite& getSprite() { return m_Sprite; }
	sf::FloatRect getRect() {
		sf::FloatRect rect(m_fX, m_fY, m_nW, m_nH);
		return rect;
	}
	
	virtual void Frame(float&) = 0;
	
	bool  m_bLife;
	
protected:
	enum eStates {
		LEFT = 0,
		RIGHT,
		UP,
		DOWN,
		STAY
	};
	
	int   m_nW, m_nH, m_nHealth;
	float m_fX, m_fY, m_fDx, m_fDy;
	float m_fSpeed, m_fCurrFrame;
	sf::Sprite  m_Sprite;
	
private:
	float m_fMoveTimer;
	
	std::string m_szName;
	sf::Texture m_Texture;
};