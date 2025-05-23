#pragma once
#include "sound/SoundSource.h"
class TItlePlayer;
class TitleStage;
class TitleCamera;
class Fead;
class Title :public IGameObject
{
public:
	Title();
	~Title();

	bool Start();
	void Update();
	void Moziten();
	void Render(RenderContext& rc);


	void ResetTitle() {
		m_isWaitFadeout = false;
		m_spriteFlag = false;
	}

	Vector3 m_fastPos = { 3840.0f,0.0f,0.0f };
	Vector3 m_endPos = { 0.0f,0.0f,0.0f };
	Vector3 m_vec = Vector3::Zero;

	SpriteRender m_spriteRender;
	SpriteRender m_GYALAXYRender;
	SpriteRender m_PressRender;

	TItlePlayer* m_tlpl=nullptr;
	TitleStage* m_tlssute=nullptr;
	TitleCamera* m_tlcm = nullptr;
	SoundSource* m_titleBGM = nullptr;
	Fead* m_fead = nullptr;

	bool m_isWaitFadeout = false;
	bool m_spriteFlag = false;
	bool m_moziFlag = false;
	bool m_GyaraFlag = false;
	bool m_gameLoopFlag = false;//ゲームループ後に生成されたかの判別。
	bool m_tpFlag = false;

	float m_alpha = 1.0f;
	float m_gyaraAlpha = 1.0f;
	float t = 0.0f;
};

