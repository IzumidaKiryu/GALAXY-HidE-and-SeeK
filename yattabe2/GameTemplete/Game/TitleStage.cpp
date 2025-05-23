#include "stdafx.h"
#include "TitleStage.h"

TitleStage::TitleStage()
{

}

TitleStage::~TitleStage()
{
}

bool TitleStage::Start()
{
	m_modelRender.Init("Assets/material/TitleStera.tkm");
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	return true;
}

void TitleStage::Update()
{
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void TitleStage::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
