//Автор Свиридникова Дарья Сергеевна 21317гр  
// Класс учителя

#include "Teacher.hpp"

using namespace sf;

CTeacher::CTeacher() : CEntity() {}

CTeacher::CTeacher(sf::Texture& Texture, float fX, float fY, int nW, int nH) : 
CEntity(Texture, fX, fY, nW, nH) {
		//Задаем спрайту один прямоугольник для вывода одного игрока. IntRect – для приведения типов 
		m_Sprite.setTextureRect(IntRect(0, 0, m_nW, m_nH));

		direction1 = rand() % (3); //Направление движения врага задаём случайным образом через генератор случайных чисел 
		m_fSpeed = 0.07f;//даем скорость.этот объект всегда двигается  /// KIRAY: Speed change
		m_fDx = m_fSpeed;
}

//ф-ция проверки столкновений с картой
void  CTeacher::CollisionWithMap(float m_fDx, float m_fDy) { 
			for (unsigned i = m_fY / 32; i < (m_fY + m_nH) / 32; i++)//проходимся по элементам карты 
				for (unsigned j = m_fX / 32; j<(m_fX + m_nW) / 32; j++) 
				{ 
					if (g_szMap[i][j] == '0')//если элемент - тайлик земли
					{ 
					if (m_fDy > 0) {
						m_fY = i * 32 - m_nH;
						m_fDy = 0.1f; 
						direction1 = rand() % (3); //Направление движения врага по Y 
					}  if (m_fDy < 0) {
						m_fY = i * 32 + 32;
						m_fDy = 0.1f; 
						direction1 = rand() % (3);//Направление движения врага столкновение с верхними краями 
					}  if (m_fDx > 0) {
						m_fX = j * 32 - m_nW;
						m_fDx = 0.1f; 
						direction1 = rand() % (3);//Направление движения врага с правым краем карты 
					}  if (m_fDx < 0) {
						m_fX = j * 32 + 32;
						m_fDx = 0.1f; 
						direction1 = rand() % (3); //Направление движения врага с левым краем карты 
					}
					}
				}
}


void CTeacher::Frame(float& fTime) {

				switch (direction1) //делаются различные действия в зависимости от состояния 
				{ 

				case RIGHT: {//состояние идти вправо 
					m_fDx = m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 2) m_fCurrFrame -= 2;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 192, 96, 96)); 
					break; } 
			
				case LEFT:	{//состояние идти влево 
					m_fDx = -m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 2) m_fCurrFrame -= 2;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 96, 96, 96));
					break; } 
				
				case UP:	{//идти вверх 
					m_fDy = -m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 2) m_fCurrFrame -= 2;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 288, 96, 96));
					break; }
				
				case DOWN:	{//идти вниз 
					m_fDy = m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 2) m_fCurrFrame -= 2;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 0, 96, 96));
					break; } 
			}  

			m_fX += m_fDx*fTime; //движение по “X”
			CollisionWithMap(m_fDx, 0);//обрабатываем столкновение по Х 
			m_fY += m_fDy*fTime; //движение по “Y” 
			CollisionWithMap(0, m_fDy);//обрабатываем столкновение по Y 
			m_Sprite.setPosition(m_fX, m_fY); //спрайт в позиции (x, y). 

	} 