#pragma once
class Fead:public IGameObject
{
public:
	enum EnInOut {
		en_NowIn,	//���B
		en_NowOut	//���B
	};

	enum EnState {
		enState_FadeIn,			//�t�F�[�h�C�����B
		enState_FadeOut,		//�t�F�[�h�A�E�g���B
		enState_Idle,			//�A�C�h�����B
	};

	Fead();
	~Fead();

	bool Start() override;
	void Update();
	void Render(RenderContext& rc);

	
	void StartFadeIn()
	{
		
		m_state = enState_FadeIn;
	}
	
	void StartFadeOut()
	{
		m_state = enState_FadeOut;
	}
	
	const bool IsFade() const
	{
		return m_state != enState_Idle;
	}
	
	const float GetCurrentAlpha() const
	{
		return m_currentAlpha;
	}

	//�t�F�[�h�A�E�g�ォ�t�F�[�h�C���ォ���ׂ�֐��B
	const EnInOut IsInOut()
	{
		return m_BW;
	}

	void DeleteFead();


	SpriteRender		m_spriteRender;				//�X�v���C�g�����_�\�B
	EnState				m_state = enState_Idle;		//��ԁB
	EnInOut				m_BW = en_NowIn;			//enState_Idle�̎��t�F�[�h�A�E�g���I�������ォ�t�F�[�h�C�����I�������ォ��ʂ��邽�߂̃X�e�[�g�B
	float				m_currentAlpha = 1.0f;		//���݂̃��l�B������ύX����Ɖ摜�������ɂȂ�B
	
};

