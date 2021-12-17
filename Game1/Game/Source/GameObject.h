#pragma once

#include "Framework.h"
#include "DataTypes.h"

namespace fw {
	class GameObject
	{
	public:
		GameObject(Mesh* pMesh, ShaderProgram* pShader, vec2 position);
		virtual ~GameObject();

		virtual void Update(float deltaTime);
		virtual void Draw();
		void Shrink(float deltaTime); //Play an animation for an instance to shrink until it reaches zero.

		bool IsCollisionFound(GameObject* pOtherMesh);

		void SetPosition(vec2 position);
		void SetPosition(float x, float y);
		vec2 GetPosition();

		void CheckBoundaries();

		void SetX(float x);
		void SetY(float y);
		float GetX();
		float GetY();

		void SetCollisionRadius(float value);
		float GetCollisionRadius();

		//float GetSize();

		//void SetActive(bool active);
		//bool IsActive();
		Mesh* m_pMesh;

	protected:
		ShaderProgram* m_pShader;

		vec2 m_Pos;

		float m_Size; //technically a radius.

		float m_collisionRadius;

		//bool m_isActive;
	};
}

