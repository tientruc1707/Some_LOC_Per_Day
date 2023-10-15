#include "GSSelectType.h"

int selectPlayer = 0;

GSSelectTpye::GSSelectTpye()
{
}

GSSelectTpye::~GSSelectTpye()
{
}

void GSSelectTpye::Init()
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("bgr_game.png");
	bgr = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	bgr->Set2DPosition(0, 0);
	bgr->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	texture = ResourceManagers::GetInstance()->GetTexture("Next_Button.png");
	Button = std::make_shared<MouseButton>(texture, SDL_FLIP_HORIZONTAL);
	Button->Set2DPosition(30, 30);
	Button->SetSize(50, 50);
	Button->SetOnClick([this] {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	listButton.push_back(Button);

	double point = -SCREEN_WIDTH / 3;
	int s = 0;
	texture = ResourceManagers::GetInstance()->GetTexture("khung_player.png");
	Button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	Button->Set2DPosition(point += SCREEN_WIDTH / 3, 70);
	Button->SetSize(SCREEN_WIDTH / 3, SCREEN_HEIGHT * 2 / 3);
	Button->SetOnClick([this] {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		selectPlayer = 1;
		});
	listButton.push_back(Button);
	Button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	Button->Set2DPosition(point += SCREEN_WIDTH / 3, 70);
	Button->SetSize(SCREEN_WIDTH / 3, SCREEN_HEIGHT * 2 / 3);
	Button->SetOnClick([this] {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		selectPlayer = 2;
		});
	listButton.push_back(Button);
	Button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	Button->Set2DPosition(point += SCREEN_WIDTH / 3, 70);
	Button->SetSize(SCREEN_WIDTH / 3, SCREEN_HEIGHT * 2 / 3);
	Button->SetOnClick([this] {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		selectPlayer = 3;
		});
	listButton.push_back(Button);

	texture = ResourceManagers::GetInstance()->GetTexture("player1.png");
	player = std::make_shared<Player>(texture, 1, 2, 8, 0.5f);
	player->SetSize(60, 80);
	player->Set2DPosition(120, 260);
	listPlayer.push_back(player);

	texture = ResourceManagers::GetInstance()->GetTexture("player2.png");
	player = std::make_shared<Player>(texture, 1, 2, 8, 0.5f);
	player->SetSize(60, 80);
	player->Set2DPosition(420, 260);
	listPlayer.push_back(player);

	texture = ResourceManagers::GetInstance()->GetTexture("player3.png");
	player = std::make_shared<Player>(texture, 1, 2, 8, 0.5f);
	player->SetSize(60, 80);
	player->Set2DPosition(720, 260);
	listPlayer.push_back(player);
}

void GSSelectTpye::Exit()
{
}

void GSSelectTpye::Pause()
{
}

void GSSelectTpye::Resume()
{
}

void GSSelectTpye::HandleEvents()
{
}

void GSSelectTpye::HandleKeyEvents(SDL_Event& e)
{
}

void GSSelectTpye::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto& it : listButton)
	{
		it->HandleTouchEvent(&e);
	}
}

void GSSelectTpye::HandleMouseMoveEvents(int x, int y)
{
}

void GSSelectTpye::Update(float deltaTime)
{
	for (auto& it : listPlayer)
	{
		it->Update(deltaTime);
	}
}

void GSSelectTpye::Draw(SDL_Renderer* renderer)
{
	bgr->Draw(renderer);
	for (auto& it : listPlayer)
	{
		it->Draw(renderer);
	}
	for (auto& it : listButton)
	{
		it->Draw(renderer);
	}
}
