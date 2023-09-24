#pragma once
#include "BaseObject.h"
#include "MouseButton.h"
#include "Text.h"
#include "TextureManager.h"

class PauseGame : public MouseButton
{
private:
	std::shared_ptr<MouseButton> button;
	std::list<std::shared_ptr<MouseButton>> listButton;
	std::shared_ptr<Text> pauseText;
	bool isPause = false;
public:
	PauseGame();
	PauseGame(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip);
	void Draw(SDL_Renderer* renderer) override;
	/*void setPause(bool pause);
	bool getPasue();*/
};