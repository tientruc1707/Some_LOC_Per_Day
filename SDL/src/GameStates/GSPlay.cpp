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

// tính khoảng cách giữa hai điểm
float distance(float x1, float y1, float x2, float y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// Calculate algle
double point_direction(double x1, double y1, double x2, double y2)
{
	double angle = atan2(y2 - y1, x2 - x1);
	// Chuyển đổi góc từ radian sang độ
	angle = angle * 180 / M_PI;
	// Đảm bảo góc nằm trong khoảng từ 0 đến 360 độ
	if (angle < 0)
		angle += 360.0;

	return angle;
}

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("bgr_game.png");

	//background
	m_background = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE);
	m_background->SetSize(2 * SCREEN_WIDTH, 2 * SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	//button close
	texture = ResourceManagers::GetInstance()->GetTexture("Next_Button.png");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(button);

   // Player and rotation
	texture = ResourceManagers::GetInstance()->GetTexture("player2.png");
	for (int i = 7; i >= 0; i--)
	{
		if(i == 7)
			playerRotation = std::make_shared<Player>(texture, 2, 2, 8, 0.5f);
		else if (i == 6)
			playerRotation = std::make_shared<Player>(texture, 1 , 2, 8, 0.5f);
		else
			playerRotation = std::make_shared<Player>(texture, i + 3, 2, 8, 0.5f);
		playerRotation->SetFlip(SDL_FLIP_NONE);
		playerRotation->SetSize(40, 50);
		m_listAnimation.push_back(playerRotation);

	}
	m_player = m_listAnimation[0];
	m_player->Set2DPosition(240, 400);

	int value = 0;
	//random chose enemy
	for (int i = 0; i < MAX_ENEMY; ++i)
	{
		value = rand() % 4;	
		ENEMIES enemy = static_cast<ENEMIES>(value);
		switch (enemy)
		{
		case Enemy1:
			m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy1-2-4.png"), 1, 8, 3, 0.5f); 
			break;
		case Enemy2:
			m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy1-2-4.png"), 2, 8, 3, 0.5f);
			break;
		case Enemy3:
			m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy1-2-4.png"), 3, 8, 3, 0.5f);
			break;
		case Enemy4:
			m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy1-2-4.png"), 3, 8, 3, 0.5f); 
			break;
		default:
			break;
		}
		
		m_enemy->SetSize(100, 100);
		m_enemy->Set2DPosition(rand() % 2 * SCREEN_WIDTH, rand() % 2 * SCREEN_HEIGHT);
		m_enemy->SetEnemyAlive(true);
		m_listEnemy.push_back(m_enemy);
	}
	//Bullet
	for (int i = 0; i < 20; ++i)
	{
		m_bullet = std::make_shared<Bullet>(ResourceManagers::GetInstance()->GetTexture("bullet.png"), SDL_FLIP_NONE);
		m_bullet->SetSize(10, 10);
		m_bullet->SetActive(false);
		m_listBullet.push_back(m_bullet);
	}
	//Gun
		////piston
		//m_gun2 = std::make_shared<Gun>(ResourceManagers::GetInstance()->GetTexture("weaponR2.png"),SDL_FLIP_NONE);
		//m_gun2->SetSize(20, 20);
		//m_gun2->SetPicked(true);
		//m_listGun.push_back(m_gun2);
	
		//M249
		m_gun = std::make_shared<Gun>(ResourceManagers::GetInstance()->GetTexture("weaponR1.png"),SDL_FLIP_NONE);
		m_gun->SetSize(30, 20);
		m_gun->SetPicked(false);
		m_gun->Set2DPosition(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
		m_listGun.push_back(m_gun);

		////Soc Lo
		//m_gun3 = std::make_shared<Gun>(ResourceManagers::GetInstance()->GetTexture("weaponR3.png"),SDL_FLIP_NONE);
		//m_gun3->SetSize(40, 20);
		//m_gun3->SetPicked(false);
		//m_gun3->Set2DPosition(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
		//m_listGun.push_back(m_gun3);

	Camera::GetInstance()->SetTarget(m_player);

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
	double midPoint_x = (m_player->Get2DPosition().x + m_player->GetWidth()) / 2;
	double midPoint_y = (m_player->Get2DPosition().y + m_player->GetHeight()) / 2;
	//If a key was pressed
	switch (e.type) {
	case SDL_KEYDOWN:
		if (e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				//playerDirection = UP;

				m_KeyPress |= KEY_UP;
				break;
			case SDLK_s:
				//playerDirection = DOWN;

				m_KeyPress |= KEY_DOWN;
				break;
			case SDLK_a:
				//playerDirection = LEFT;

				m_KeyPress |= KEY_LEFT;
				break;
			case SDLK_d:
				//playerDirection = RIGHT;

				m_KeyPress |= KEY_RIGHT;
				break;
			default:
				break;
			}

		}
		break;
		////Key Up
	case SDL_KEYUP:
		if (e.key.repeat == 0)
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
			// x > && y <
		if (midPoint_x >= SCREEN_WIDTH && m_gun->Get2DPosition().y < SCREEN_HEIGHT)
		{
			gunAngle = point_direction(midPoint_x, midPoint_y, 2 * e.motion.x, e.motion.y);
		}
		// x < && y >
		else if (midPoint_x < SCREEN_WIDTH && midPoint_y >= SCREEN_HEIGHT)
		{
			gunAngle = point_direction(midPoint_x, midPoint_y, e.motion.x, 2 * e.motion.y);
		}
		// x > && y >
		else if (midPoint_x >= SCREEN_WIDTH && midPoint_y >= SCREEN_HEIGHT)
		{
			gunAngle = point_direction(midPoint_x, midPoint_y, 2 * e.motion.x, 2 * e.motion.y);
		}
		// x < && y <
		else
		{
			gunAngle = point_direction(midPoint_x, m_gun->Get2DPosition().y, e.motion.x, e.motion.y);
		}
		currentAngleIndex = getAngleIndex(gunAngle, numAngle, angleSteps);

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
						it->Set2DPosition(m_gun->Get2DPosition().x + m_gun->GetWidth() / 2,
							m_gun->Get2DPosition().y + m_gun->GetHeight() / 2);
						it->SetRotation(gunAngle);
						it->SetActive(true);
						m_lastShoot = curentTime;
					}
				}
			}
		}
		break;
	}
}

