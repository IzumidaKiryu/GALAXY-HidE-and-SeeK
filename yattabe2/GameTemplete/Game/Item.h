#pragma once
#include "sound/SoundSource.h"
class Player;
class Item:public IGameObject
{
public:
	Item();
	~Item();

	bool Start()override;
	void Update();
	void Render(RenderContext& rc);

	ModelRender m_modelRender;

	Player* m_player=nullptr;
	SoundSource* m_bgm = nullptr;

	Vector3 m_position = Vector3::Zero;
	float m_groundtime = 0.0f;
	int m_count = 0;
	int m_pox=0;
	int m_poz=0;
};

