#include "Framework.h"

#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "PlayerController.h"
#include "Enemy.h"
#include "Pickup.h"
#include "Bullet.h"
#include <time.h>

Game::Game(fw::FWCore& fwCore)
	: m_FWCore(fwCore)
	, gui_Manage(nullptr)
	, m_TimePassed(0.0f)
	, m_pBasicShader(nullptr)
	, m_pPlayer(nullptr)
	, m_pPlayerController(nullptr)
	, m_sinEnemy(nullptr)
	, m_sinEnemyTwo(nullptr)
	, m_sinPickup(nullptr)
	, m_sinBullet(nullptr)
	, m_Pickups{}
	, m_Enemies{}
	, m_Bullets{}
	, v_yourScore(0)
	, v_round(1)
	, v_enemiesKilled(0)
	, v_highScore(0)
{
}

Game::~Game()
{
	delete m_pPlayer;
	delete m_sinEnemy;
	delete m_sinPickup;

	delete m_pPlayerController;
	
	delete m_pBasicShader;

	/*for (auto& it = m_Meshes.begin(); it != m_Meshes.end(); it++)
	{
		delete it->second;
	}*/

	for (auto& it : m_Meshes)
	{
		delete it.second;
	}

	/*for (unsigned int i = 0; i < g_Enemies.size(); i++)
	{
		delete g_Enemies.at(i);
		g_Enemies.at(i) = nullptr;
	}

	for (unsigned int i = 0; i < g_Pickups.size(); i++)
	{
		delete g_Pickups.at(i);
		g_Pickups.at(i) = nullptr;
	}*/

	delete gui_Manage;
}

