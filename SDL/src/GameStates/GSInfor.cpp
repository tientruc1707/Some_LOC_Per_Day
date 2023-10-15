#include "GSInfor.h"

GSInfor::GSInfor()
{
}

GSInfor::~GSInfor()
{
}

void GSInfor::Init()
{
	bgr = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("bgr_game.png"), SDL_FLIP_NONE);
	bgr->Set2DPosition(0, 0);
	bgr->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	quitButton = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("Next_Button.png"), SDL_FLIP_HORIZONTAL);
	quitButton->Set2DPosition(30, 30);
	quitButton->SetSize(50, 50);
	quitButton->SetOnClick([this] {
		GameStateMachine::GetInstance()->PopState();
		});
	SDL_Color black = { 0,0,0 };
	credit = std::make_shared<Text>("Data/NotJamChunkySans.ttf", black, 28);
	credit->Set2DPosition(100, 100);
	credit->LoadFromRenderText("Game made by YuuKun_Jul17th");
	credit->SetSize(400, 28);
}

void GSInfor::Exit()
{
}

void GSInfor::Pause()
{
}

void GSInfor::Resume()
{
}

void GSInfor::HandleEvents()
{
}

void GSInfor::HandleKeyEvents(SDL_Event& e)
{
	quitButton->HandleTouchEvent(&e);
}

void GSInfor::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
}

void GSInfor::HandleMouseMoveEvents(int x, int y)
{
}

void GSInfor::Update(float deltaTime)
{
}

void GSInfor::Draw(SDL_Renderer* renderer)
{
	bgr->Draw(renderer);
	quitButton->Draw(renderer);
	credit->Draw(renderer);
}
