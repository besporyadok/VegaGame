#include "Entity.hpp"

using namespace sf;

CEntity::CEntity() {}

CEntity::CEntity(sf::Texture& Texture, float fX, float fY, int nW, int nH, std::string szName) {
	m_Texture = Texture;
	m_Sprite.setTexture(m_Texture);
	
	if(fX == 0.f || fY == 0.f) {
		m_fX = m_fY = 50.f;
	} else {
		m_fX = fX; m_fY = fY;
	}
	
	m_nW = nW; m_nH = nH;
	m_fDx = m_fDy = 0.f;
	
	m_szName = szName;
	
	m_nHealth = 100;
	m_bLife = true;
	
	m_fCurrFrame = 0.f;
	m_fSpeed = 0.f;
	m_fMoveTimer = 0.f;
}