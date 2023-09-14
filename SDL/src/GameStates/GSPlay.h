#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Enemy.h"
#include "Player.h"
#include "Gun.h"
#include "Bullet.h"

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
	void	Draw(SDL_Renderer* renderer) override;
//	void	MovePlayer(float dx, float dy);

	void EnemyAutoMove(std::shared_ptr<Enemy> e);
	//Lấy chỉ số của hướng xxoay
	int getAngleIndex(double gunAngle, int numAngles, double angleSteps);

	int m_KeyPress;

private:
	std::shared_ptr<Sprite2D>	m_background;
	//std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::vector<std::shared_ptr<Player>>	m_listAnimation;
	std::shared_ptr<MouseButton> button;

	//player
	std::shared_ptr<Player> m_player, playerRotation;
	//Enemy
	std::shared_ptr<Enemy> m_enemy;
	std::list<std::shared_ptr<Enemy>> m_listEnemy;
	//Gun
	std::shared_ptr<Gun> m_gun;
	std::list<std::shared_ptr<Gun>> m_listGun;
	//Bullet
	std::shared_ptr<Bullet> m_bullet;
	std::list<std::shared_ptr<Bullet>> m_listBullet;

	float time = 0.0f;
	float m_Velocity = 10.0f;

	float m_shootDelay = 20;
	float m_lastShoot = 0.0;
	float gunAngle = 0.0;

	//int playerDirection = 1;
	//số hướng quay
	int numAngle = 8;
	//độ chia nhỏ nhất
	double angleSteps = 360.0 / numAngle;
	//hướng quay được chọn
	int currentAngleIndex = 0;
};

