//Автор Пийпаринен Алексей 21317гр 
// Класс врага
#ifndef _ENEMY_H
#define _ENEMY_H

#include "Entity.hpp"

class CEnemy : public CEntity {
public:
	int direction;//направление движения врага

	CEnemy();             // Конструкторы с без параметра и с параметрами 
	CEnemy(sf::Texture&, float, float, int, int, std::string);
//	~CEnemy();

	void checkCollisionWithMap(float fDx, float fDy);//ф-ция проверки столкновений с картой
	void Frame(float& fTime);

	std::string* m_pszMapCode;
//	void setMap(std::string* dsd) {m_pszMapCode = dsd;}

	sf::Sprite getSprite() {return m_Sprite;}

};

/*
	bool  m_bLife;
	int   m_nW, m_nH, m_nHealth;
	float m_fX, m_fY, m_fDx, m_fDy;
	float m_fSpeed, m_fCurrFrame;
	sf::Sprite  m_Sprite;
*/

#endif // ndef _ENEMY_H