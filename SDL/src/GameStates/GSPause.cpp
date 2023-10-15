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

	pHome = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("Home_Button.png"), SDL_FLIP_NONE);
	pHome->Set2DPosition(SCREEN_WIDTH * 3 / 4 - 25, SCREEN_HEIGHT / 2 - 25);
	pHome->SetSize(50, 50);
	pHome->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	listOption.push_back(pHome);

	pRestart = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("Restart_Button.png"), SDL_FLIP_NONE);
	pRestart->SetSize(50, 50);
	pRestart->Set2DPosition(SCREEN_WIDTH / 4 - 25, SCREEN_HEIGHT / 2 - 25);
	pRestart->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_SELECTTYPE);
		});
	listOption.push_back(pRestart);

	pResume = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("Play_Button.png"), SDL_FLIP_NONE);
	pResume->SetSize(50, 50);
	pResume->Set2DPosition(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 - 25);
	pResume->SetOnClick([this] {
		GameStateMachine::GetInstance()->PopState();
		});
	listOption.push_back(pResume);
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