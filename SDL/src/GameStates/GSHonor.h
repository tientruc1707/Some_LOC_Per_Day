#pragma once
#include "GameStateBase.h"
#include "MouseButton.h"
#include "SpriteAnimation.h"
#include "Text.h"

class GSHonor : public GameStateBase
{
public:
	GSHonor();
	~GSHonor();

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
private:
	std::shared_ptr<MouseButton>	quitButton;
	std::shared_ptr<Text>		bestScore;
	std::shared_ptr<Sprite2D>	background;
	std::shared_ptr<Sprite2D>	bestScore_img;
	
	int highScore;
};