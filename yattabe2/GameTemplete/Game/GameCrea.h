#pragma once
#include "sound/SoundSource.h"
class Game;
class EndingCamera;
class PlayerCamera;
class Title;
class Fead;
class GameCrea :public IGameObject
{
public:
	GameCrea();
	~GameCrea();

	bool Start();
	void Update();

	void Render(RenderContext& rc);

	bool m_spriteFlag = false;
	float t = 0.0f;
	float m_alpha=1.0f;
	Game* m_game=nullptr;
	EndingCamera* m_edCamera=nullptr;
	PlayerCamera* m_plcame = nullptr;
	SoundSource* m_bgm = nullptr;
	Title* m_title = nullptr;
	Fead* m_fead = nullptr;

private:
	SpriteRender m_spriteRender;
	SpriteRender m_mozi;
};

