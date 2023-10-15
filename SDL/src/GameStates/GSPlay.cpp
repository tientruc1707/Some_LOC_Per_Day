#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include <GSMenu.h>
#include "GSSelectType.h"

extern int selectPlayer;

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
		angle += 360;

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
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	//button pause
	texture = ResourceManagers::GetInstance()->GetTexture("Pause_Button.png");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PAUSE);
		});
	m_listButton.push_back(button);

	// Pick Player
	switch (selectPlayer)
	{
	case 1:
		texture = ResourceManagers::GetInstance()->GetTexture("player1.png");
		break;
	case 2:
		texture = ResourceManagers::GetInstance()->GetTexture("player2.png");
		break;
	case 3:
		texture = ResourceManagers::GetInstance()->GetTexture("player3.png");
		break;
	default:
		break;
	}
	//Player and Rotation
	for (int i = 7; i >= 0; i--)
	{
		if (i == 7)
			playerRotation = std::make_shared<Player>(texture, 2, 2, 8, 0.5f);
		else if (i == 6)
			playerRotation = std::make_shared<Player>(texture, 1, 2, 8, 0.5f);
		else
			playerRotation = std::make_shared<Player>(texture, i + 3, 2, 8, 0.5f);
		playerRotation->SetFlip(SDL_FLIP_NONE);
		playerRotation->SetSize(50, 60);
		m_listAnimation.push_back(playerRotation);
	}
	m_player = m_listAnimation[0];
	m_player->Set2DPosition(450, 300);

	//Bullet
	for (int i = 0; i < 20; ++i)
	{
		m_bullet = std::make_shared<Bullet>(ResourceManagers::GetInstance()->GetTexture("bullet.png"), SDL_FLIP_NONE);
		m_bullet->SetSize(12, 12);
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
	m_gun = std::make_shared<Gun>(ResourceManagers::GetInstance()->GetTexture("weaponR3.png"), SDL_FLIP_NONE);
	m_gun->SetSize(40,20);
	m_gun->SetPicked(false);
	//m_gun->Set2DPosition(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
	m_listGun.push_back(m_gun);

	//Score
	m_score = std::make_shared<Text>("Data/NotJamChunkySans.ttf", BLACK, 14);
	m_score->SetSize(110, 40);
	m_score->Set2DPosition((SCREEN_WIDTH - m_score->GetWidth()) / 2, 30);
	m_score->LoadFromRenderText("SCORE : ");

	score = std::make_shared<Text>("Data/NotJamChunkySans.ttf", BLACK, 14);
	score->SetSize(50, 40);
	score->Set2DPosition(m_score->Get2DPosition().x + m_score->GetWidth() + 5, 30);

	//Hearth
	for (int i = 0; i < heart_nums; ++i)
	{
		int x = i * 50 + 10;
		heartIcon = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("heart.png"), SDL_FLIP_NONE);
		heartIcon->SetSize(50, 50);
		heartIcon->Set2DPosition(x, 80);
		listHearthIcon.push_back(heartIcon);
	}
	Winer = std::make_shared<SpriteAnimation>(ResourceManagers::GetInstance()->GetTexture("victory.jpg"), 2, 5, 4, 0.2f);
	Winer->SetSize(300, 300);
	Winer->Set2DPosition((SCREEN_WIDTH - Winer->GetWidth()) / 2, (SCREEN_HEIGHT - Winer->GetHeight()) / 2);
	Loser = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("Lose.jpg"), SDL_FLIP_NONE);
	Loser->SetSize(500, 300);
	Loser->Set2DPosition((SCREEN_WIDTH - Loser->GetWidth()) / 2, (SCREEN_HEIGHT - Loser->GetHeight()) / 2);
	backToHome = std::make_shared<MouseButton>(ResourceManagers::GetInstance()->GetTexture("Home_Button.png"), SDL_FLIP_NONE);
	backToHome->SetSize(70, 70);
	backToHome->Set2DPosition((SCREEN_WIDTH - backToHome->GetWidth()) / 2, Winer->Get2DPosition().y + Winer->GetHeight() + 10);
	backToHome->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	//Camera::GetInstance()->SetTarget(m_player);

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
	double midPoint_x = m_player->Get2DPosition().x + m_player->GetWidth() / 2;
	double midPoint_y = m_player->Get2DPosition().y + m_player->GetHeight() / 2;
	//If a key was pressed
	switch (e.type) {
	case SDL_KEYDOWN:
		if (e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
		{//Adjust the velocity
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
		if (e.key.repeat == 0)
		{//Adjust the velocity
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
		gunAngle = point_direction(midPoint_x, midPoint_y, e.motion.x, e.motion.y);
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
						it->Set2DPosition(m_gun->Get2DPosition().x + m_gun->GetWidth() / static_cast<float>(2),
							m_gun->Get2DPosition().y + m_gun->GetHeight() / static_cast<float>(2));
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
	if (isGameOver)
	{
		backToHome->HandleTouchEvent(&e);
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	if (!isGameOver)
	{
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
		//PlayerRotation
		m_player->Update(deltaTime);
		for (auto& it : m_listAnimation) {
			it->Set2DPosition(m_player->Get2DPosition().x, m_player->Get2DPosition().y);
			it->Update(deltaTime);
		}
		m_player = m_listAnimation[currentAngleIndex];

		//Spawn enemy each 5s
		spawnTime += deltaTime;
		int value;
		if (spawnTime > timeToSpawn)
		{
			//Random chose enemy
			for (int i = 0; i < 4; ++i)
			{
				float x, y;
				value = rand() % 4;
				ENEMIES enemy = static_cast<ENEMIES>(value);
				switch (enemy)
				{
				case Enemy1:
					m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy1-2-4.png"), 1, 8, 3, 0.125f);
					break;
				case Enemy2:
					m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy1-2-4.png"), 2, 8, 3, 0.125f);
					break;
				case Enemy3:
					m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy1-2-4.png"), 3, 8, 3, 0.125f);
					break;
				case Enemy4:
					m_enemy = std::make_shared<Enemy>(ResourceManagers::GetInstance()->GetTexture("Enemy1-2-4.png"), 3, 8, 3, 0.125f);
					break;
				default:
					break;
				}
				int side = rand() % 4; // Chọn ngẫu nhiên 1 trong 4 cạnh của màn hình
				switch (side)
				{
				case 0: // Cạnh trên
					x = rand() % SCREEN_WIDTH; // Chọn ngẫu nhiên hoành độ từ 0 đến SCREEN_WIDTH
					y = 0; // Đặt tung độ bằng âm chiều cao của enemy
					break;
				case 1: // Cạnh phải
					x = SCREEN_WIDTH; // Đặt hoành độ bằng chiều rộng của màn hình
					y = rand() % SCREEN_HEIGHT; // Chọn ngẫu nhiên tung độ từ 0 đến SCREEN_HEIGHT
					break;
				case 2: // Cạnh dưới
					x = rand() % SCREEN_WIDTH; // Chọn ngẫu nhiên hoành độ từ 0 đến SCREEN_WIDTH
					y = SCREEN_HEIGHT; // Đặt tung độ bằng chiều cao của màn hình
					break;
				case 3: // Cạnh trái
					x = 0; // Đặt hoành độ bằng âm chiều rộng của enemy
					y = rand() % SCREEN_HEIGHT; // Chọn ngẫu nhiên tung độ từ 0 đến SCREEN_HEIGHT
					break;
				}
				m_enemy->SetSize(50, 50);
				m_enemy->Set2DPosition(x, y);
				m_enemy->SetEnemyAlive(true);
				m_listEnemy.push_back(m_enemy);
			}
			spawnTime = 0.0f;
		}

		//Update Enemy
		for (auto& it : m_listEnemy)
		{
			// Get the enemy position and size
			float ex = it->Get2DPosition().x;
			float ey = it->Get2DPosition().y;
			float ew = it->GetWidth();
			float eh = it->GetHeight();

			// Get player position and size
			float px = m_player->Get2DPosition().x;
			float py = m_player->Get2DPosition().y;
			float pw = m_player->GetWidth();
			float ph = m_player->GetHeight();
			//Move to Player
			GSPlay::EnemyAutoMove(it);
			it->SetFlip(ex - px > 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

			// check collision with bullet and player
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
						scores += 10;
						score->LoadFromRenderText(std::to_string(scores));
						break;
					}
				}
				//coliision with player
				if (checkVAR(px, py, pw, ph, ex, ey, ew, eh))
				{
					heart_nums--;
					it->SetEnemyAlive(false);
				}
			}

			// outside window
			if (ex + ew < 0 || ex > SCREEN_WIDTH || ey + eh < 0 || ey > SCREEN_HEIGHT)
			{
				it->SetEnemyAlive(false);
			}

			it->Update(deltaTime);
		}
		//Update Gun
		//Hand Posision
		double handX = m_player->Get2DPosition().x + m_player->GetWidth() / 2 + cos(gunAngle * M_PI / 180) * 12.5;
		double handY = m_player->Get2DPosition().y + m_player->GetHeight() / 2 + sin(gunAngle * M_PI / 180) * 12.5;
		m_gun->SetRotation(gunAngle);
		m_gun->SetFlip(gunAngle > 90 && gunAngle <= 270 ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
		//Set Gun on Hand
		m_gun->Set2DPosition(handX - m_gun->GetWidth() / 2, handY );

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
				if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT)
				{
					it->SetActive(false);
				}
			}
			it->Update(deltaTime);
		}

		//Time
		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - startTime;
		if (elapsedTime >= 1000)
		{
			countdown = (countdown <= 1) ? 1 : countdown - 1;
			startTime = currentTime;
		}
		//Min
		int minutes = countdown / 60;
		min = std::make_shared<Text>("Data/NotJamChunkySans.ttf", BLACK, 14);
		min->SetSize(50, 40);
		min->Set2DPosition(25, 30);
		min->LoadFromRenderText(std::to_string(minutes) + " : ");

		//Sec
		int seconds = countdown % 60;
		sec = std::make_shared<Text>("Data/NotJamChunkySans.ttf", BLACK, 14);
		sec->SetSize(50, 40);
		sec->Set2DPosition(min->Get2DPosition().x + min->GetWidth() + 5, 30);
		seconds < 10 ? sec->LoadFromRenderText("0 " + std::to_string(seconds))
			: sec->LoadFromRenderText(std::to_string(seconds));

		//Check GameOver
		isGameOver = (minutes < 1 && seconds < 1);// || (heart_nums < 1 && seconds > 1);
		if (isGameOver)
		{
			bestScore = std::max(scores, bestScore);
			GSPlay::GetBestScore(bestScore);
		}
		//Update position of camera
		//Camera::GetInstance()->Update(deltaTime);
	}
	Winer->Update(deltaTime);
}

