/*++

VegeTable group, FTI grp. 21317

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
	CEntity(sf::Texture&, float, float, int, int, std::string);
	
	int getHealth() { return m_nHealth; }  // Получить здоровье
	void setHealth(int const nHealth) { m_nHealth = nHealth; }  // Установить здоровье

	sf::Sprite& getSprite() { return m_Sprite; }  // Получить спрайт

	// Получить прямоугольник, в котором находится спрайт
	sf::FloatRect getRect() {
		sf::FloatRect rect(m_fX, m_fY, m_nW, m_nH);
		return rect;
	}
	
	virtual void Frame(float&) = 0;  // Подготовка кадра
	
	bool  m_bLife; // Флаг, показывающий, жив иль нет
	
protected:
	// Состояния
	enum eStates {
		LEFT = 0,
		RIGHT,
		UP,
		DOWN,
		STAY
	};
	
	int   m_nW, m_nH, m_nHealth; // Высота, ширина спрайта и здоровье соответственно
	float m_fX, m_fY, m_fDx, m_fDy; // Текущая координата икс, игрек, смещение, на которое необходимо будет сдвинуться по иксу и игреку
	float m_fSpeed, m_fCurrFrame; // Скорость перемещения, текущий кадр
	sf::Sprite  m_Sprite; // Спрайт
	
private:
	float m_fMoveTimer;
	
	std::string m_szName; // Имя НПС
	sf::Texture m_Texture; // Текстура, которая будет наложена на спрайт
};

#endif // ndef _ENTITY_H