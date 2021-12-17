#pragma once

#include "Framework.h"

class PlayerController
{
public:
    PlayerController();

    void OnEvent(fw::Event* pEvent);

    bool IsRightHeld();
    bool IsUpHeld();
    bool IsLeftHeld();
    bool IsDownHeld();

protected:
    bool m_Right;
    bool m_Up;
    bool m_Left;
    bool m_Down;
};
