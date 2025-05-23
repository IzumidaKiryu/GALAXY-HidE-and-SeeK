#pragma once
class TitleStage:public IGameObject
{
public:
	TitleStage();
	~TitleStage();

	bool Start();
	void Update();

	void Render(RenderContext& rc);

	Vector3 m_position = { 0.0f,0.0f,0.0f };

	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
};

