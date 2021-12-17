#include "Framework.h"

#include "GameObject.h"

namespace fw
{
	GameObject::GameObject(Mesh* pMesh, ShaderProgram* pShader, vec2 position)
		: m_pMesh(pMesh)
		, m_pShader(pShader)
		, m_Pos(position)
		, m_Size (0.25f)
		, m_collisionRadius(1.0f)
		//, m_isActive(false)
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Update(float deltaTime)
	{
	}

	void GameObject::Draw()
	{
		m_pMesh->Draw(m_pShader, m_Pos, 0.0f);
	}

	void GameObject::Shrink(float deltaTime)
	{
		m_Size -= deltaTime;
	}

	bool GameObject::IsCollisionFound(GameObject* pOtherMesh)
	{
		assert(pOtherMesh != nullptr);

		float distance = m_Pos.DistanceTo(pOtherMesh->m_Pos);
		float combinedRadius = m_Size + pOtherMesh->m_Size;

		if (distance < combinedRadius)
		{
			return true;
		}

		return false;
	}

	void GameObject::SetPosition(vec2 position)
	{
		SetPosition(position.x, position.y);
		//p_X = position.x;
		//p_Y = position.y;
	}

	void GameObject::SetPosition(float x, float y)
	{
		m_Pos.x = x;
		m_Pos.y = y;
	}

	vec2 GameObject::GetPosition()
	{
		return m_Pos;
	}
	void GameObject::CheckBoundaries()
	{
		if (GetX() > 100.0f)
		{
			SetX(0.0f);
		}
		
		if (GetX() < 0.0f)
		{
			SetX(100.0f);
		}

		if (GetY() > 100.0f)
		{
			SetY(0.0f);
		}

		if (GetY() < 0.0f)
		{
			SetY(100.0f);
		}
	}
	void GameObject::SetX(float x)
	{
		m_Pos.x = x;
	}
	void GameObject::SetY(float y)
	{
		m_Pos.y = y;
	}
	float GameObject::GetX()
	{
		return m_Pos.x;
	}
	float GameObject::GetY()
	{
		return m_Pos.y;
	}
	void GameObject::SetCollisionRadius(float value)
	{
		m_collisionRadius = value;
	}
	float GameObject::GetCollisionRadius()
	{
		return m_collisionRadius;
	}
	//float GameObject::GetSize()
	//{
	//	return m_Size;
	//}
	//void GameObject::SetActive(bool active)
	//{
	//	m_isActive = active;
	//}
	//bool GameObject::IsActive()
	//{
	//	return m_isActive;
	//}
}