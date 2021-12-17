#pragma once

#include "Framework.h"

class PlayerController
{
public:
    PlayerController();

    void OnEvent(fw::Event* pEvent);

    bool IsRightHeld();

protected:
    bool m_Right;
};
