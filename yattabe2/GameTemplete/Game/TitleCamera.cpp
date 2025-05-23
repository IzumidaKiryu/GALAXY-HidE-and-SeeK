#include "stdafx.h"
#include "TitleCamera.h"
#include "TitlePlayer.h"



TitleCamera::TitleCamera() 
{
}

TitleCamera::~TitleCamera()
{
}

bool TitleCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_CameraPos.Set(0.0f, 150.0f, 400.0f);
	m_tlpl = FindGO<TItlePlayer>("tlpl");

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	g_camera3D->SetNear(100.0f);
	g_camera3D->SetFar(20000.0f);

	return true;
}

void TitleCamera::Update()
{
	//�J�������X�V�B
	//�����_���v�Z����B
	Vector3 target = m_tlpl->m_position;
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_CameraPos;
	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y������̉�]

	m_Rot.SetRotationDeg(Vector3::AxisY, 2.0f * x);

	m_Rot.Apply(m_CameraPos);
	//X������̉�]�B
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_CameraPos);
	axisX.Normalize();
	m_Rot.SetRotationDeg(axisX, 2.0f * y);
	m_Rot.Apply(m_CameraPos);
	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	Vector3 toPosDir = m_CameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.2f) {
		//�J����������������B
		m_CameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		//�J�����������������B
		m_CameraPos = toCameraPosOld;
	}

	//���_���v�Z����B
	Vector3 pos = target+m_CameraPos;
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//�J�����̍X�V�B
	g_camera3D->Update();
}
