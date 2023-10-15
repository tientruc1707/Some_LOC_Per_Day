#pragma once
#include "GameStateBase.h"
#include "MouseButton.h"
#include "Player.h"

class GSSelectTpye : public GameStateBase
{
public:
	GSSelectTpye();
	~GSSelectTpye();
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
	std::shared_ptr<Sprite2D>	bgr;

	std::shared_ptr<MouseButton>	Button;
	std::vector<std::shared_ptr<MouseButton>> listButton;

	std::shared_ptr<Player>	player;
	std::vector<std::shared_ptr<Player>> listPlayer;

};