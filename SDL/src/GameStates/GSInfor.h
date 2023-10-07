#pragma once
#include "GameStateBase.h"
#include "MouseButton.h"
#include "Text.h"

class GSInfor : public GameStateBase
{
public:
	GSInfor();
	~GSInfor();

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

};