void Game::Init()
{
	srand((unsigned int)time(0));
	
	gui_Manage = new fw::ImGuiManager( &m_FWCore );
	gui_Manage->Init();
	
	glPointSize(10);

	std::vector<float> playerVerts = {
		0.0f,0.0f,1.0f,0.0f,0.0f,
		0.5f,0.5f,0.0f,1.0f,0.0f,
		0.5f,1.0f,0.0f,0.0f,1.0f,
		0.0f,1.5f,0.0f,0.0f,1.0f,
		-0.5f,1.0f,0.0f,1.0f,0.0f,
		-0.5f,0.5f,1.0f,0.0f,0.0f,
	};
	std::vector<float> enemyVertsOne = {
		0.0f,0.0f,1.0f,0.0f,0.0f,
		0.5f,0.5f,0.90f,0.0f,0.0f,
		0.0f,1.0f,0.80f,0.0f,0.0f,
		0.5f,1.5f,0.70f,0.0f,0.0f,
		0.0f,2.0f,0.60f,0.0f,0.0f,
		-0.5f,1.5f,0.50f,0.0f,0.0f,
		0.0f,1.0f,0.40f,0.0f,0.0f,
		-0.5f,0.5f,0.30f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,0.0f,
	};
	std::vector<float> enemyVertsTwo = {
		0.0f,0.0f,0.0f,0.0f,0.0f,
		0.5f,0.5f,0.5f,0.5f,0.5f,
		1.0f,0.0f,1.0f,1.0f,1.0f,
		1.0f,2.0f,0.5f,0.5f,0.5f,
		0.5f,1.5f,1.0f,1.0f,1.0f,
		0.0f,2.0f,0.5f,0.5f,0.5f,
		0.0f,0.0f,0.0f,0.0f,0.0f,
	};
	std::vector<float> pickupVerts = {
		0.0f,0.0f,0.0f,1.0f,0.0f,
		0.15f,0.35f,1.0f,1.0f,1.0f,
		0.5f,0.5f,0.0f,1.0f,0.0f,
		0.15f,0.65f,1.0f,1.0f,1.0f,
		0.0f,1.0f,0.0f,1.0f,0.0f,
		-0.15f,0.65f,1.0f,1.0f,1.0f,
		-0.5f,0.5f,0.0f,1.0f,0.0f,
		-0.15f,0.35f,1.0f,1.0f,1.0f,
		0.0f,0.0f,0.0f,1.0f,0.0f,
	};
	std::vector<float> bulletVerts = {
		0.0f,0.0f,1.0f,1.0f,0.0f,
		0.5f,0.5f,0.90f,0.90f,0.0f,
		0.25f,1.0f,0.80f,0.80f,0.0f,
		0.0f,1.5f,0.70f,0.70f,0.0f,
		-0.25f,1.0f,0.60f,0.60f,0.0f,
		-0.5f,0.5f,0.50f,0.50f,1.0f,
	};
	
	m_Meshes["Player"] = new fw::Mesh(GL_TRIANGLE_FAN, playerVerts);
	m_Meshes["EnemyOne"] = new fw::Mesh(GL_LINE_STRIP, enemyVertsOne);
	m_Meshes["EnemyTwo"] = new fw::Mesh(GL_LINE_STRIP, enemyVertsTwo);
	m_Meshes["Pickup"] = new fw::Mesh(GL_LINE_STRIP, pickupVerts);
	m_Meshes["Bullet"] = new fw::Mesh(GL_TRIANGLE_FAN, bulletVerts);


	/*g_Player = new fw::Player();

	for (int i = 0; i < 10; i++)
	{
		g_Enemies.push_back(new fw::Enemy);
		float randXEnemy = (((float)rand() / (float)RAND_MAX) * 2) * 2;
		float randYEnemy = (((float)rand() / (float)RAND_MAX) * 2) * 2;
		g_Enemies[i]->SetPosition(randXEnemy, randYEnemy);
	}

	for (int j = 0; j < 2; j++)
	{
		g_Pickups.push_back(new fw::Pickup);
		float randXPickup = (((float)rand() / (float)RAND_MAX) * 2) * 2 / -1;
		float randYPickup = (((float)rand() / (float)RAND_MAX) * 2) * 2 / -1;
		g_Pickups[j]->SetPosition(randXPickup, randYPickup);
	}*/

	m_pBasicShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag");

	m_pPlayerController = new PlayerController();

	m_pPlayer = new Player(m_Meshes["Player"], m_pBasicShader, vec2(50.0f, 50.0f), m_pPlayerController);
	
	m_sinEnemy = new Enemy(m_Meshes["EnemyOne"], m_pBasicShader, vec2(0.0f, 10.0f), 4);
	
	m_sinEnemyTwo = new Enemy(m_Meshes["EnemyTwo"], m_pBasicShader, vec2(0.0f, 10.0f), 4);

	m_sinPickup = new Pickup(m_Meshes["Pickup"], m_pBasicShader, vec2(5.0f, 5.0f));
	
	m_SceneObjects.push_back(m_pPlayer);

	//20 Enemies per round.
	for (size_t i = 0; i < 20; i++)
	{
		
		if (i % 2 == 0)
		{
			//Enemy* temporEnemy = new Enemy(m_Meshes["EnemyOne"], m_pBasicShader, vec2(rand() % 101, rand() % 101), 1); This caused warnings :'(
			Enemy* temporEnemy = new Enemy(m_Meshes["EnemyOne"], m_pBasicShader, vec2(static_cast<float>(rand()) / RAND_MAX * 100, static_cast<float>(rand()) / RAND_MAX * 100), 1);
			m_SceneObjects.push_back(temporEnemy);
		}
		else
		{
			Enemy* temporEnemy = new Enemy(m_Meshes["EnemyOne"], m_pBasicShader, vec2(static_cast<float>(rand()) / RAND_MAX * 100, static_cast<float>(rand()) / RAND_MAX * 100), 2);
			m_SceneObjects.push_back(temporEnemy);
		}
	}
	
	//5 Pickups per round.
	for (size_t i = 0; i < 5; i++)
	{
		Pickup* temporPickup = new Pickup(m_Meshes["Pickup"], m_pBasicShader, vec2(static_cast<float>(rand()) / RAND_MAX * 100, static_cast<float>(rand()) / RAND_MAX * 100));
		m_SceneObjects.push_back(temporPickup);
	}
	
	//Pool of 20 bullets.
	for (size_t i = 0; i < 30; i++)
	{
		m_Bullets.push_back(new Bullet(m_Meshes["Bullet"], m_pBasicShader, vec2(1.0f, 1.0f)));
	}
}

