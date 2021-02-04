// Enemy class

#include "Enemy.hpp"

using namespace sf;

CEnemy::CEnemy() : CEntity() {}

/**
CEnemy::CEnemy(...) - constructor for CEnemy class

Parameters:
	1) Texture - texture for sprite 
	2) fX - spawn coordinate X 
	3) fY - spawn coordinate Y
	4) nW - sprite width
	5) nH - sprite height
	6) -unused-
**/

CEnemy::CEnemy(sf::Texture& Texture, float fX, float fY, int nW, int nH) : 
CEntity(Texture, fX, fY, nW, nH) {
	// «адаем спрайту один пр€моугольник дл€ вывода одного игрока. IntRect Ц дл€ приведени€ типов 
	m_Sprite.setTextureRect(IntRect(0, 0, m_nW, m_nH));

	direction = rand() % (3); // Ќаправление движени€ врага задаЄм случайным образом через генератор случайных чисел 
	m_fSpeed = 0.1f;// ƒаем скорость.этот объект всегда двигаетс€ 
	m_fDx = m_fSpeed;
}

//ф-ци€ проверки столкновений с картой
void  CEnemy::checkCollisionWithMap(float fDx, float fDy) { 
	for(unsigned i = m_fY/32; i < (m_fY+m_nH)/32; i++)
		for(unsigned j = m_fX/32; j < (m_fX+m_nW)/32; j++) {
			if(g_szMap[i][j] == '0') {
				if(fDy > 0) {
					m_fY = i*32 - m_nH;
					m_fDy = 0.f; direction = rand() % (3);
				} else if(fDy < 0) {
					m_fY = i*32 + 32;
					m_fDy = 0.f; direction = rand() % (3);
				} else if(fDx > 0) {
					m_fX = j*32 - m_nW;
					m_fDx = 0.f; direction = rand() % (3); 
				} else if(fDx < 0) {
					m_fX = j*32 + 32;
					m_fDx = 0.f; direction = rand() % (3);
				}
			}
		}
}

void CEnemy::Frame(float& fTime) {
//if (szName == "Army")
//	if (m_bLife) {//провер€ем, жив ли герой 

	// ƒелаютс€ различные действи€ в зависимости от состо€ни€ 
	switch (direction) { 
		case RIGHT: // состо€ние идти вправо 
			m_fDx = m_fSpeed;
			m_fCurrFrame += 0.005f*fTime;
			if (m_fCurrFrame > 2) m_fCurrFrame -= 2;
			m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 192, 96, 96)); 
			break; 
			
		case LEFT:	// —осто€ние идти влево 
			m_fDx = -m_fSpeed;
			m_fCurrFrame += 0.005f*fTime;
			if (m_fCurrFrame > 2) m_fCurrFrame -= 2;
			m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 96, 96, 96));
			break;
				
		case UP:	// »дти вверх 
			m_fDy = -m_fSpeed;
			m_fCurrFrame += 0.005f*fTime;
			if (m_fCurrFrame > 2) m_fCurrFrame -= 2;
			m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 288, 96, 96));
			break;
				
		case DOWN:	// »дти вниз 
			m_fDy = m_fSpeed;
			m_fCurrFrame += 0.005f*fTime;
			if (m_fCurrFrame > 2) m_fCurrFrame -= 2;
			m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 0, 96, 96));
			break;
	} // end switch

	m_fX += m_fDx*fTime; //движение по УXФ
	checkCollisionWithMap(m_fDx, 0);//обрабатываем столкновение по ’ 
	m_fY += m_fDy*fTime; //движение по УYФ 
	checkCollisionWithMap(0, m_fDy);//обрабатываем столкновение по Y 
	m_Sprite.setPosition(m_fX, m_fY); //спрайт в позиции (x, y). 

//	if (m_nHealth <= 0)
//		{ m_bLife = false; }//если жизней меньше 0, либо равно 0, то умираем 
} // update