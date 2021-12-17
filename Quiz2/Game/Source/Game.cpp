#include "Framework.h"
#include <random>

#include "Game.h"
#include "GameObject.h"
#include "Shapes.h"

Game::Game(fw::FWCore& fwCore)
    : m_FWCore( fwCore )
    , m_pImGuiManager( nullptr )
    , m_TimePassed( 0.0f )
{
}

Game::~Game()
{
    delete m_pGameObject;

    for( auto& it : m_Meshes )
    {
        delete it.second;
    }

    for( auto& it : m_Shaders )
    {
        delete it.second;
    }

    for( auto& it : m_Textures )
    {
        delete it.second;
    }

    delete m_pImGuiManager;
}

void Game::Init()
{
    m_pImGuiManager = new fw::ImGuiManager( &m_FWCore );
    m_pImGuiManager->Init();

    // OpenGL settings.
    glPointSize( 10 );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    // Load our resources.
    m_Meshes["Sprite"] = new fw::Mesh( GL_TRIANGLE_STRIP, g_SpriteVerts );
    m_Shaders["Basic"] = new fw::ShaderProgram( "Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" );
    m_Textures["Player"] = new fw::Texture( "Data/Textures/player_05.png" );

    // Setup our camera.
    m_ProjectionScale = vec2( 1/10.0f, 1/10.0f );
    m_CameraPosition = vec2( 0, 0 );

    // Initialize GameObjects.
    m_pGameObject = new GameObject( this, m_Meshes["Sprite"], m_Shaders["Basic"], vec2(4,4), vec2(0,0) );
}

void Game::StartFrame(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );
}

void Game::OnEvent(fw::Event* pEvent)
{
}

void Game::Update(float deltaTime)
{
    //ImGui::ShowDemoWindow();

    m_TimePassed += deltaTime;
}

void Game::Draw()
{
    glClearColor( 0.0f, 0.0f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    // Draw GameObjects.
    m_pGameObject->Draw( m_ProjectionScale, m_CameraPosition );

    m_pImGuiManager->EndFrame();
}