float Game::GetTimePassed()
{
	return m_TimePassed;
}

void Game::SpawnBullet(vec2 direction)
{
	Bullet* spawn = m_Bullets[0];
	spawn->SetPosition(m_pPlayer->GetX(), m_pPlayer->GetY());
	spawn->SetDirection(vec2(direction));
	m_SceneObjects.push_back(spawn);
	std::remove(m_Bullets.begin(), m_Bullets.end(), spawn);
}

void Game::ReturnBulletToPool(Bullet* bullet)
{	
	m_Bullets.insert(m_Bullets.end(), bullet);
	m_SceneObjects.erase(std::remove(m_SceneObjects.begin(), m_SceneObjects.end(), bullet), m_SceneObjects.end());
}

void Game::ReturnEnemyToPool(Enemy* enemy)
{
	m_Enemies.insert(m_Enemies.end(), enemy);
	m_SceneObjects.erase(std::remove(m_SceneObjects.begin(), m_SceneObjects.end(), enemy), m_SceneObjects.end());
}

void Game::ReturnPickupToPool(Pickup* pickup)
{
	m_Pickups.insert(m_Pickups.end(), pickup);
	m_SceneObjects.erase(std::remove(m_SceneObjects.begin(), m_SceneObjects.end(), pickup), m_SceneObjects.end());
}

void Game::IncrementScore(int value)
{
	v_yourScore += value;
}

void Game::OnEvent(fw::Event* pEvent)
{
	m_pPlayerController->OnEvent(pEvent);
	if (pEvent->GetEventType() == fw::EventType::Input)
	{
		fw::InputEvent* input = static_cast<fw::InputEvent*>(pEvent);
		if (input->GetDeviceType() == fw::DeviceType::Keyboard)
		{
			//WASD
			if (input->GetID() == 'W' && input->GetInputState() == fw::InputState::Pressed)
			{
				SpawnBullet(vec2(0.0f, 1.0f));
			}
			if (input->GetID() == 'A' && input->GetInputState() == fw::InputState::Pressed)
			{
				SpawnBullet(vec2(-1.0f, 0.0f));
			}
			if (input->GetID() == 'S' && input->GetInputState() == fw::InputState::Pressed)
			{
				SpawnBullet(vec2(0.0f, -1.0f));
			}
			if (input->GetID() == 'D' && input->GetInputState() == fw::InputState::Pressed)
			{
				SpawnBullet(vec2(1.0f, 0.0f));
			}

			//IJKL
			if (input->GetID() == 'I' && input->GetInputState() == fw::InputState::Pressed)
			{
				SpawnBullet(vec2(-1.0f, 1.0f));
			}
			if (input->GetID() == 'J' && input->GetInputState() == fw::InputState::Pressed)
			{
				SpawnBullet(vec2(-1.0f, -1.0f));
			}
			if (input->GetID() == 'K' && input->GetInputState() == fw::InputState::Pressed)
			{
				SpawnBullet(vec2(1.0f, -1.0f));
			}
			if (input->GetID() == 'L' && input->GetInputState() == fw::InputState::Pressed)
			{
				SpawnBullet(vec2(1.0f, 1.0f));
			}
		}
	}
	if (pEvent->GetEventType() == fw::EventType::Collision)
	{
		fw::CollisionEvent* col_event = static_cast<fw::CollisionEvent*>(pEvent);

		Player* youPlayer = dynamic_cast<Player*>(col_event->GetFirstObject());
		
		Bullet* bulletOne = dynamic_cast<Bullet*>(col_event->GetFirstObject());
		Bullet* bulletTwo = dynamic_cast<Bullet*>(col_event->GetSecondObject());

		Enemy* enemyOne = dynamic_cast<Enemy*>(col_event->GetFirstObject());
		Enemy* enemyTwo = dynamic_cast<Enemy*>(col_event->GetSecondObject());

		Pickup* pickupOne = dynamic_cast<Pickup*>(col_event->GetFirstObject());
		Pickup* pickupTwo = dynamic_cast<Pickup*>(col_event->GetSecondObject());

		bulletOne = bulletOne ? bulletOne : bulletTwo;
		enemyOne = enemyOne ? enemyOne : enemyTwo;
		pickupOne = pickupOne ? pickupOne : pickupTwo;

		if (bulletOne && ( enemyOne || enemyTwo))
		{
			ReturnBulletToPool(bulletOne);
			ReturnEnemyToPool(enemyOne ? enemyOne : enemyTwo);
			IncrementScore(10);
			v_enemiesKilled++;
		}

		if (bulletOne && (pickupOne || pickupTwo))
		{
			ReturnBulletToPool(bulletOne);
			ReturnPickupToPool(pickupOne ? pickupOne : pickupTwo);
		}

		if (youPlayer && (pickupOne || pickupTwo))
		{
			ReturnPickupToPool(pickupOne ? pickupOne : pickupTwo);
			IncrementScore(20);
		}
	}
	if (pEvent->GetEventType() == fw::EventType::Destroy)
	{
		fw::DestroyEvent* destroy_event = static_cast<fw::DestroyEvent*>(pEvent);
		
		Bullet* bulletOne = dynamic_cast<Bullet*>(destroy_event->GetFirstObject());
		Enemy* enemyOne = dynamic_cast<Enemy*>(destroy_event->GetFirstObject());
		Pickup* pickupOne = dynamic_cast<Pickup*>(destroy_event->GetFirstObject());

		if (bulletOne)
		{
			ReturnBulletToPool(bulletOne);
		}
		if (enemyOne)
		{
			ReturnEnemyToPool(enemyOne);
		}
		if (pickupOne)
		{
			ReturnPickupToPool(pickupOne);
		}
	}
	if (pEvent->GetEventType() == fw::EventType::GoToNextRound)
	{
		GoToNextRound();
	}
}

