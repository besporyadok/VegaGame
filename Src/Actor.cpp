/*++

VegeTable group, FTI grp. 21317

Filename:
	Actor.cpp
	
Abstract:
	Implementation CActor class (player)
	
Author:
	KIRAY

--*/

#include "Actor.hpp"

// -[ERR]: If unset map

using namespace sf;

CActor::CActor() : CEntity() {}

CActor::CActor(sf::Texture& Texture, float fX, float fY, int nW, int nH, std::string szName) :
CEntity(Texture, fX, fY, nW, nH, szName) {
	m_state = STAY;
	m_Sprite.setTextureRect(IntRect(0, 0, m_nW, m_nH));
	
	m_uLabCnt = 0;
}

//Подготовка кадра к рендерингу (обработка нажатий клавиши, просчёт столкновений, перемещение спрайта)
void CActor::Frame(float& fTime) {
//	if(m_bLife) {
		Input(); // Обработка нажатий клавиши
		
		switch(m_state) {
			// Игрок пожелал пойти налево
			case LEFT:
				m_fDx = -m_fSpeed;
				m_fCurrFrame += 0.005*fTime;
				if(m_fCurrFrame > 3) m_fCurrFrame -= 3;
				m_Sprite.setTextureRect(IntRect(96*static_cast<int>(m_fCurrFrame), 96, 96, 96));
				break;
				
			// Игрок пожелал пойти направо
			case RIGHT:
				m_fDx = m_fSpeed;
				m_fCurrFrame += 0.005*fTime;
				if(m_fCurrFrame > 3) m_fCurrFrame -= 3;
				m_Sprite.setTextureRect(IntRect(96*static_cast<int>(m_fCurrFrame), 192, 96, 96));
				break;
			
			// Игрок пожелал пойти вверх
			case UP:
				m_fDy = -m_fSpeed;
				m_fCurrFrame += 0.005*fTime;
				if(m_fCurrFrame > 3) m_fCurrFrame -= 3;
				m_Sprite.setTextureRect(IntRect(96*static_cast<int>(m_fCurrFrame), 288, 96, 96));
				break;
				
			// Игрок пожелал пойти вниз
			case DOWN:
				m_fDy = m_fSpeed;
				m_fCurrFrame += 0.005*fTime;
				if(m_fCurrFrame > 3) m_fCurrFrame -= 3;
				m_Sprite.setTextureRect(IntRect(96*static_cast<int>(m_fCurrFrame), 0, 96, 96));
				break;
				
			// Игрок не нажал клавишу (стоим)
			case STAY:
				m_fDx = m_fSpeed;
				m_fDy = m_fSpeed;
				break;
		}
		
		m_fX += m_fDx*fTime; // Получаем новую координату для спрайта икс
		Collision(m_fDx, 0.f); // Просчитываем столкновения по иксу
		m_fY += m_fDy*fTime; // Получаем новую координату для спрайта игрек
		Collision(0.f, m_fDy); // Просчитываем столкновения по игреку
		
		m_fSpeed = 0.f;
		m_Sprite.setPosition(m_fX, m_fY); // Перемещаем спрайт в полученные координаты
		m_state = STAY;
		
//		if(m_nHealth <= 0) m_bLife = false;
//	}
}

// Просчёт столкновений
void CActor::Collision(float fDx, float fDy) {
	for(unsigned i = m_fY/32; i < (m_fY+m_nH)/32; i++)
		for(unsigned j = m_fX/32; j < (m_fX+m_nW)/32; j++) {
			if(g_szMap[i][j] == '0') { // Если встретили стену
				if(fDy > 0) {
					m_fY = i*32 - m_nH; // Координата по игрек*ширину клетки - высота спрайта
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
			
			if(g_szMap[i][j] == '2') { // Если пересекли лабу
				g_szMap[i][j] = '1'; // Рисуем вместо лабы пол
				m_uLabCnt++;
			}
		}
}

// Обработка нажатия клавиши
void CActor::Input() {
	if(Keyboard::isKeyPressed(Keyboard::Left)) {
		m_state = LEFT;
		m_fSpeed = 0.1f;
	}
	if(Keyboard::isKeyPressed(Keyboard::Right)) {
		m_state = RIGHT;
		m_fSpeed = 0.1f;
	}
	if(Keyboard::isKeyPressed(Keyboard::Up)) {
		m_state = UP;
		m_fSpeed = 0.1f;
	}
	if(Keyboard::isKeyPressed(Keyboard::Down)) {
		m_state = DOWN;
		m_fSpeed = 0.1f;
	}
}