/*++

VegeTable group, FTI grp. 21317

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
	CActor(sf::Texture&, float, float, int, int, std::string);
	
	void Frame(float& fTime);
	
	unsigned getLabCnt() {return m_uLabCnt;} // �������� ���-�� ��������� ���.
	
private:
	void Input(); // ��������� ������� ������
	void Collision(float fDx, float fDy); // ������� ������������
	
	unsigned m_uLabCnt; // ���-�� ��������� ���.

	eStates m_state; // ��������� (���� �������� ��� �����)
};

#endif // ndef _ACTOR_H