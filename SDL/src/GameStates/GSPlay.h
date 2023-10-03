﻿#pragma once
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

class GSPlay :
	public GameStateBase
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
	void drawRect(SDL_Renderer* renderer);
	void drawEnemyRect(SDL_Renderer* renderer);
	void	Draw(SDL_Renderer* renderer) override;
//	void	MovePlayer(float dx, float dy);

	void EnemyAutoMove(std::shared_ptr<Enemy> e);
	//Lấy chỉ số của hướng xxoay
	int getAngleIndex(double gunAngle, int numAngles, double angleSteps);

	//Time countdown
	Uint32 startTime = SDL_GetTicks();
	Uint32 currentTime, elapsedTime;
	int countdown = 2 * 60;
	SDL_Color BLACK;
	int m_KeyPress;
	float spawnTime = timeToSpawn;
	bool isGameOver = false;
private:
	std::shared_ptr<Sprite2D>	m_background;
	//std::shared_ptr<Text>		m_score;

	//Button
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::shared_ptr<MouseButton> button;

	//player
	std::shared_ptr<Player>					m_player;
	std::shared_ptr<Player>					playerRotation;
	std::shared_ptr<Player>					m_currentAnimation;
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

	float time = 0.0f;
	float m_shootDelay = 20;
	float m_lastShoot = 0.0;
	float gunAngle = 0.0;

	//số hướng quay
	int numAngle = 8;
	//độ chia nhỏ nhất
	double angleSteps = 360.0 / numAngle;
	//hướng quay được chọn
	int currentAngleIndex = 0;
};

