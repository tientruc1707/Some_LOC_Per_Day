#pragma once
#include "BaseObject.h"
#include "GameStateBase.h"

class Enemy : BaseObject
{
public:
	Enemy(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~Enemy();
	void		Init() override;
	void		Draw(SDL_Renderer* renderer) override;
	void		Update(float deltatime) override;

	void		Set2DPosition(float x, float y);
	void		SetFlip(SDL_RendererFlip flip);
	Vector2		Get2DPosition();
	void		SetSize(int width, int height);
	int			GetWidth();
	int			GetHeight();

	void		SetEnemyAlive(bool Alive);
	bool		GetEnemyAlive();

	std::shared_ptr<Sprite2D> deathEnemy;
protected:
	Vector2			m_Vec2DPos;
	int			m_iHeight;
	int			m_iWidth;
	int			m_currentFrame;
	float		m_frameTime;
	float		m_currentTime;
	int			m_spriteRow; //start 0,1,2
	int		m_frameCount; // start from 1,2,3...
	float  m_currentTicks;
	Uint32 m_lastUpdate;
	int m_numAction;
	bool Alive = true;
};