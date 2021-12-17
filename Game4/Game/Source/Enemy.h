#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "GameObject.h"
#include <functional>

class Pathfinder;
class Player;

enum EnemyAIState
{
    AI_Idle,
    AI_Walking,
    AI_Attacking
};

class Enemy : public GameObject
{
public:
    Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, Pathfinder* path, Player* player);
    Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::SpriteSheet* pSpriteSheet, vec2 pos, Pathfinder* path, Player* player);
    virtual ~Enemy();

    virtual void Update(float deltaTime) override;

    void DoAnimation(float deltaTime);

    void SetPathfinder(Pathfinder* path) { m_pPathfinder = path; }

    void UpdatePath();

    Player* GetPlayer();

    void SetFunctionPointer(std::function<void(Enemy* pObject, float deltaTime)> pointer);

    void WalkToPlayer(float deltaTime);

protected:
    Player* m_pPlayer;
    float TickTrack = 0;
    float moveDuration = 1.0f;
    Pathfinder* m_pPathfinder;

    std::function<void(Enemy* pObject, float deltaTime)> functionPointer;

    std::vector<int> m_path;

    vec2 NextLocation;
    vec2 LastLocation;

    float FloatTimer;

    vec2 basePos;

};

#ifndef AI
#define AI
void AIState_Idle(Enemy* pObject, float deltaTime);
void AIState_Walk(Enemy* pObject, float deltaTime);
void AIState_Attack(Enemy* pObject, float deltaTime);

#endif // !AI