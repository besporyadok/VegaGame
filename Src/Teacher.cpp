// Teacher class

#include "Teacher.hpp"

using namespace sf;

CTeacher::CTeacher() : CEntity() {}

CTeacher::CTeacher(sf::Texture& Texture, float fX, float fY, int nW, int nH) : 
CEntity(Texture, fX, fY, nW, nH) {
		//������ ������� ���� ������������� ��� ������ ������ ������. IntRect � ��� ���������� ����� 
		m_Sprite.setTextureRect(IntRect(0, 0, m_nW, m_nH));

		direction1 = rand() % (3); //����������� �������� ����� ����� ��������� ������� ����� ��������� ��������� ����� 
		m_fSpeed = 0.07f;//���� ��������.���� ������ ������ ���������  /// KIRAY: Speed change
		m_fDx = m_fSpeed;
}

//�-��� �������� ������������ � ������
void  CTeacher::CollisionWithMap(float m_fDx, float m_fDy) { 
			for (unsigned i = m_fY / 32; i < (m_fY + m_nH) / 32; i++)//���������� �� ��������� ����� 
				for (unsigned j = m_fX / 32; j<(m_fX + m_nW) / 32; j++) 
				{ 
					if (g_szMap[i][j] == '0')//���� ������� - ������ �����
					{ 
					if (m_fDy > 0) {
						m_fY = i * 32 - m_nH;
						m_fDy = 0.1f; 
						direction1 = rand() % (3); //����������� �������� ����� �� Y 
					}  if (m_fDy < 0) {
						m_fY = i * 32 + 32;
						m_fDy = 0.1f; 
						direction1 = rand() % (3);//����������� �������� ����� ������������ � �������� ������ 
					}  if (m_fDx > 0) {
						m_fX = j * 32 - m_nW;
						m_fDx = 0.1f; 
						direction1 = rand() % (3);//����������� �������� ����� � ������ ����� ����� 
					}  if (m_fDx < 0) {
						m_fX = j * 32 + 32;
						m_fDx = 0.1f; 
						direction1 = rand() % (3); //����������� �������� ����� � ����� ����� ����� 
					}
					}
				}
}


void CTeacher::Frame(float& fTime) {

				switch (direction1) //�������� ��������� �������� � ����������� �� ��������� 
				{ 

				case RIGHT: {//��������� ���� ������ 
					m_fDx = m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 2) m_fCurrFrame -= 2;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 192, 96, 96)); 
					break; } 
			
				case LEFT:	{//��������� ���� ����� 
					m_fDx = -m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 2) m_fCurrFrame -= 2;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 96, 96, 96));
					break; } 
				
				case UP:	{//���� ����� 
					m_fDy = -m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 2) m_fCurrFrame -= 2;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 288, 96, 96));
					break; }
				
				case DOWN:	{//���� ���� 
					m_fDy = m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 2) m_fCurrFrame -= 2;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 0, 96, 96));
					break; } 
			}  

			m_fX += m_fDx*fTime; //�������� �� �X�
			CollisionWithMap(m_fDx, 0);//������������ ������������ �� � 
			m_fY += m_fDy*fTime; //�������� �� �Y� 
			CollisionWithMap(0, m_fDy);//������������ ������������ �� Y 
			m_Sprite.setPosition(m_fX, m_fY); //������ � ������� (x, y). 

	} 