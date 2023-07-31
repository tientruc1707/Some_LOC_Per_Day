#pragma once
#include "BaseObject.h"

class Bullet : BaseObject
{
protected:
	int m_iWidth;
	int m_iHeight;
	SDL_RendererFlip m_flip;
	bool isActive;

public:
	Bullet() : BaseObject(), m_iWidth(0), m_iHeight(0) {}
	Bullet(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip);
	void Init() override;
	void Draw(SDL_Renderer* renderer) override;

	void Update(float deltatime) override;
	void Set2DPosition(float x, float y);
	Vector3		Get2DPosition();
	void SetSize(int width, int height);
	int GetWidth();
	int GetHeight();
	void SetRotation(double angle);
	void SetFlip(SDL_RendererFlip flip);

	void SetActive(bool Active);
	bool GetActive();
};