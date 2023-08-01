#include "Bullet.h"
#include "TextureManager.h"

Bullet::Bullet(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip)
	:BaseObject(texture), m_iWidth(100), m_iHeight(50)
{
	m_flip = flip;
	Init();
}

void Bullet::Init()
{
}

void Bullet::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Render(m_position.x, m_position.y, m_iWidth, m_iHeight, m_angle, m_flip);
	}

}

void Bullet::Update(float deltatime)
{
}

void Bullet::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

Vector3 Bullet::Get2DPosition()
{
	return Vector3(m_position.x, m_position.y, 0.0f);
}

void Bullet::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int Bullet::GetWidth()
{
	return m_iWidth;
}

int Bullet::GetHeight()
{
	return m_iHeight;
}

void Bullet::SetRotation(double angle)
{
	m_angle = angle;
}

float Bullet::GetRotation()
{
	return (float) m_angle;
}

void Bullet::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}

void Bullet::SetActive(bool Active)
{
	isActive = Active;
}

bool Bullet::GetActive()
{
	return isActive;
}