void Game::CheckForCollisions()
{
	for (size_t a = 0; a < m_SceneObjects.size() - 1; a++)
	{
		for (size_t b = a + 1; b < m_SceneObjects.size(); b++)
		{
			ImGui::Begin("Current Events");
			ImGui::Text("Distance: %f", m_SceneObjects[a]->GetPosition().DistanceTo(m_SceneObjects[b]->GetPosition()));
			ImGui::End();
			if (m_SceneObjects[a]->GetPosition().DistanceTo(m_SceneObjects[b]->GetPosition()) < m_SceneObjects[a]->GetCollisionRadius() + m_SceneObjects[b]->GetCollisionRadius())
			{
				m_FWCore.GetEventManager()->AddEvent(new fw::CollisionEvent(m_SceneObjects[a], m_SceneObjects[b]));
			}
		}
		
	}
	
	//ImGui::Text("EQ: %d", m_FWCore.GetEventManager()->m_EventQueue.size());
}

void Game::CheckWinCondition()
{
	if (m_Enemies.size() == 20)
	{
		v_round++;
		m_Enemies.clear();
		m_Pickups.clear();
		m_FWCore.GetEventManager()->AddEvent(new fw::GoToNextRound());
	}
}

void Game::GoToNextRound()
{
	//Wrap up round
	for (fw::GameObject* object : m_SceneObjects)
	{
		if (object != m_pPlayer)
		{
			m_FWCore.GetEventManager()->AddEvent(new fw::DestroyEvent(object));
		}
	}

	m_Enemies.clear();
	m_Pickups.clear();

	//Did you make the high-score?
	if (v_enemiesKilled > v_highScore)
	{
		v_highScore = v_enemiesKilled;
	}

	//Reset this for the new round!
	v_enemiesKilled = 0;

	//Proceed to new level
	switch (v_round)
	{
	case 1:
		//20 Enemies per round.
		for (size_t i = 0; i < 20; i++)
		{

			if (i % 2 == 0)
			{
				Enemy* temporEnemy = new Enemy(m_Meshes["EnemyOne"], m_pBasicShader, vec2(static_cast<float>(rand()) / RAND_MAX * 100, static_cast<float>(rand()) / RAND_MAX * 100), 1);
				m_SceneObjects.push_back(temporEnemy);
			}
			else
			{
				Enemy* temporEnemy = new Enemy(m_Meshes["EnemyOne"], m_pBasicShader, vec2(static_cast<float>(rand()) / RAND_MAX * 100, static_cast<float>(rand()) / RAND_MAX * 100), 2);
				m_SceneObjects.push_back(temporEnemy);
			}
		}

		//5 Pickups per round.
		for (size_t i = 0; i < 5; i++)
		{
			Pickup* temporPickup = new Pickup(m_Meshes["Pickup"], m_pBasicShader, vec2(static_cast<float>(rand()) / RAND_MAX * 100, static_cast<float>(rand()) / RAND_MAX * 100));
			m_SceneObjects.push_back(temporPickup);
		}

		//Pool of 20 bullets.
		for (size_t i = 0; i < 30; i++)
		{
			m_Bullets.push_back(new Bullet(m_Meshes["Bullet"], m_pBasicShader, vec2(1.0f, 1.0f)));
		}
		break;
	case 2:
		//20 Enemies per round.
		for (size_t i = 0; i < 20; i++)
		{

			if (i % 2 == 0)
			{
				Enemy* temporEnemy = new Enemy(m_Meshes["EnemyTwo"], m_pBasicShader, vec2(static_cast<float>(rand()) / RAND_MAX * 100, static_cast<float>(rand()) / RAND_MAX * 100), 3);
				m_SceneObjects.push_back(temporEnemy);
			}
			else
			{
				Enemy* temporEnemy = new Enemy(m_Meshes["EnemyTwo"], m_pBasicShader, vec2(static_cast<float>(rand()) / RAND_MAX * 100, static_cast<float>(rand()) / RAND_MAX * 100), 4);
				m_SceneObjects.push_back(temporEnemy);
			}
		}

		//5 Pickups per round.
		for (size_t i = 0; i < 5; i++)
		{
			Pickup* temporPickup = new Pickup(m_Meshes["Pickup"], m_pBasicShader, vec2(static_cast<float>(rand()) / RAND_MAX * 100, static_cast<float>(rand()) / RAND_MAX * 100));
			m_SceneObjects.push_back(temporPickup);
		}

		//Pool of 20 bullets.
		for (size_t i = 0; i < 30; i++)
		{
			m_Bullets.push_back(new Bullet(m_Meshes["Bullet"], m_pBasicShader, vec2(1.0f, 1.0f)));
		}
		break;
	case 3:
		//20 Enemies per round.
		for (size_t i = 0; i < 20; i++)
		{

			if (i % 4 == 0)
			{
				Enemy* temporEnemy = new Enemy(m_Meshes["EnemyOne"], m_pBasicShader, vec2(static_cast<float>(rand()) / RAND_MAX * 100, static_cast<float>(rand()) / RAND_MAX * 100), 1);
				m_SceneObjects.push_back(temporEnemy);
			}
			else if (i % 4 == 1)
			{
				Enemy* temporEnemy = new Enemy(m_Meshes["EnemyOne"], m_pBasicShader, vec2(static_cast<float>(rand()) / RAND_MAX * 100, static_cast<float>(rand()) / RAND_MAX * 100), 2);
				m_SceneObjects.push_back(temporEnemy);
			}
			else if (i % 4 == 2)
			{
				Enemy* temporEnemy = new Enemy(m_Meshes["EnemyTwo"], m_pBasicShader, vec2(static_cast<float>(rand()) / RAND_MAX * 100, static_cast<float>(rand()) / RAND_MAX * 100), 3);
				m_SceneObjects.push_back(temporEnemy);
			}
			else if (i % 4 == 3)
			{
				Enemy* temporEnemy = new Enemy(m_Meshes["EnemyTwo"], m_pBasicShader, vec2(static_cast<float>(rand()) / RAND_MAX * 100, static_cast<float>(rand()) / RAND_MAX * 100), 4);
				m_SceneObjects.push_back(temporEnemy);
			}
		}

		//5 Pickups per round.
		for (size_t i = 0; i < 5; i++)
		{
			Pickup* temporPickup = new Pickup(m_Meshes["Pickup"], m_pBasicShader, vec2(static_cast<float>(rand()) / RAND_MAX * 100, static_cast<float>(rand()) / RAND_MAX * 100));
			m_SceneObjects.push_back(temporPickup);
		}

		//Pool of 20 bullets.
		for (size_t i = 0; i < 30; i++)
		{
			m_Bullets.push_back(new Bullet(m_Meshes["Bullet"], m_pBasicShader, vec2(1.0f, 1.0f)));
		}
		break;
	case 4:
		m_FWCore.Shutdown();
		break;
	}
}

