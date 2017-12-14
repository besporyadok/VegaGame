#include "Actor.hpp"

CActor::CActor() : m_fX(0.f), m_fY(0.f), 
				   m_fH(0.f), m_fW(0.f),
				   m_fDx(0.f), m_fDy(0.f),
				   m_fSpeed(0.f) 
{}

CActor::CActor(std::string szTailset, float fX, float fY, float fH, float fW) {
	m_szTailset = szTailset;
	
	m_fH = fH; m_fW = fW;
	m_fX = fX; m_fY = fY;
	
	m_Texture.loadFromFile("./Data/"+m_szTailset+".png");
	Ractor.setTexture(m_Texture);
	Ractor.setTextureRect(sf::IntRect(0, 0, m_fW, m_fH));
	
	dir = HALT;
	m_fSpeed = 0.f;
}

void CActor::Frame(std::string* pszMap, float& fTime) {
	switch(dir) {
		case LEFT:
			m_fDx = -m_fSpeed;
			m_fDy = 0.f;
			break;
		case RIGHT:
			m_fDx = m_fSpeed;
			m_fDy = 0.f;
			break;
		case UP:
			m_fDy = -m_fSpeed;
			m_fDx = 0.f;
			break;
		case DOWN:
			m_fDy = m_fSpeed;
			m_fDx = 0.f;
			break;
	}
	
	m_fX += m_fDx*fTime;
	m_fY += m_fDy*fTime;
	
	m_fSpeed = 0.f;
	
	Ractor.setPosition(m_fX, m_fY);
	
	Collision(pszMap);
}

void CActor::Collision(std::string* pszMap) {
	for(unsigned i = m_fY/32; i < (m_fY+m_fH)/32; i++)
		for(unsigned j = m_fX/32; j < (m_fX+m_fW)/32; j++) {
			if(pszMap[i][j] == '0') {
				if(m_fDy > 0.f) m_fY = i*32 - m_fH;
				else if(m_fDy < 0.f) m_fY = i*32 + 32;
				else if(m_fDx > 0.f) m_fX = j*32 - m_fW;
				else m_fX = j*32 + 32;
			}
			
			if(pszMap[i][j] == '2') {
				pszMap[i][j] = '1';
			}
		}
}