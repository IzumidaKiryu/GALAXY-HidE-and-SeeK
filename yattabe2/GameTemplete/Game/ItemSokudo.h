#pragma once
#include "sound/SoundSource.h"
class Player;
class ItemManage;
class ItemSokudo:public IGameObject
{
public:
	ItemSokudo();
	~ItemSokudo();

	bool Start()override;
	void Update();

	void Render(RenderContext& rc);

	ModelRender m_modelRender;

	Player* m_player=nullptr;
	ItemManage* m_Imana=nullptr;
	SoundSource* m_bgm = nullptr;

	Vector3 m_position = Vector3::Zero;
	float m_groundtime = 0.0f;
	int m_count = 0;
	int m_syozi = 0;
	int m_sokupox=0;
	int m_sokupoz=0;
};

