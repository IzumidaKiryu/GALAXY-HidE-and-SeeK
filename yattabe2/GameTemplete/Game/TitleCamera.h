#pragma once
class TItlePlayer;
class TitleCamera:public IGameObject
{
public:
	TitleCamera();
	~TitleCamera();

	bool Start();
	void Update();

	float m_timer = 0.0f;

	Vector3 m_CameraPos = Vector3::Zero;
	Quaternion m_Rot=Quaternion::Identity;

	TItlePlayer* m_tlpl = nullptr;
};

