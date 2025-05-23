#include "stdafx.h"
#include "EndingCamera.h"
#include "Player.h"

EndingCamera::EndingCamera()
{
}

EndingCamera::~EndingCamera()
{
}

bool EndingCamera::Start()
{
	
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("player");

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(30000.0f);

	m_target = m_player->m_position;
	m_target.y += 80.0f;

	m_fastTarget = m_target;
	m_endTarget = { m_target.x,10000.0f,m_target.z };
	
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(0.0f, 0.0f, -250.0f);
	m_pos = m_target + m_toCameraPos;
	m_fastPos = m_pos;
	m_endPos = { m_pos.x,10000.0f,m_pos.z };
	return true;
}

void EndingCamera::Update()
{
	
	t += g_gameTime->GetFrameDeltaTime()/5.0f;
	if (t > 1.0f) {
		t = 1.0f;
		m_endEagingFlag = true;
	}
	m_pos.Lerp(t, m_fastPos, m_endPos);
	m_target.Lerp(t, m_fastTarget, m_endTarget);

	g_camera3D->SetTarget(m_target);
	g_camera3D->SetPosition(m_pos);
	//�J�����̍X�V�B
	g_camera3D->Update();
}
