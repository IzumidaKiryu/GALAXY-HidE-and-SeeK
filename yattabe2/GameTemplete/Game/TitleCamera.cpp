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
	//注視点から視点までのベクトルを設定。
	m_CameraPos.Set(0.0f, 150.0f, 400.0f);
	m_tlpl = FindGO<TItlePlayer>("tlpl");

	//カメラのニアクリップとファークリップを設定する。
	g_camera3D->SetNear(100.0f);
	g_camera3D->SetFar(20000.0f);

	return true;
}

void TitleCamera::Update()
{
	//カメラを更新。
	//注視点を計算する。
	Vector3 target = m_tlpl->m_position;
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_CameraPos;
	//パッドの入力を使ってカメラを回す。
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y軸周りの回転

	m_Rot.SetRotationDeg(Vector3::AxisY, 2.0f * x);

	m_Rot.Apply(m_CameraPos);
	//X軸周りの回転。
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_CameraPos);
	axisX.Normalize();
	m_Rot.SetRotationDeg(axisX, 2.0f * y);
	m_Rot.Apply(m_CameraPos);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir = m_CameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.2f) {
		//カメラが上向きすぎ。
		m_CameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		//カメラが下向きすぎ。
		m_CameraPos = toCameraPosOld;
	}

	//視点を計算する。
	Vector3 pos = target+m_CameraPos;
	//メインカメラに注視点と視点を設定する。
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//カメラの更新。
	g_camera3D->Update();
}
