#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip)
{
}

void Bullet::Init()
{
}

void Bullet::Draw(SDL_Renderer* renderer)
{
}

void Bullet::Update(float deltatime)
{
}

void Bullet::Set2DPosition(float x, float y)
{
}

Vector3 Bullet::Get2DPosition()
{
	return Vector3();
}

void Bullet::SetSize(int width, int height)
{
}

int Bullet::GetWidth()
{
	return 0;
}

int Bullet::GetHeight()
{
	return 0;
}

void Bullet::SetRotation(double angle)
{
}

void Bullet::SetFlip(SDL_RendererFlip flip)
{
}

void Bullet::SetActive(bool Active)
{
	isActive = Active;
}

bool Bullet::GetActive()
{
	return isActive;
}
