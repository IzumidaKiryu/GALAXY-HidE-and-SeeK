#pragma once
class Fead:public IGameObject
{
public:
	enum EnInOut {
		en_NowIn,	//白。
		en_NowOut	//黒。
	};

	enum EnState {
		enState_FadeIn,			//フェードイン中。
		enState_FadeOut,		//フェードアウト中。
		enState_Idle,			//アイドル中。
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

	//フェードアウト後かフェードイン後か調べる関数。
	const EnInOut IsInOut()
	{
		return m_BW;
	}

	void DeleteFead();


	SpriteRender		m_spriteRender;				//スプライトレンダ―。
	EnState				m_state = enState_Idle;		//状態。
	EnInOut				m_BW = en_NowIn;			//enState_Idleの時フェードアウトが終了した後かフェードインが終了した後か区別するためのステート。
	float				m_currentAlpha = 1.0f;		//現在のα値。ここを変更すると画像が透明になる。
	
};

