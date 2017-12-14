#include "Map.hpp"

using namespace sf;

CMap::CMap() : m_uMapHeight(0), m_uMapWidth(0), m_pszMap(NULL) {
	m_szTailset = "";
}

CMap::CMap(const char* szMapName) {
	std::ifstream fMap(szMapName, std::ios::in);
	if(!fMap) std::cerr << "[ERR]:\tCan't find level: \'" << szMapName << "\'!\n";
	
	char tmp[6];
	fMap.getline(tmp, 6);
	std::sscanf(tmp, "%d %d", &m_uMapHeight, &m_uMapWidth);
	if(!m_uMapHeight || !m_uMapWidth) std::cerr << "[ERR]:\tInvalid level!";
	
	m_pszMap = new std::string[m_uMapHeight];
	for(unsigned i=0; i<m_uMapHeight; i++) std::getline(fMap, m_pszMap[i]);
	
	std::getline(fMap, m_szTailset);
	m_Texture.loadFromFile("./Data/"+m_szTailset+".png");
	m_Sprite.setTexture(m_Texture);
	
	fMap.close();
}

CMap::~CMap() {
	m_uMapHeight = 0;
	m_uMapWidth = 0;
	m_szTailset = "";
	
	delete[] m_pszMap;
	m_pszMap = NULL;
}

void CMap::Render(sf::RenderWindow& wnd) {
	for(unsigned i=0; i<m_uMapHeight; i++)
		for(unsigned j=0; j<m_uMapWidth; j++) {
			if(m_pszMap[i][j] == '0') m_Sprite.setTextureRect(IntRect(64, 0, 32, 32));
			if(m_pszMap[i][j] == '1') m_Sprite.setTextureRect(IntRect(0, 0, 32, 32));
			if(m_pszMap[i][j] == '2') m_Sprite.setTextureRect(IntRect(32, 0, 32, 32));
			
			m_Sprite.setPosition(j*32, i*32);
			wnd.draw(m_Sprite);
		}
}


void CMap::Frame(CActor& actor, float& fTime, float& fCurrFrame) {
	if(Keyboard::isKeyPressed(Keyboard::Left)) {
		actor.dir = CActor::LEFT;
		actor.m_fSpeed = 0.1f;
		
		fCurrFrame += 0.005f*fTime;
		if(fCurrFrame > 3.f) fCurrFrame -= 3.f;
		actor.Ractor.setTextureRect(IntRect(96*static_cast<int>(fCurrFrame), 96, 96, 96));
	}
	
	if(Keyboard::isKeyPressed(Keyboard::Right)) {
		actor.dir = CActor::RIGHT;
		actor.m_fSpeed = 0.1f;
		
		fCurrFrame += 0.005f*fTime;
		if(fCurrFrame > 3.f) fCurrFrame -= 3.f;
		actor.Ractor.setTextureRect(IntRect(96*static_cast<int>(fCurrFrame), 192, 96, 96));
	}
	
	if(Keyboard::isKeyPressed(Keyboard::Up)) {
		actor.dir = CActor::UP;
		actor.m_fSpeed = 0.1f;
		
		fCurrFrame += 0.005f*fTime;
		if(fCurrFrame > 3.f) fCurrFrame -= 3.f;
		actor.Ractor.setTextureRect(IntRect(96*static_cast<int>(fCurrFrame), 288, 96, 96));
	}
	
	if(Keyboard::isKeyPressed(Keyboard::Down)) {
		actor.dir = CActor::DOWN;
		actor.m_fSpeed = 0.1f;
		
		fCurrFrame += 0.005f*fTime;
		if(fCurrFrame > 3.f) fCurrFrame -= 3.f;
		actor.Ractor.setTextureRect(IntRect(96*static_cast<int>(fCurrFrame), 0, 96, 96));
	}
}