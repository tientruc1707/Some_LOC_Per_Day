#pragma once
#include "GameStateBase.h"
#include "MouseButton.h"
#include "Text.h"
#include "TextureManager.h"

class GSPause : public GameStateBase
{
private:
	std::shared_ptr<Text> pauseText;
	bool isPause = false;
	
	std::shared_ptr<MouseButton> pRestart;
	std::shared_ptr<MouseButton> pResume;
	std::shared_ptr<MouseButton> pSound;
	std::vector<std::shared_ptr<MouseButton>> listOption;
	
	std::shared_ptr<Sprite2D> background;
public:
	GSPause();
	~GSPause();
	
	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	
};