void GSPlay::drawRect(SDL_Renderer* renderer)
{
	SDL_Rect hitboxRect;
	hitboxRect.x = m_player->Get2DPosition().x;
	hitboxRect.y = m_player->Get2DPosition().y;
	hitboxRect.w = m_player->GetWidth();
	hitboxRect.h = m_player->GetHeight();
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &hitboxRect);
}

void GSPlay::drawEnemyRect(SDL_Renderer* renderer)
{
	SDL_Rect enemyRect;
	enemyRect.x = m_enemy->Get2DPosition().x;
	enemyRect.y = m_enemy->Get2DPosition().y;
	enemyRect.w = m_enemy->GetWidth();
	enemyRect.h = m_enemy->GetHeight();
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderDrawRect(renderer, &enemyRect);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	min->Draw(renderer);
	sec->Draw(renderer);
	m_score->Draw(renderer);
	score->Draw(renderer);
	for (auto& it : m_listButton)
	{
		it->Draw(renderer);
	}
	//Draw player
	for (auto& it : m_listAnimation)
	{
		if (it == m_player)
		{
			it->Draw(renderer);
			drawRect(renderer);
		}
	}

	//Draw hearth
	for (int i = 0 ; i < heart_nums; ++i)
	{
		listHearthIcon[i]->Draw(renderer);
	}
	//Draw gun
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
		{
			it->Draw(renderer);
			drawEnemyRect(renderer);
		} 
		else {
			it->deathEnemy->Draw(renderer);
		}
	}
	if (isGameOver)
	{
		heart_nums < 1 ? Loser->Draw(renderer) : Winer->Draw(renderer);
		backToHome->Draw(renderer);
	}
}

void GSPlay::EnemyAutoMove(std::shared_ptr<Enemy> e)
{

	int m_enemySpeed = 1 ;
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

void GSPlay::GetBestScore(int highScore)
{
	
	FILE* file = NULL;
	fopen_s(&file, "Data/bestScore.txt", "w");
	if (file == nullptr)
	{
		return;
	}
	fprintf(file, "%d", highScore);
	fclose(file);
}

int GSPlay::getAngleIndex(double gunAngle, int numAngles, double angleSteps)
{
	
	//làm tròn gunANgle đến số int gần nhất
	int roundedAngle = (int)round(gunAngle);
	int angleIndex = (roundedAngle / (int)angleSteps) % numAngles;
	return angleIndex;
}
