// Teacher class

#ifndef _TEACHER_H
#define _TEACHER_H

#include "Entity.hpp"

class CTeacher : public CEntity {
public:
	int direction1;//����������� �������� �����

	CTeacher();             // ������������ � ��� ��������� � � ����������� 
	CTeacher(sf::Texture&, float, float, int, int);

	void CollisionWithMap(float m_fDx, float m_fDy);//�-��� �������� ������������ � ������
	void Frame(float& fTime);
};

#endif // ndef _TEACHER_H