#pragma once

#include <SFML\Graphics.hpp>

class CActor {
public:
	CActor();
	CActor(std::string, float, float, float, float);
	
	void Frame(std::string* pszMap, float& fTime);
	
	float m_fSpeed;
	
	enum eStay {
		LEFT = 0,
		RIGHT,
		UP,
		DOWN,
		HALT = -1,
	};
	eStay dir;
	
	sf::Sprite Ractor;
private:
	void Collision(std::string* pszMap);

	float m_fX, m_fY, m_fDx, m_fDy, m_fH, m_fW;
	
	std::string m_szTailset;
	sf::Texture m_Texture;
};