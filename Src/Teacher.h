//Автор Свиридникова Дарья Сергеевна 21317гр  
// Класс учителя

#ifndef _TEACHER_H
#define _TEACHER_H

#include "Entity.hpp"

class CTeacher : public CEntity {
public:
	int direction1;//направление движения врага

	CTeacher();             // Конструкторы с без параметра и с параметрами 
	CTeacher(sf::Texture&, float, float, int, int, std::string);
//	~CEnemy();

	void CollisionWithMap(float m_fDx, float m_fDy);//ф-ция проверки столкновений с картой
	void Frame(float& fTime);

	std::string* m_pszMapCode;
//	void setMap(std::string* dsd) {m_pszMapCode = dsd;}

	sf::Sprite getSprite() {return m_Sprite;}

};

#endif // ndef _TEACHER_H