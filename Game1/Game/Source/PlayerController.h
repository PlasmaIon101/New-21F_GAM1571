#pragma once

#include "Framework.h"

class PlayerController
{
public:
	PlayerController();

	void OnEvent(fw::Event* pEvent);

	bool IsRightHeld();
	bool IsLeftHeld();
	bool IsUpHeld();
	bool IsDownHeld();

	bool IsWHeld();
	bool IsAHeld();
	bool IsSHeld();
	bool IsDHeld();
	bool IsIHeld();
	bool IsJHeld();
	bool IsKHeld();
	bool IsLHeld();
protected:
	//Movement
	bool m_MoveRight;
	bool m_MoveLeft;
	bool m_MoveUp;
	bool m_MoveDown;

	//Fire Bullet
	bool m_BulletTop;
	bool m_BulletTopRight;
	bool m_BulletRight;
	bool m_BulletBottomRight;
	bool m_BulletBottom;
	bool m_BulletBottomLeft;
	bool m_BulletLeft;
	bool m_BulletTopLeft;
};