void Game::Update(float deltaTime)
{
	gui_Manage->StartFrame(deltaTime);
	ImGui::ShowDemoWindow();

	m_TimePassed += deltaTime;

	for (int i = 0; i < m_SceneObjects.size(); i++)
	{
		m_SceneObjects[i]->Update(deltaTime);
		if (m_SceneObjects[i] == m_pPlayer)
		{
			continue;
		}
		vec2 pos = m_SceneObjects[i]->GetPosition();

		if (pos.x > 100 || pos.x < 0 || pos.y > 100 || pos.y < 0)
		{
			m_FWCore.GetEventManager()->AddEvent(new fw::DestroyEvent(m_SceneObjects[i]));
		}
	}

	ImGui::Text("Welcome to the Fraud Engine Debug!");
	ImGui::Text("SCORE: %d", v_yourScore);
	ImGui::Text("PICKUPS: %d", m_Pickups.size());
	ImGui::Text("ENEMIES: %d", m_Enemies.size());
	ImGui::Text("ENEMIES DESTROYED: %i", v_enemiesKilled);
	ImGui::Text("ENEMY HIGH SCORE: %i", v_highScore);
	ImGui::Text("ROUND: %i", v_round);

	if (ImGui::Button("GO TO NEXT LEVEL")) //For some reason, for a glitch I can't patch, the enemy size of the vector reaches to 40, or anumber around that. Weirdly, it used to work, but I think after I git commited it, it's been weird. Oddly though, if the game is played as it is supposed to be, there is no issue and it runs fine.
	{
		if (m_Enemies.size() != 20)
		{
			v_round++;
			for (fw::GameObject* object : m_SceneObjects)
			{
				if (object != m_pPlayer)
				{
					m_FWCore.GetEventManager()->AddEvent(new fw::DestroyEvent(object));
				}
			}
			m_Enemies.clear();
			m_Pickups.clear();
			GoToNextRound();
		}
	}

	if (ImGui::Button("GO TO LEVEL 1")) //For some reason, along with the other button, the Enemy vecotr size gets all weird. Set to 40 when the buttons are pressed, but not when the game condition is actually fulfilled.
	{
		if (m_Enemies.size() != 20)
		{
			v_round = 1;
			for (fw::GameObject* object : m_SceneObjects)
			{
				if (object != m_pPlayer)
				{
					m_FWCore.GetEventManager()->AddEvent(new fw::DestroyEvent(object));
				}
			}
			m_Enemies.clear();
			m_Pickups.clear();
			GoToNextRound();
		}
	}

	//if (ImGui::Button("CREATE LEVEL"))
	//{
	//	GoToNextRound();
	//}

	CheckForCollisions();

	CheckWinCondition();
}

void Game::Draw()
{
	glClearColor(0.0f, 0.0f, 0.25f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//glUseProgram(m_pBasicShader->GetProgram());

	for (int d = 0; d < m_SceneObjects.size(); d++)
	{
		m_SceneObjects[d]->Draw();
	}

	gui_Manage->EndFrame();
}
