#include "stdafx.h"
#include "PlayerCamera.h"
#include "Player.h"

PlayerCamera::PlayerCamera() 
{
}
PlayerCamera::~PlayerCamera()
{
}

bool PlayerCamera::Start() {
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(0.0f, 125.0f, -250.0f);
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("player");
	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(30000.0f);

	return true;
}
void PlayerCamera::Update() {
	//�J�������X�V�B
	//�����_���v�Z����B
	m_target = m_player->m_position;
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	m_target.y += 80.0f;

	Vector3 toCameraPosOld = m_toCameraPos;
	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y������̉�]�B
	
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * x);
	
	qRot.Apply(m_toCameraPos);
	//X������̉�]�B
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Apply(m_toCameraPos);
	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.2f) {
		//�J����������������B
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		//�J�����������������B
		m_toCameraPos = toCameraPosOld;
	}

	//���_���v�Z����B
	m_pos = m_target + m_toCameraPos;
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	g_camera3D->SetTarget(m_target);
	g_camera3D->SetPosition(m_pos);

	//�J�����̍X�V�B
	g_camera3D->Update();
}


