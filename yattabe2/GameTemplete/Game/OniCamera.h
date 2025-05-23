#pragma once
class Oni;
class Player;
class Game;
class OniCamera:public IGameObject
{
public:
	OniCamera();
	~OniCamera();
	bool Start();
	void Update();
	float posy = -200.0f;
	float m_time = 0.0f;
	Vector3 m_toCameraPos = Vector3::Zero;

	Oni* m_oni=nullptr;
	Player* m_player=nullptr;
	Game* m_game=nullptr;

	
};

