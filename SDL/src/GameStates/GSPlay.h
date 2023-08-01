#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Enemy.h"
#include "Player.h"
#include "Gun.h"
#include "Bullet.h"

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
	void	Draw(SDL_Renderer* renderer) override;
	void	MovePlayer(float dx, float dy);

	void EnemyAutoMove(std::shared_ptr<Enemy> e);

	int m_KeyPress;

private:
	std::shared_ptr<Sprite2D>	m_background;
	//std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<Player>>	m_listAnimation;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<MouseButton> button;
	//Enemy
	std::shared_ptr<Enemy> m_enemy;
	std::list<std::shared_ptr<Enemy>> m_listEnemy;
	//Gun
	std::shared_ptr<Gun> m_gun1, m_gun2, m_gun3, m_selectedGun;
	std::list<std::shared_ptr<Gun>> m_listGun;
	//Bullet
	std::shared_ptr<Bullet> m_bullet;
	std::list<std::shared_ptr<Bullet>> m_listBullet;

	float time = 0.0f;
	float m_Velocity = 10.0f;

	float m_shootDelay = 20;
	float m_lastShoot = 0.0;
	float gunAngle = 0.0;

	int playerDirection = 1;
};

