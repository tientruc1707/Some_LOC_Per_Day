#include "GSPause.h"
#include "Sprite2D.h"

GSPause::GSPause(){
}

GSPause::~GSPause()
{
}

void GSPause::Init()
{
	background = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("pause.jpg"), SDL_FLIP_NONE);
	background->Set2DPosition(0, 0);
	background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	pRestart = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("Restart_Button.png"), SDL_FLIP_NONE);
	pRestart->SetSize(50, 50);
	pRestart->Set2DPosition(SCREEN_WIDTH / 4 - 25, SCREEN_HEIGHT / 2 - 25);
	pRestart->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});

	listOption.push_back(pRestart);
	pResume = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("Play_Button.png"), SDL_FLIP_NONE);
	pResume->SetSize(50, 50);
	pResume->Set2DPosition(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 - 25);
	pResume->SetOnClick([this] {
		GameStateMachine::GetInstance()->PopState();
		});
	listOption.push_back(pResume);
	pSound = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("Music_On.png"), SDL_FLIP_NONE);
	pSound->SetSize(50, 50);
	pSound->Set2DPosition(3 * SCREEN_WIDTH / 4 - 25, SCREEN_HEIGHT / 2 - 25);
	listOption.push_back(pSound);
}

void GSPause::Exit()
{
}

void GSPause::Pause()
{
}

void GSPause::Resume()
{
}

void GSPause::HandleEvents()
{
}

void GSPause::HandleKeyEvents(SDL_Event& e)
{
}

void GSPause::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto& button : listOption)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSPause::HandleMouseMoveEvents(int x, int y)
{
}

void GSPause::Update(float deltaTime)
{
	for (auto& it : listOption) 
	{
		it->Update(deltaTime);
	}
}

void GSPause::Draw(SDL_Renderer* renderer)
{
	background->Draw(renderer);
	for (auto& it : listOption) {
		it->Draw(renderer);
	}
}