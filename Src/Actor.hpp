#pragma once

#include "Entity.hpp"

class CActor : public CEntity {
public:
	CActor();
	CActor(sf::Texture&, float, float, int, int, std::string);
	~CActor();
	
	void Frame(float& fTime);
	
	void setMap(std::string* szMapCode) { m_pszMapCode = szMapCode; }
	unsigned getLabCnt() {return m_uLabCnt;}
	
private:
	void Input();
	void Collision(float fDx, float fDy);
	
	unsigned m_uLabCnt;

	std::string* m_pszMapCode;
	eStates m_state;
};