#pragma once
#include "Framework.h"
#include "DataTypes.h"

namespace fw
{
	class GameObject;
}

class Player;

class PlayerController;

class Bullet;

class Enemy;

class Pickup;

class Game : public fw::GameCore
{
public:
	Game(fw::FWCore& fwCore);
	virtual ~Game() override;

	virtual void OnEvent(fw::Event* pEvent) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	void Init();

	float GetTimePassed();

	void SpawnBullet(vec2 direction);

	void ReturnBulletToPool(Bullet* bullet);
	void ReturnEnemyToPool(Enemy* enemy);
	void ReturnPickupToPool(Pickup* pickup);

	void IncrementScore(int value);

	void CheckForCollisions();

	void CheckWinCondition();
	
	void GoToNextRound();

protected:
	fw::FWCore& m_FWCore;
	fw::ImGuiManager* gui_Manage;

	int v_yourScore;
	int v_enemiesKilled;
	int v_round;
	
	int v_highScore;

	float m_TimePassed;

	std::map < std::string, fw::Mesh*> m_Meshes;
	fw::ShaderProgram* m_pBasicShader;

	PlayerController* m_pPlayerController;

	std::vector<fw::GameObject*> m_SceneObjects;

	fw::GameObject* m_pPlayer;
	fw::GameObject* m_sinEnemy;
	fw::GameObject* m_sinEnemyTwo;
	fw::GameObject* m_sinPickup;
	fw::GameObject* m_sinBullet;

	std::vector<fw::GameObject*> m_Enemies;
	std::vector<fw::GameObject*> m_Pickups;
	std::vector<Bullet*> m_Bullets;
};
