#include "Framework.h"

#include "Game.h"
#include <string>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    fw::FWCore fwCore;
    Game game( fwCore );

    fwCore.Init( 600, 600 );
    game.Init();

    fwCore.Run( game );

    fwCore.Shutdown();
}
