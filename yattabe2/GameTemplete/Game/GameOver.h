#pragma once
#include "sound/SoundSource.h"
class Game;
class Title;
class Fead;
class GameOver:public IGameObject
{
public:
	GameOver();
	~GameOver();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	FontRender m_fontRender;
	SpriteRender m_spriteRender;
	Fead* m_fead = nullptr;
	Game* m_game = nullptr;
	SoundSource* m_bgm = nullptr;
	Title* m_title = nullptr;

	bool m_spriteFlag = false;
	float t = 0.0f;
	float m_alpha = 1.0f;
};

