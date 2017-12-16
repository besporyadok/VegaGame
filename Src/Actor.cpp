#include "Actor.hpp"

// -[ERR]: If unset map
// -[BUG]: Animation stop if key unpressed
// +[ERR]: Spawn actor in wall
// -[BUG]: Two key pressed (stop move)
// -[BUG]: Lab not store

using namespace sf;

CActor::CActor() : CEntity() {}

CActor::CActor(sf::Texture& Texture, float fX, float fY, int nW, int nH, std::string szName) :
CEntity(Texture, fX, fY, nW, nH, szName) {
	eState = STAY;
	m_Sprite.setTextureRect(IntRect(0, 0, m_nW, m_nH));
}

void CActor::Frame(float& fTime) {
//	if(m_bLife) {
		Input();
		
		switch(eState) {
			case LEFT:
				m_fDx = -m_fSpeed;
				m_fCurrFrame += 0.005*fTime;
				if(m_fCurrFrame > 3) m_fCurrFrame -= 3;
				m_Sprite.setTextureRect(IntRect(96*static_cast<int>(m_fCurrFrame), 96, 96, 96));
				break;
				
			case RIGHT:
				m_fDx = m_fSpeed;
				m_fCurrFrame += 0.005*fTime;
				if(m_fCurrFrame > 3) m_fCurrFrame -= 3;
				m_Sprite.setTextureRect(IntRect(96*static_cast<int>(m_fCurrFrame), 192, 96, 96));
				break;
				
			case UP:
				m_fDy = -m_fSpeed;
				m_fCurrFrame += 0.005*fTime;
				if(m_fCurrFrame > 3) m_fCurrFrame -= 3;
				m_Sprite.setTextureRect(IntRect(96*static_cast<int>(m_fCurrFrame), 288, 96, 96));
				break;
				
			case DOWN:
				m_fDy = m_fSpeed;
				m_fCurrFrame += 0.005*fTime;
				if(m_fCurrFrame > 3) m_fCurrFrame -= 3;
				m_Sprite.setTextureRect(IntRect(96*static_cast<int>(m_fCurrFrame), 0, 96, 96));
				break;
				
			case STAY:
				m_fDx = m_fSpeed;
				m_fDy = m_fSpeed;
				break;
		}
		
		m_fX += m_fDx*fTime;
		Collision(m_fDx, 0.f);
		m_fY += m_fDy*fTime;
		Collision(0.f, m_fDy);
		
		m_fSpeed = 0.f;
		m_Sprite.setPosition(m_fX, m_fY);
		
//		if(m_nHealth <= 0) m_bLife = false;
//	}
}

void CActor::Collision(float fDx, float fDy) {
	for(unsigned i = m_fY/32; i < (m_fY+m_nH)/32; i++)
		for(unsigned j = m_fX/32; j < (m_fX+m_nW)/32; j++) {
			if(m_pszMapCode[i][j] == '0') {
				if(fDy > 0) {
					m_fY = i*32 - m_nH;
					m_fDy = 0.f;
				} else if(fDy < 0) {
					m_fY = i*32 + 32;
					m_fDy = 0.f;
				} else if(fDx > 0) {
					m_fX = j*32 - m_nW;
					m_fDx = 0.f;
				} else if(fDx < 0) {
					m_fX = j*32 + 32;
					m_fDx = 0.f;
				}
			}
			
			if(m_pszMapCode[i][j] == '2') {
				m_pszMapCode[i][j] == '1';
			}
		}
}

void CActor::Input() {
	if(Keyboard::isKeyPressed(Keyboard::Left)) {
		eState = LEFT;
		m_fSpeed = 0.1f;
	}
	if(Keyboard::isKeyPressed(Keyboard::Right)) {
		eState = RIGHT;
		m_fSpeed = 0.1f;
	}
	if(Keyboard::isKeyPressed(Keyboard::Up)) {
		eState = UP;
		m_fSpeed = 0.1f;
	}
	if(Keyboard::isKeyPressed(Keyboard::Down)) {
		eState = DOWN;
		m_fSpeed = 0.1f;
	}
}