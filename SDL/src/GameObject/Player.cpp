#include "Player.h"
#include "TextureManager.h"
#include "SpriteAnimation.h"
#include "BaseObject.h"

Player::Player(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : BaseObject(texture)
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

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->RenderFrame(m_position.x, m_position.y, m_iWidth, m_iHeight, m_spriteRow, m_currentFrame, m_frameCount, m_numAction, m_angle, m_flip);
	}
}

void Player::Update(float deltatime)
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

void Player::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

void Player::SetRotation(double angle)
{
	m_angle = angle;
}

void Player::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}

Vector2 Player::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);
}

void Player::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int Player::GetWidth()
{
	return m_iWidth;
}

int Player::GetHeight()
{
	return m_iHeight;
}

void Player::SetPlayerAlive(bool isAlive)
{
	Alive = isAlive;
}

bool Player::GetPlayerAlive()
{
	return Alive;
}

void Player::MoveLeft(float deltatime)
{
	if (m_position.x < 0)
	{
		m_position.x = 0;
	}
	else
		m_position.x -= 100 * deltatime;
}

void Player::MoveRight(float deltatime)
{
	if (m_position.x > 2 * SCREEN_WIDTH - this->GetWidth())
	{
		m_position.x = 2 * SCREEN_WIDTH - this->GetWidth();
	}
	else
		m_position.x += 100 * deltatime;
}

void Player::MoveUp(float deltatime)
{
	if (m_position.y < 0)
	{
		m_position.y = 0;
	}
	m_position.y -= 100 * deltatime;
}

void Player::MoveDown(float deltatime)
{
	if (m_position.y > 2 * SCREEN_HEIGHT - this->GetHeight())
	{
		m_position.y = 2 * SCREEN_HEIGHT - this->GetHeight();
	}
	m_position.y += 100 * deltatime;
}
