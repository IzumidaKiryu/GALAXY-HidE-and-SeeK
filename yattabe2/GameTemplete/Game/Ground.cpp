#include "stdafx.h"
#include "Ground.h"

Ground::Ground() {

}

Ground::~Ground()
{
}

bool Ground::Start()
{
	m_modelRender.Init("Assets/material/stera.tkm");

	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	//ステージにRay判定用の属性を与える。
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Stage);
	return true;
}

void Ground::Update() {
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}
void Ground::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}