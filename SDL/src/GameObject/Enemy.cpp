#include "Enemy.h"
#include "TextureManager.h"
#include "SpriteAnimation.h"
#include "BaseObject.h"

Enemy::Enemy(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : BaseObject(texture)
{
	m_spriteRow = spriteRow;
	m_frameCount = frameCount;
	m_numAction = numAction;
	//m_animSpeed = animSpeed;
	m_frameTime = frameTime;
	//m_flip = flip;
	m_currentFrame = 0;
	m_currentTicks = 0;
	m_lastUpdate = SDL_GetTicks();
	Init();
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->RenderFrame(m_position.x, m_position.y, m_iWidth, m_iHeight, m_spriteRow, m_currentFrame, m_frameCount, m_numAction, m_angle, m_flip);
	}
}

void Enemy::Update(float deltatime)
{
	m_currentTicks += deltatime;
	if (m_currentTicks >= m_frameTime) {
		m_currentFrame++;
		if (m_currentFrame >= m_frameCount) {
			m_currentFrame = 0;
		}
		m_currentTicks -= m_frameTime;
	}
}

void Enemy::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

void Enemy::SetRotation(double angle)
{
	m_angle = angle;
}

void Enemy::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}

Vector2 Enemy::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);
}

void Enemy::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int Enemy::GetWidth()
{
	return m_iWidth;
}

int Enemy::GetHeight()
{
	return m_iHeight;
}

void Enemy::SetEnemyAlive(bool isAlive)
{
	Alive = isAlive;
}

bool Enemy::GetEnemyAlive()
{
	return Alive;
}
