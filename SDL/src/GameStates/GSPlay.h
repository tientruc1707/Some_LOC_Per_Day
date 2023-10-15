#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Enemy.h"
#include "Player.h"
#include "Gun.h"
#include "Bullet.h"
#include "Timer.h"
#include "GameObject/Text.h"

enum ENEMIES {Enemy1, Enemy2, Enemy3, Enemy4};
enum GUNS {Piston, M249, Soc_Lo};

class Sprite2D;
class SpriteAnimation;

class GSPlay : public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;
	void	Pause() override;
	void	Resume() override;
	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;


	void	drawRect(SDL_Renderer* renderer);
	void	drawEnemyRect(SDL_Renderer* renderer);
	void	EnemyAutoMove(std::shared_ptr<Enemy> e);
	void	GetBestScore(int highScore);

	//Lấy chỉ số của hướng xxoay
	int getAngleIndex(double gunAngle, int numAngles, double angleSteps);

private:
	std::shared_ptr<Sprite2D>	m_background;

	//Button
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::shared_ptr<MouseButton> button;

	//player
	std::shared_ptr<Player>					m_player;
	std::shared_ptr<Player>					playerRotation;
	std::vector<std::shared_ptr<Player>>	m_listAnimation;

	//Enemy
	std::shared_ptr<Enemy> m_enemy;
	std::list<std::shared_ptr<Enemy>> m_listEnemy;

	//Gun
	std::shared_ptr<Gun> m_gun;
	std::list<std::shared_ptr<Gun>> m_listGun;
	
	//Bullet
	std::shared_ptr<Bullet> m_bullet;
	std::list<std::shared_ptr<Bullet>> m_listBullet;

	//Time countdown
	std::shared_ptr<Text>		min;
	std::shared_ptr<Text>		sec;

	// Score
	std::shared_ptr<Text>		m_score;
	std::shared_ptr<Text>		score;
	int scores = 0;

	//Heart
	std::shared_ptr<Sprite2D> heartIcon;
	std::vector<std::shared_ptr<Sprite2D>> listHearthIcon;

	//Win or Lose
	std::shared_ptr<SpriteAnimation> Winer;
	std::shared_ptr<Sprite2D> Loser;
	std::shared_ptr<MouseButton> backToHome;

	float m_shootDelay = 20;
	float m_lastShoot = 0.0;
	float gunAngle = 0.0;

	//số hướng quay
	int numAngle = 8;
	//độ chia nhỏ nhất
	double angleSteps = 360.0 / numAngle;
	//hướng quay được chọn
	int currentAngleIndex = 0;
	//Time countdown
	Uint32 startTime = SDL_GetTicks();
	Uint32 currentTime, elapsedTime;
	int countdown = 1 * 60;
	SDL_Color BLACK = { 0, 0, 0 };

	//Spawn Enemy
	float spawnTime = timeToSpawn;
	bool isGameOver = false;

	int heart_nums = 3;
	int m_KeyPress;
	int bestScore = 0;
};

