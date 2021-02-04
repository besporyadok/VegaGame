/*++

VegeTable group, FTI grp. <extr>

Filename:
	Entity.hpp
	
Abstract:
	Definition base class for Actor, Enemy's and other
	
Author:
	KIRAY

--*/

#ifndef _ENTITY_H
#define _ENTITY_H

#include <SFML\Graphics.hpp>

#include "Map.h"

class CEntity {
public:
	CEntity();
	CEntity(sf::Texture&, float, float, int, int);

	sf::Sprite& getSprite() { return m_Sprite; }  // �������� ������

	// �������� �������������, � ������� ��������� ������
	sf::FloatRect getRect() {
		sf::FloatRect rect(m_fX, m_fY, m_nW, m_nH);
		return rect;
	}
	
	virtual void Frame(float&) = 0;  // ���������� �����
	
	bool  m_bLife; // ����, ������������, ��� ��� ���
	int nHealth; // ��������
	
protected:
	// ���������
	enum eStates {
		LEFT = 0,
		RIGHT,
		UP,
		DOWN,
		STAY
	};
	
	int   m_nW, m_nH; // ������, ������ ������� ��������������
	float m_fX, m_fY, m_fDx, m_fDy; // ������� ���������� ���, �����, ��������, �� ������� ���������� ����� ���������� �� ���� � ������
	float m_fSpeed, m_fCurrFrame; // �������� �����������, ������� ����
	sf::Sprite  m_Sprite; // ������
	
private:
	sf::Texture m_Texture; // ��������, ������� ����� �������� �� ������
};

#endif // ndef _ENTITY_H