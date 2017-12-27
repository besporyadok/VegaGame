//Автор Пийпаринен Алексей 21317гр 
// Класс врага

/*
	++	CEnemy (*)
	++	void checkCollisionWithMap(*)
	+-	void update(*)

	bool  m_bLife;
	int   m_nW, m_nH, m_nHealth;
	float m_fX, m_fY, m_fDx, m_fDy;
	float m_fSpeed, m_fCurrFrame;
	sf::Sprite  m_Sprite;
	fTime

*/

#include "Enemy.hpp"

using namespace sf;

CEnemy::CEnemy() : CEntity() {}

CEnemy::CEnemy(sf::Texture& Texture, float fX, float fY, int nW, int nH, std::string szName) : CEntity(Texture, fX, fY, nW, nH, szName) 
	{
		if (szName == "Army")
			{ //Задаем спрайту один прямоугольник для вывода одного игрока. IntRect – для приведения типов 
				m_nW = nW; m_nH = nH;
				m_Sprite.setTextureRect(IntRect(0, 0, m_nW, m_nH));

				direction = rand() % (3); //Направление движения врага задаём случайным образом через генератор случайных чисел 
				m_fSpeed = 0.1f;//даем скорость.этот объект всегда двигается 
				m_fDx = m_fSpeed; 

				m_fX = fX; m_fY = fY;
			} 
	}

//ф-ция проверки столкновений с картой
void  CEnemy::checkCollisionWithMap(float fDx, float fDy) { 
	/*		for (int i = m_fY / 32; i < (m_fY + m_nH) / 32; i++)//проходимся по элементам карты 
				for (int j = m_fX / 32; j < (m_fX + m_nW) / 32; j++) 
				{ 
					if (m_pszMapCode[i][j] == '0')//если элемент - тайлик земли
					{ 

					if (m_fDy > 0) 
					{ m_fY = i * 32 - m_nH;
					m_fDy = -0.1f; direction = rand() % (3); //Направление движения врага по Y 
					}

					if (m_fDy < 0) 
					{ m_fY = i * 32 + 32;
					m_fDy = 0.1f; direction = rand() % (3);//Направление движения врага столкновение с верхними краями 
					}

					if (m_fDx > 0) 
					{ m_fX = j * 32 - m_nW;
					m_fDx = -0.1f; direction = rand() % (3);//Направление движения врага с правым краем карты 
					} 
					
					if (m_fDx < 0) 
					{ m_fX = j * 32 + 32;
					m_fDx = 0.1f; direction = rand() % (3); //Направление движения врага с левым краем карты 
					}
					}
			*/
	for(unsigned i = m_fY/32; i < (m_fY+m_nH)/32; i++)
		for(unsigned j = m_fX/32; j < (m_fX+m_nW)/32; j++) {
			if(m_pszMapCode[i][j] == '0') {
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

	//bool  m_bLife;
	//int   m_nW, m_nH, m_nHealth;
	//float m_fX, m_fY, m_fDx, m_fDy;
	//float m_fSpeed, m_fCurrFrame;
	//sf::Sprite  m_Sprite;

void CEnemy::Frame(float& fTime) {
		//if (szName == "Army")
		//{ //для персонажа с таким именем логика будет такой 
		//	if (m_bLife) {//проверяем, жив ли герой 

				switch (direction) //делаются различные действия в зависимости от состояния 
				{ 

				case RIGHT: {//состояние идти вправо 
					m_fDx = m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 3) m_fCurrFrame -= 3;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 192, 96, 96)); 
					break; } 
			
				case LEFT:	{//состояние идти влево 
					m_fDx = -m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 3) m_fCurrFrame -= 3;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 96, 96, 96));
					break; } 
				
				case UP:	{//идти вверх 
					m_fDy = -m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 3) m_fCurrFrame -= 3;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 288, 96, 96));
					break; }
				
				case DOWN:	{//идти вниз 
					m_fDy = m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 3) m_fCurrFrame -= 3;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 0, 96, 96));
					break; } 
			} // end switch

			m_fX += m_fDx*fTime; //движение по “X”
			checkCollisionWithMap(m_fDx, 0);//обрабатываем столкновение по Х 
			m_fY += m_fDy*fTime; //движение по “Y” 
			checkCollisionWithMap(0, m_fDy);//обрабатываем столкновение по Y 
			m_Sprite.setPosition(m_fX, m_fY); //спрайт в позиции (x, y). 

		//	if (m_nHealth <= 0)
		//		{ m_bLife = false; }//если жизней меньше 0, либо равно 0, то умираем 
		//	} // end if life
		//}  // end if Army
	} // update