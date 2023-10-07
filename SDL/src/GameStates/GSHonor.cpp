#include "GSHonor.h"
#include "GSPlay.h"

GSHonor::GSHonor()
{
}

GSHonor::~GSHonor()
{
}

void GSHonor::Init()
{
	background = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("bgr_game.png"), SDL_FLIP_NONE);
	background->Set2DPosition(0, 0);
	background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	quitButton = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("Next_Button.png"), SDL_FLIP_HORIZONTAL);
	quitButton->Set2DPosition(30,30);
	quitButton->SetSize(75, 75);
	quitButton->SetOnClick([this] {
		GameStateMachine::GetInstance()->PopState();
		});

	bestScore_img = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("bestScore.jpg"), SDL_FLIP_NONE);
	bestScore_img->SetSize(522, 478);
	bestScore_img->Set2DPosition((SCREEN_WIDTH - bestScore_img->GetWidth()) / 2, (SCREEN_HEIGHT - bestScore_img->GetHeight()) / 2);

	FILE* file = NULL;
	fopen_s(&file, "Data/bestScore.txt", "r");
	if (file == nullptr)
	{
		return;
	}
	fscanf_s(file, "%d", &highScore);

	SDL_Color black = { 0,0,0 };
	bestScore = std::make_shared<Text>("Data/NotJamChunkySans.ttf", black, 10);
	std::shared_ptr<GSPlay> score = std::make_shared<GSPlay>();
	bestScore->Set2DPosition(bestScore_img->Get2DPosition().x + 230, bestScore_img->Get2DPosition().y + 350);
	bestScore->SetSize(70, 50);
	bestScore->LoadFromRenderText(std::to_string(highScore));
	fclose(file);
}

void GSHonor::Exit()
{
}

void GSHonor::Pause()
{
}

void GSHonor::Resume()
{
}

void GSHonor::HandleEvents()
{
}

void GSHonor::HandleKeyEvents(SDL_Event& e)
{
}

void GSHonor::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	quitButton->HandleTouchEvent(&e);
}

void GSHonor::HandleMouseMoveEvents(int x, int y)
{
}

void GSHonor::Update(float deltaTime)
{
}

void GSHonor::Draw(SDL_Renderer* renderer)
{
	background->Draw(renderer);
	bestScore_img->Draw(renderer);
	bestScore->Draw(renderer);
	quitButton->Draw(renderer);
}
