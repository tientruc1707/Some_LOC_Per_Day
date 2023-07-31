#include "Gun.h"
#include "TextureManager.h"

Gun::Gun(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip)
	:BaseObject(texture), m_iWidth(100), m_iHeight(50)
{
	m_flip = flip;
	Init();
}

void Gun::Init()
{
}

void Gun::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Render(m_position.x, m_position.y, m_iWidth, m_iHeight, m_angle, m_flip);
	}

}

void Gun::Update(float deltatime)
{
}

void Gun::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

Vector3 Gun::Get2DPosition()
{
	return Vector3(m_position.x, m_position.y, 0.0f);
}

void Gun::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int Gun::GetWidth()
{
	return m_iWidth;
}

int Gun::GetHeight()
{
	return m_iHeight;
}

void Gun::SetRotation(double angle)
{
	m_angle = angle;
}

void Gun::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}
