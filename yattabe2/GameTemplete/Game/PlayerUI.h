#pragma once
class Player;
class PlayerUI:public IGameObject
{
public:
	PlayerUI();
	~PlayerUI();

	bool Start()override;
	void Update();
	void Render(RenderContext& rc);


	SpriteRender m_SpriteRender;
	SpriteRender m_spriteRender2;
	FontRender m_fontRender;

	Player* m_player=nullptr;
};

