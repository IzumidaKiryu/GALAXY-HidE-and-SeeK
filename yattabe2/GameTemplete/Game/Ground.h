#pragma once
class Ground:public IGameObject
{
public:
	Ground();
	~Ground();

	bool Start() override;
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_position = Vector3::Zero;

	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
};

