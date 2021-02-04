// Teacher class

#ifndef _TEACHER_H
#define _TEACHER_H

#include "Entity.hpp"

class CTeacher : public CEntity {
public:
	int direction1;//направление движения врага

	CTeacher();             // Конструкторы с без параметра и с параметрами 
	CTeacher(sf::Texture&, float, float, int, int);

	void CollisionWithMap(float m_fDx, float m_fDy);//ф-ция проверки столкновений с картой
	void Frame(float& fTime);
};

#endif // ndef _TEACHER_H