#include "GSMenu.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}



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

	//// exit button
	//texture = ResourceManagers::GetInstance()->GetTexture("Next_Button.png");
	//exitButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//exitButton->SetSize(50, 50);
	//exitButton->Set2DPosition(SCREEN_WIDTH - exitButton->GetWidth(), 10);
	//exitButton->SetOnClick([]() {
	//	exit(0);
	//	});
	//m_listButton.push_back(exitButton);

	// game title
	///Set Font
	m_textColor = { 255, 255, 0 };
	m_textGameName = std::make_shared<Text>("Data/NotJamChunkySans.ttf", m_textColor, 28);
	m_textGameName->SetSize(500, 75);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth())/2, SCREEN_HEIGHT / 7 );
	m_textGameName->LoadFromRenderText("Monster Attack");
	//m_Sound = std::make_shared<Sound>("Data/Sounds/Still_Want_It.mp3");
	//m_Sound->PlaySound();
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
	//m_Sound->StopSound();

}

void GSMenu::Resume()
{
	//m_Sound->PlaySound();
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
	m_background->Update(deltaTime);
	for (auto& it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto& it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_textGameName->Draw(renderer);
}
