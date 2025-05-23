#pragma once
class GameCrea;
class Player;
class Game;
class NokoriTime :public IGameObject
{
public:
	NokoriTime();
	~NokoriTime();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	float m_timer = 80.0f;
	FontRender m_fontRender;

	Game* m_game=nullptr;
	GameCrea* m_crea=nullptr;
	Player* m_player=nullptr;

	bool m_onRenderFlag = true;
	
};

