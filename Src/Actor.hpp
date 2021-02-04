/*++

VegeTable group, FTI grp. <extr>

Filename:
	Actor.hpp
	
Abstract:
	Definition CActor class (player)
	
Author:
	KIRAY

--*/

#ifndef _ACTOR_H
#define _ACTOR_H

#include "Entity.hpp"

class CActor : public CEntity {
public:
	CActor();
	CActor(sf::Texture&, float, float, int, int);
	
	void Frame(float& fTime);
	
	unsigned uLabCnt; // ���-�� ��������� ���.
	
private:
	void Input(); // ��������� ������� ������
	void Collision(float fDx, float fDy); // ������� ������������

	eStates m_state; // ��������� (���� �������� ��� �����)
};

#endif // ndef _ACTOR_H