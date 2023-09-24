#include "PauseGame.h"

PauseGame::PauseGame() : MouseButton()
{
	m_position.x = 0;
	m_position.y = 0;
}

PauseGame::PauseGame(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip)
	: MouseButton(texture, flip)
{
}

void PauseGame::Draw(SDL_Renderer* renderer)
{

	if (m_pTexture != nullptr)
	{
		m_pTexture->RenderOriginal(m_position.x, m_position.y, m_iWidth, m_iHeight, m_angle, m_flip);
	}
}
//
//void PauseGame::setPause(bool pause)
//{
//	isPause = pause;
//}
//
//bool PauseGame::getPasue()
//{
//	return isPause;
//}
