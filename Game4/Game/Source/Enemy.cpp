#include "Framework.h"

#include "Enemy.h"
#include "Player.h"
#include "Tilemap.h"
#include "Pathfinder.h"

void AIState_Idle(Enemy* pObject, float deltaTime)
{
	ImGui::Text("State: Idle");
	if ((pObject->GetPlayer()->GetPosition() - pObject->GetPosition()).Length() < 6.0f)
	{
		pObject->SetFunctionPointer(AIState_Walk);
	}

}

void AIState_Walk(Enemy* pObject, float deltaTime)
{
	ImGui::Text("State: Walking");
	if ((pObject->GetPlayer()->GetPosition() - pObject->GetPosition()).Length() < 1.5f)
	{
		pObject->SetFunctionPointer(AIState_Attack);
	}
	else if ((pObject->GetPlayer()->GetPosition() - pObject->GetPosition()).Length() > 5.0f)
	{
		pObject->SetFunctionPointer(AIState_Idle);
	}
	pObject->WalkToPlayer(deltaTime);
}

void AIState_Attack(Enemy* pObject, float deltaTime)
{
	ImGui::Text("State: Attacking");
	if ((pObject->GetPlayer()->GetPosition() - pObject->GetPosition()).Length() > 1.5f)
	{
	pObject->SetFunctionPointer(AIState_Walk);
	}
}

Enemy::Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, Pathfinder* path, Player* player)
	: GameObject(pMesh, pShader, pTexture, pos)
	, m_pPathfinder(path)
	, m_pPlayer(player)
{
	//m_pAIStateFunction = &AIState_Idle;

	FloatTimer = 0.0f;

	LastLocation = pos;
	NextLocation = pos;
}

Enemy::Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::SpriteSheet* pSpriteSheet, vec2 pos, Pathfinder* path, Player* player)
	: GameObject(pMesh, pShader, pSpriteSheet, pos)
	, m_pPathfinder(path)
	, m_pPlayer(player)
{
	functionPointer = AIState_Idle;

	FloatTimer = 0.0f;

	LastLocation = pos;
	NextLocation = pos;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	functionPointer(this, deltaTime);
	
	
	DoAnimation(deltaTime);
}

void Enemy::DoAnimation(float deltaTime)
{
	fw::SpriteSheet::SpriteInfo info = m_pSpriteSheet->GetSpriteByName("block_02");
	m_UVScale = info.uvScale;
	m_UVOffset = info.uvOffset;

	FloatTimer += deltaTime;
	if (FloatTimer >= 1)
	{
		FloatTimer = 0;
	}
	m_Position = basePos + vec2(0, sin(2 * 3.141592f * FloatTimer) / 4);
}

void Enemy::UpdatePath()
{
	int sx = (int)(NextLocation.x / 1.5f + 0.5f);
	int sy = (int)(NextLocation.y / 1.5f + 0.5f);
	int ex = (int)(m_pPlayer->GetPosition().x / 1.5f + 0.5f);
	int ey = (int)(m_pPlayer->GetPosition().y / 1.5f + 0.5f);

	//int sx = (int)((NextLocation.x + 0.5f) / 1.5f);
	//int sy = (int)((NextLocation.y + 0.5f) / 1.5f);
	//int ex = (int)((m_pPlayer->GetPosition().x + 0.5f) / 1.5f);
	//int ey = (int)((m_pPlayer->GetPosition().y + 0.5f) / 1.5f);

	ImGui::Text("%d, %d", sx, sy);
	if (m_pPathfinder->FindPath(sx, sy, ex, ey))
	{
		m_path = m_pPathfinder->GetPath(ex, ey);
	}
}

Player* Enemy::GetPlayer()
{
	return m_pPlayer;
}

void Enemy::SetFunctionPointer(std::function<void(Enemy* pObject, float deltaTime)> pointer)
{
	functionPointer = pointer;
}

void Enemy::WalkToPlayer(float deltaTime)
{
	TickTrack += deltaTime;
	for (size_t i = 0; i < m_path.size(); i++)
	{
		ImGui::Text("%d", m_path[i]);
	}
	if (TickTrack > moveDuration)
	{
		TickTrack = 0;
		if (m_path.size() > 1)
		{
			int index = m_path[m_path.size() - 2];
			m_path.erase(m_path.begin() + m_path.size() - 2);
			LastLocation = NextLocation;
			NextLocation = m_pPathfinder->GetWorldPosition(index); //get index for world position.
		}
		else
		{
			LastLocation = NextLocation;
		}
		UpdatePath();

	}
	float percent = TickTrack / moveDuration;
	basePos = LastLocation + (NextLocation - LastLocation) * percent;
}

//void Idle()
//{
//	ImGui::Text("CURRENT STATE: IDLE");
//}
//
//void Walk()
//{
//	ImGui::Text("CURRENT STATE: WALKING");
//}
//
//void Attack()
//{
//	ImGui::Text("CURRENT STATE: ATTACKING");
//}
