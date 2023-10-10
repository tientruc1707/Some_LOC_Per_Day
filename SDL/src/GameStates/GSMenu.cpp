#include "GSMenu.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}

bool isSound = true;

void GSMenu::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bgr_game.png");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(2 * SCREEN_WIDTH, 2 * SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("Play_Button.png");
	playButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	playButton->SetSize(100, 100);
	playButton->Set2DPosition(SCREEN_WIDTH * 2 / 3, 180);
	playButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(playButton);

	texture = ResourceManagers::GetInstance()->GetTexture("cup.png");
	honorButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	honorButton->Set2DPosition(SCREEN_WIDTH * 2 / 3, 300);
	honorButton->SetSize(100, 100);
	honorButton->SetOnClick([this] {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_HONOR);
		});
	m_listButton.push_back(honorButton);

	texture = ResourceManagers::GetInstance()->GetTexture("information.png");
	inforButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	inforButton->Set2DPosition(SCREEN_WIDTH * 2 / 3, 420);
	inforButton->SetSize(100, 100);
	inforButton->SetOnClick([this] {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_INFOR);
		});
	m_listButton.push_back(inforButton);

	// game title
	m_textColor = { 255, 255, 0 };
	m_textGameName = std::make_shared<Text>("Data/NotJamChunkySans.ttf", m_textColor, 28);
	m_textGameName->SetSize(500, 75);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth()) / 2, SCREEN_HEIGHT / 7);
	m_textGameName->LoadFromRenderText("Monster Attack");

	//sound
	m_Sound = std::make_shared<Sound>("Data/Sounds/Still_Want_It.mp3");
	m_Sound->PlaySound();

	texture = ResourceManagers::GetInstance()->GetTexture("Music_On.png");
	musicOnButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	musicOnButton->Set2DPosition(50, 50);
	musicOnButton->SetSize(75, 75);
	musicOnButton->SetOnClick([this] {
		m_Sound->PauseSound();
		isSound = false;
		});
	texture = ResourceManagers::GetInstance()->GetTexture("Music_Off.png");
	musicOffButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	musicOffButton->Set2DPosition(50, 50);
	musicOffButton->SetSize(75, 75);
	musicOffButton->SetOnClick([this] {
		m_Sound->ResumeSound();
		isSound = true;
		});
}

void GSMenu::Exit()
{
	//ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(SDL_Event& e)
{
}

void GSMenu::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto& button : m_listButton)
	{
		if (button ->HandleTouchEvent(&e))
		{
			break;
		}
	}
	isSound ? musicOnButton->HandleTouchEvent(&e) : musicOffButton->HandleTouchEvent(&e);
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}
float time = 0.0f;
void GSMenu::Update(float deltaTime)
{
	time += deltaTime;
	//printf("DeltaTime = %f", deltaTime);
	if (time >= 1.5f)
	{
		time = 0.0f;
	}
	for (auto& it : m_listButton)
	{
		it->Update(deltaTime);
	}
	musicOnButton->Update(deltaTime);
	musicOffButton->Update(deltaTime);
}

void GSMenu::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto& it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_textGameName->Draw(renderer);
	isSound ? musicOnButton->Draw(renderer) : musicOffButton->Draw(renderer);
}