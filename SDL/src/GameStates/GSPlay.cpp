#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"

//check VAR
bool checkVAR(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
	return x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2;
}

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bgr_game.png");

	// background
	
	m_background = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("Next_Button.png");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

   // Player
	texture = ResourceManagers::GetInstance()->GetTexture("player2.png");
	m_player = std::make_shared<Player>( texture, 1,2,8, 0.5f);
	m_player->SetFlip(SDL_FLIP_HORIZONTAL);
	m_player->SetSize(40, 50);
	m_player->Set2DPosition(240, 400);
	m_listAnimation.push_back(m_player);

	//Bullet
	for (int i = 0; i < 20; ++i)
	{
		m_bullet = std::make_shared<Bullet>(ResourceManagers::GetInstance()->GetTexture("bullet.png"));
		m_bullet->SetSize(10, 10);
		m_bullet->SetActive(false);
		m_listBullet.push_back(m_bullet);
	}
	//Gun
		//piston
		m_gun2 = std::make_shared<Gun>(ResourceManagers::GetInstance()->GetTexture("weaponR2.png"));
		m_gun2->SetSize(20, 20);
		m_listGun.push_back(m_gun2);
		//M249
		m_gun1 = std::make_shared<Gun>(ResourceManagers::GetInstance()->GetTexture("weaponR1.png"));
		m_gun1->SetSize(30, 20);
		m_listGun.push_back(m_gun1);
		//Soc Lo
		m_gun3 = std::make_shared<Gun>(ResourceManagers::GetInstance()->GetTexture("weaponR3.png"));
		m_gun3->SetSize(40, 20);
		m_listGun.push_back(m_gun3);

	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation.push_back(m_player);

	m_KeyPress = 0;
}

void GSPlay::Exit()
{
	
}


void GSPlay::Pause()
{

}
void GSPlay::Resume()
{
	
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(SDL_Event& e)
{
	//If a key was pressed
	switch (e.type) {
	case SDL_KEYDOWN: 
		if(e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				m_KeyPress |= KEY_UP;
				break;
			case SDLK_s:
				m_KeyPress |= KEY_DOWN;
				break;
			case SDLK_a:
				m_KeyPress |= KEY_LEFT;
				break;
			case SDLK_d:
				m_KeyPress |= KEY_RIGHT;
				break;
			default:
				break;
			}

		}
		break;
		////Key Up
	case SDL_KEYUP:
		if(e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
				m_KeyPress ^= KEY_LEFT;
				break;
			case SDLK_s:
				m_KeyPress ^= KEY_DOWN;
				break;
			case SDLK_d:
				m_KeyPress ^= KEY_RIGHT;
				break;
			case SDLK_w:
				m_KeyPress ^= KEY_UP;
				break;
			default:
				break;
			}

		}
		break;
		//mouse motion
	case SDL_MOUSEMOTION:
		//rotation of gun
		for (auto& it : m_listGun)
		{
			gunAngle = atan2(e.motion.y - it->Get2DPosition().y, e.motion.x - it->Get2DPosition().x) * 180 / M_PI;
		}
		break;
		//left mouse click
	case SDL_MOUSEBUTTONDOWN:
		if (e.button.button == SDL_BUTTON_LEFT) { //cick left mouse
			for (auto& it : m_listBullet)
			{
				int curentTime = SDL_GetTicks();
				if (!it->GetActive()) //if bullet doesn't active
				{
					if (curentTime - m_lastShoot > m_shootDelay) {
						for (auto& weapon : m_listGun) { //each gun of listgun
							it->Set2DPosition(weapon->Get2DPosition().x + weapon->GetWidth() / 2,
								weapon->Get2DPosition().y + weapon->GetHeight() / 2);
							it->SetRotation(gunAngle);
							it->SetActive(true);
							m_lastShoot = curentTime;
						}
					}
				}
			}
		}
		break;
	}
}

void GSPlay::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}
float time1 = 0.0f;

void GSPlay::Update(float deltaTime)
{
	switch (m_KeyPress)//Handle Key event
	{
	default:
		break;
	}
	
	for (auto& it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto& it : m_listAnimation)
	{
		
	}
	//Spawn Enenmy 
	time1 += deltaTime;
	if (time1 >= 1.5f)
	{
		for (int i = 0; i < MAX_ENEMY; ++i)
		{
			m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy1.tga"), 1, 1, 7, 0.5f);
			m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy2.tga"), 1, 1, 7, 0.5f);
			m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy3.tga"), 1, 1, 7, 0.5f);
			m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy4.tga"), 1, 1, 7, 0.5f);

			m_enemy->SetSize(30, 45);
			m_enemy->Set2DPosition(rand() % 0 + (-10) || rand() % (SCREEN_WIDTH + 10) + SCREEN_WIDTH,
									rand() % 0 + (-10) || (SCREEN_HEIGHT + 10) + SCREEN_HEIGHT);
			m_enemy->SetEnemyAlive(true);
			m_listEnemy.push_back(m_enemy);
		}
		time1 += 0.0f;
	}
	//Update position of camera
	Camera::GetInstance()->Update(deltaTime);
	m_player->Update(deltaTime);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	//m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
//	obj->Draw(renderer);
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}
}
//Move Player
void GSPlay::MovePlayer(float dx, float dy) {
	// Get the player position and size
	float x = m_player->Get2DPosition().x;
	float y = m_player->Get2DPosition().y;
	float w = m_player->GetWidth();
	float h = m_player->GetHeight();

	// Move the player by dx and dy
	x += dx;
	y += dy;

	// Clamp the player position to the screen boundary
	x = std::max(0.0f, std::min(x, SCREEN_WIDTH - w));
	y = std::max(0.0f, std::min(y, SCREEN_HEIGHT - h));

	// Set the new player position
	m_player->Set2DPosition(x, y);
}