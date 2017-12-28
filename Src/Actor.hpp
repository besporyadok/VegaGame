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
	
	unsigned uLabCnt; // Кол-во собранных лаб.
	
private:
	void Input(); // Обработка нажатия клавиш
	void Collision(float fDx, float fDy); // Просчёт столкновений

	eStates m_state; // Состояние (куда движемся иль стоим)
};

#endif // ndef _ACTOR_H