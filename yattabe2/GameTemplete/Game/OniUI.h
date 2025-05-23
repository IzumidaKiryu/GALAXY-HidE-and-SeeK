#pragma once
class Oni;
class OniUI:public IGameObject
{
public:
	OniUI();
	~OniUI();

	bool Start()override;
	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_SpriteRender;
	SpriteRender m_spriteRender2;
	SpriteRender m_spriteNige;
	FontRender m_fontRender;

	bool m_nigeFlag = false;

	Vector3 m_scalb = Vector3::Zero;

	Oni* m_oni=nullptr;
};

