#include "Framework.h"

#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "PlayerController.h"
#include "Enemy.h"
#include "Tilemap.h"
#include "Layouts.h"
#include "Pathfinder.h"

Game::Game(fw::FWCore& fwCore)
    : m_FWCore( fwCore )
    , m_pImGuiManager( nullptr )
    , m_TimePassed( 0.0f )
    , m_pBasicShader( nullptr )
    , m_pTexture( nullptr )
    , m_pSpriteSheet( nullptr )
    , m_pTilemap( nullptr )
    , m_pPlayer( nullptr )
    , m_pEnemy1( nullptr )
    , m_pEnemy2( nullptr )
    , m_pPlayerController( nullptr )
{
}

Game::~Game()
{
    delete m_pPlayer;
    delete m_pEnemy1;
    delete m_pEnemy2;

    delete m_pPlayerController;

    delete m_pTilemap;

    delete m_pSpriteSheet;
    delete m_pTexture;
    delete m_pBasicShader;

    for( auto& it : m_Meshes )
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

    //std::vector<float> triangleVerts = { 0.0f,0.0f,0.5f,   0.5f,0.5f,1.0f,   -0.5f,0.5f,0.2f   };
    //std::vector<float> diamondVerts = { 0.0f,0.0f,0.5f,   0.5f,0.5f,1.0f,   -0.5f,0.5f,0.2f,    0.0f,1.0f,0.5f };
    std::vector<fw::VertexFormat> spriteVerts =
    {
        { vec2( 0.0f,1.0f)-vec2(0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
        { vec2( 0.0f,0.0f)-vec2(0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
        { vec2( 1.0f,1.0f)-vec2(0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
        { vec2( 1.0f,0.0f)-vec2(0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    };

        std::vector<fw::VertexFormat> tileVerts =
    {
        { vec2( 0.0f,1.0f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
        { vec2( 0.0f,0.0f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
        { vec2( 1.0f,1.0f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
        { vec2( 1.0f,0.0f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    };

    m_Meshes["Sprite"] = new fw::Mesh( GL_TRIANGLE_STRIP, spriteVerts );
    m_Meshes["Tile"] = new fw::Mesh( GL_TRIANGLE_STRIP, tileVerts );

    m_pBasicShader = new fw::ShaderProgram( "Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" );

    m_pTexture = new fw::Texture( "Data/Textures/Sprites.png" );

    m_pSpriteSheet = new fw::SpriteSheet( "Data/Textures/Sprites.json", m_pTexture );

    m_pTilemap = new Tilemap( this, g_MainMap, ivec2(g_MainMapWidth, g_MainMapHeight), vec2(1.5f,1.5f) );

    m_pPlayerController = new PlayerController();

    m_pPlayer = new Player( m_Meshes["Sprite"], m_pBasicShader, m_pSpriteSheet, vec2(1.5f, 1.5f), m_pPlayerController );
    m_pPlayer->SetTilemap( m_pTilemap );
    
    m_pEnemyPathfinder = new Pathfinder(m_pTilemap);

    m_pEnemy1 = new Enemy( m_Meshes["Sprite"], m_pBasicShader, m_pSpriteSheet, vec2(10.0f, 10.0f), m_pEnemyPathfinder, m_pPlayer);
    
    m_pEnemy2 = new Enemy(m_Meshes["Sprite"], m_pBasicShader, m_pSpriteSheet, vec2(0.0f, 2.0f), m_pEnemyPathfinder, m_pPlayer);
}

void Game::StartFrame()
{
    m_pPlayerController->StartFrame();
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pPlayerController->OnEvent( pEvent );
}

void Game::Update(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );
    ImGui::ShowDemoWindow();

    m_TimePassed += deltaTime;

    m_pPlayer->Update( deltaTime );
    m_pEnemy1->Update( deltaTime );
    m_pEnemy2->Update( deltaTime );

    CheckForCollisions();
}

void Game::Draw()
{
    glClearColor( 0.0f, 0.0f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    vec2 projScale = vec2(1/10.0f, 1/10.0f);
    static vec2 camPos = vec2(1.5f*10,1.5f*10)/2;
    ImGui::DragFloat2( "Cam Pos", &camPos.x, 0.01f );

    m_pTilemap->Draw( projScale, camPos );

    m_pPlayer->Draw( projScale, camPos );
    m_pEnemy1->Draw( projScale, camPos );
    m_pEnemy2->Draw( projScale, camPos );

    m_pImGuiManager->EndFrame();
}

void Game::CheckForCollisions()
{
    //if( m_pPlayer->IsCollidingWith( m_pEnemy ) )
    //{
    //    ImGui::Text( "Colliding" );
    //}
}
