#pragma once
class Player;
class EndingCamera :public IGameObject
{
public:
	EndingCamera();
	~EndingCamera();

	bool Start();
	void Update();

	bool m_endEagingFlag = false;
	Vector3 m_target=Vector3::Zero;
	Vector3 m_fastTarget = Vector3::Zero;
	Vector3 m_endTarget = Vector3::Zero;
	Vector3 m_fastPos = Vector3::Zero;
	Vector3 m_endPos = Vector3::Zero;
	Vector3 m_pos = Vector3::Zero;
	float t = 0.0f;
	Player* m_player=nullptr;
	Vector3 m_toCameraPos = Vector3::Zero;
};

