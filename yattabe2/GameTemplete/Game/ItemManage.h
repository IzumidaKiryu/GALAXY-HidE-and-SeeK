#pragma once
#include "sound/SoundSource.h"
class Player;
class ItemManage :public IGameObject
{
public:
	ItemManage();
	~ItemManage();

	bool Start()override;
	void Update();
	void Font();
	void Sokudohennka();
	void Render(RenderContext& rc);

	int m_SokuSyozi = 0;
	bool m_UpFlag = false;//速度が上がったかの判断フラグ。
	bool m_whatFontFlag = false;
	float m_timer = 0.0f;
	float m_larpTime = 0.0f;
	int m_saiseiCoice = 0;
	Vector3 m_scal = Vector3::Zero;
	Vector3 m_fastScal = { 0.0f,0.0f,0.0f };
	Vector3 m_endScal = { 2.0f,2.0f,0.0f };

	Player* m_player=nullptr;
	SoundSource* m_bgm = nullptr;
	SoundSource* m_bgm2 = nullptr;
	FontRender m_fontRender;

};