void GSPlay::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto& button : m_listButton)
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
	//Handle KeyEvent

	//Update Button
	for (auto& it : m_listButton)
	{
		it->Update(deltaTime);
	}

	//Update Player
		//Move player
	switch (m_KeyPress)
	{
	case 1: // Move left

		m_player->MoveLeft(deltaTime);
		break;
	case 2: // Move down

		m_player->MoveDown(deltaTime);
		break;
	case 4: // Move right

		m_player->MoveRight(deltaTime);
		break;
	case 8: // Move up

		m_player->MoveUp(deltaTime);
		break;
	default:
		break;
	}
	m_player = m_listAnimation[currentAngleIndex];
	for (auto& it : m_listAnimation) {
		it->Set2DPosition(m_player->Get2DPosition().x, m_player->Get2DPosition().y);
		it->Update(deltaTime);
	}
	//Update Enemy
	for (auto& it : m_listEnemy)
	{
		// Get the enemy position and size
		float ex = it->Get2DPosition().x;
		float ey = it->Get2DPosition().y;
		float ew = it->GetWidth();
		float eh = it->GetHeight();

		//Move to Player
		GSPlay::EnemyAutoMove(it);
		it->SetFlip(ex - m_player->Get2DPosition().x > 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

		if (it->GetEnemyAlive()) //if enemy alive
		{
			//collision with bullet
			for (auto& bul : m_listBullet)
			{
				float xb = bul->Get2DPosition().x;
				float yb = bul->Get2DPosition().y;
				float wb = bul->GetWidth();
				float hb = bul->GetHeight();
				//check VAR
				if (checkVAR(xb, yb, wb, hb, ex, ey, ew, eh))
				{
					bul->SetActive(false);
					it->SetEnemyAlive(false);
					break;
				}
			}
		}
		it->Update(deltaTime);
	}

	//Spawn Enenmy 
	//time1 += deltaTime;
	//if (time1 >= 1.5f)
	//{
	//	for (int i = 0; i < MAX_ENEMY; ++i)
	//	{
	//		m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy1-2-4.png"), 1, 8, 3, 0.5f);
	//		/*m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy2.tga"), 1, 1, 7, 0.5f);
	//		m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy3.tga"), 1, 1, 7, 0.5f);
	//		m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy4.tga"), 1, 1, 7, 0.5f);*/
	//		m_enemy->SetFlip(SDL_FLIP_NONE);
	//		m_enemy->SetSize(30, 45);
	//		m_enemy->Set2DPosition(rand() % SCREEN_WIDTH,
	//								rand() %  SCREEN_HEIGHT);
	//		m_enemy->SetEnemyAlive(true);
	//		m_listEnemy.push_back(m_enemy);
	//	}
	//	time1 += 0.0f;
	//}

	//Update Gun
	float x = m_player->Get2DPosition().x,
		y = m_player->Get2DPosition().y,
		w = m_player->GetWidth(),
		h = m_player->GetHeight();
	//Hand Posision
	double handX = x + m_player->GetWidth() / 2 + cos(gunAngle * M_PI / 180) * 25;
	double handY = y + m_player->GetHeight() / 2 + sin(gunAngle * M_PI / 180) * 25;
	//Pick Gun
	/*if (checkVAR(x, y, w, h, m_gun1->Get2DPosition().x, m_gun1->Get2DPosition().y, m_gun1->GetWidth(), m_gun1->GetHeight()))
	{
		m_gun1->SetPicked(true);
		m_gun2->SetPicked(false);
		m_gun3->SetPicked(false);
	}
	if (checkVAR(x, y, w, h, m_gun2->Get2DPosition().x, m_gun2->Get2DPosition().y, m_gun2->GetWidth(), m_gun2->GetHeight()))
	{
		m_gun1->SetPicked(false);
		m_gun2->SetPicked(false);
		m_gun3->SetPicked(true);
	}*/
	//Pick gun done
	m_gun->SetRotation(gunAngle);
	//Set Gun on Hand
	m_gun->Set2DPosition(handX - m_gun->GetWidth() / 2, handY - m_gun->GetHeight() / 2);

	//Update BUllet
	for (auto& it : m_listBullet) {

		if (it->GetActive())
		{
			float x = it->Get2DPosition().x;
			float y = it->Get2DPosition().y;
			float r = it->GetRotation();
			x += 20 * cos(r * M_PI / 180);
			y += 20 * sin(r * M_PI / 180);

			// Set the new bullet position
			it->Set2DPosition(x, y);

			// Collision with screen
			if (x < 0 || x > 2 * SCREEN_WIDTH || y < 0 || y > 2 * SCREEN_HEIGHT)
			{
				it->SetActive(false);
			}
		}
		it->Update(deltaTime);
	}

	//Update position of camera
	Camera::GetInstance()->Update(deltaTime);
	m_player->Update(deltaTime);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->DrawOriginal(renderer);
	//m_score->Draw();
	for (auto& it : m_listButton)
	{
		it->Draw(renderer);
	}
//	obj->Draw(renderer);
	//Draw player
	for (auto& it : m_listAnimation)
	{
		if (it == m_player)
		{
			it->Draw(renderer);
		}
	}
	//Draw gun
	/*for (auto& it : m_listGun)
	{
		if (it->GetPicked())
			it->Draw(renderer);
	}*/
	m_gun->Draw(renderer);
	//Draw bullet
	for (auto& it : m_listBullet)
	{
		if (it->GetActive())
			it->Draw(renderer);
	}

	//Draw enemy
	for (auto& it : m_listEnemy)
	{
		if (it->GetEnemyAlive())
			it->Draw(renderer);
	}
}

void GSPlay::EnemyAutoMove(std::shared_ptr<Enemy> e)
{

	int m_enemySpeed = 1;
	//tinh go'c giua enemy vs palyer
	float angle = atan2(m_player->Get2DPosition().y - e->Get2DPosition().y, m_player->Get2DPosition().x - e->Get2DPosition().x);
	//tinh khoang cach
	float dist = distance(m_player->Get2DPosition().x, m_player->Get2DPosition().y, e->Get2DPosition().x, e->Get2DPosition().y);

	if (dist > 10)
	{
		float a = e->Get2DPosition().x;
		a += cos(angle) * m_enemySpeed;
		float b = e->Get2DPosition().y;
		b += sin(angle) * m_enemySpeed;

		e->Set2DPosition(a, b);
		dist = distance(m_player->Get2DPosition().x, m_player->Get2DPosition().y, a, b);
	}
}

int GSPlay::getAngleIndex(double gunAngle, int numAngles, double angleSteps)
{
	
	//làm tròn gunANgle đến số int gần nhất
	int roundedAngle = (int)round(gunAngle);
	int angleIndex = (roundedAngle / (int)angleSteps) % numAngles;
	return angleIndex;
}
